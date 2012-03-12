#include <string>
#include <strstream>
#include <vector>
#include <set>
#include <map>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <ctype.h>

#include <istream>
#include <fstream>
#include <iostream>

#include <glload/gl_all.h>
#include "framework.h"
#include "Scene.h"
#include "SceneBinders.h"
#include "Mesh.h"
#include <glutil/Shader.h>

#include "rapidxml.hpp"
#include "rapidxml_helpers.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glimg/glimg.h>


#define PARSE_THROW(cond, message)\
	if(!(cond))\
		throw std::runtime_error(message);


namespace Framework
{
	using rapidxml::xml_document;
	using rapidxml::xml_node;
	using rapidxml::xml_attribute;
	using rapidxml::make_string;


	namespace
	{
		void ThrowAttrib(const xml_attribute<> &attrib, const std::string &msg)
		{
			std::string name = make_string(attrib);
			throw std::runtime_error("Attribute " + name + " " + msg);
		}

		template<typename PairType>
		void DeleteSecond(PairType &value)
		{
			delete value.second;
			value.second = NULL;
		}

		template<typename DeleteType>
		void DeleteThis(DeleteType &value) { delete value; }

		struct BindBinder
		{
			BindBinder(GLuint prog) : m_prog(prog){}
			void operator()(const StateBinder *pState) const {pState->BindState(m_prog);}
			GLuint m_prog;
		};

		struct UnbindBinder
		{
			UnbindBinder(GLuint prog) : m_prog(prog){}
			void operator()(const StateBinder *pState) const {pState->UnbindState(m_prog);}
			GLuint m_prog;
		};

		std::string GetExtension(const std::string &filename)
		{
			size_t dotLoc = filename.rfind('.');
			if(dotLoc == std::string::npos)
				throw std::runtime_error("Texture must have an extension. " + filename + " does not.");

			std::string ext = filename.substr(dotLoc + 1);

			//Make lowercase.
			std::transform(ext.begin(), ext.end(), ext.begin(), tolower);

			return ext;
		}
	}

	class SceneMesh
	{
	public:
		SceneMesh(const std::string &filename)
			: m_pMesh(new Framework::Mesh(filename))
		{}

		~SceneMesh()
		{
			delete m_pMesh;
		}

		void Render() const
		{
			m_pMesh->Render();
		}

		Mesh *GetMesh() {return m_pMesh;}

	private:
		Mesh *m_pMesh;
	};

	class SceneTexture
	{
	public:
		SceneTexture(const std::string &filename, unsigned int creationFlags)
		{
			std::string pathname(Framework::FindFileOrThrow(filename));

			std::auto_ptr<glimg::ImageSet> pImageSet;
			std::string ext = GetExtension(pathname);
			if(ext == "dds")
			{
				pImageSet.reset(glimg::loaders::dds::LoadFromFile(pathname.c_str()));
			}
			else
			{
				pImageSet.reset(glimg::loaders::stb::LoadFromFile(pathname.c_str()));
			}

			m_texObj = glimg::CreateTexture(pImageSet.get(), creationFlags);
			m_texType = glimg::GetTextureType(pImageSet.get(), creationFlags);
		}

		~SceneTexture()
		{
			glDeleteTextures(1, &m_texObj);
		}

		GLuint GetTexture() const {return m_texObj;}
		GLenum GetType() const {return m_texType;}

	private:
		GLuint m_texObj;
		GLenum m_texType;
	};

	class SceneProgram
	{
	public:
		SceneProgram(GLuint programObj, GLint matrixLoc, GLint normalMatLoc)
			: m_programObj(programObj)
			, m_matrixLoc(matrixLoc)
			, m_normalMatLoc(normalMatLoc)
		{}

		~SceneProgram()
		{
			glDeleteProgram(m_programObj);
		}

		GLint GetMatrixLoc() const {return m_matrixLoc;}
		GLint GetNormalMatLoc() const {return m_normalMatLoc;}

		void UseProgram() const {glUseProgram(m_programObj);}

		GLuint GetProgram() const {return m_programObj;}

	private:
		GLuint m_programObj;
		GLint m_matrixLoc;
		GLint m_normalMatLoc;
	};

	struct Transform
	{
		Transform()
			: m_orient(1.0f, 0.0f, 0.0f, 0.0f)
			, m_scale(1.0f, 1.0f, 1.0f)
			, m_trans(0.0f, 0.0f, 0.0f)
		{}

		glm::mat4 GetMatrix() const
		{
			glm::mat4 ret;
			ret = glm::translate(ret, m_trans);
			ret *= glm::mat4_cast(m_orient);
			ret = glm::scale(ret, m_scale);
			return ret;
		}

		glm::fquat m_orient;
		glm::vec3 m_scale;
		glm::vec3 m_trans;
	};

	enum SamplerTypes
	{
		SPL_NEAREST,
		SPL_LINEAR,
		SPL_MIPMAP_NEAREST,
		SPL_MIPMAP_LINEAR,
		SPL_ANISOTROPIC,
		SPL_HALF_ANISOTROPIC,

		MAX_SAMPLERS,
	};

	SamplerTypes GetTypeFromName(const std::string &name)
	{
		const char *samplerNames[MAX_SAMPLERS] =
		{
			"nearest",
			"linear",
			"mipmap nearest",
			"mipmap linear",
			"anisotropic",
			"half anisotropic",
		};

		const char **theName = std::find(samplerNames, samplerNames + MAX_SAMPLERS, name);

		for(int spl = 0; spl < MAX_SAMPLERS; ++spl)
		{
			if(name == samplerNames[spl])
				return SamplerTypes(spl);
		}

		throw std::runtime_error("Unknown sampler name: " + name);
	}

	void MakeSamplerObjects(std::vector<GLuint> &samplers)
	{
		samplers.resize(MAX_SAMPLERS);
		glGenSamplers(MAX_SAMPLERS, &samplers[0]);

		//Always repeat.
		for(int samplerIx = 0; samplerIx < MAX_SAMPLERS; samplerIx++)
		{
			glSamplerParameteri(samplers[samplerIx], GL_TEXTURE_WRAP_S, GL_REPEAT);
			glSamplerParameteri(samplers[samplerIx], GL_TEXTURE_WRAP_T, GL_REPEAT);
			glSamplerParameteri(samplers[samplerIx], GL_TEXTURE_WRAP_R, GL_REPEAT);
		}

		glSamplerParameteri(samplers[0], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glSamplerParameteri(samplers[0], GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glSamplerParameteri(samplers[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplers[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glSamplerParameteri(samplers[2], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glSamplerParameteri(samplers[2], GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		glSamplerParameteri(samplers[3], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplers[3], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		GLfloat maxAniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);

		glSamplerParameteri(samplers[4], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplers[4], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(samplers[4], GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso / 2.0f);

		glSamplerParameteri(samplers[5], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplers[5], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(samplers[5], GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
	}

	struct TextureBinding
	{
		SceneTexture *pTex;
		GLuint texUnit;
		SamplerTypes sampler;
	};

	class SceneNode
	{
	public:
		SceneNode(SceneMesh *pMesh, SceneProgram *pProg, const glm::vec3 &nodePos,
			const std::vector<TextureBinding> &texBindings)
			: m_pMesh(pMesh)
			, m_pProg(pProg)
			, m_texBindings(texBindings)
		{
			m_nodeTm.m_trans = nodePos;
		}

		void NodeSetScale( const glm::vec3 &scale )
		{
			m_nodeTm.m_scale = scale;
		}

		void NodeRotate( const glm::fquat &orient )
		{
			m_nodeTm.m_orient = m_nodeTm.m_orient * orient;
		}

		void NodeSetOrient( const glm::fquat &orient )
		{
			m_nodeTm.m_orient = orient;
		}

		glm::fquat NodeGetOrient() const {return m_nodeTm.m_orient;}

		void SetNodeOrient(const glm::fquat &nodeOrient)
		{
			m_nodeTm.m_orient = glm::normalize(nodeOrient);
		}

		void SetNodeScale(const glm::vec3 &nodeScale)
		{
			m_nodeTm.m_scale = nodeScale;
		}

		void Render(const std::vector<GLuint> &samplers, glm::mat4 baseMat) const
		{
			baseMat *= m_nodeTm.GetMatrix();
			glm::mat4 objMat = baseMat * m_objTm.GetMatrix();

			m_pProg->UseProgram();
			glUniformMatrix4fv(m_pProg->GetMatrixLoc(), 1, GL_FALSE, glm::value_ptr(objMat));

			if(m_pProg->GetNormalMatLoc() != -1)
			{
				glm::mat3 normMat = glm::mat3(glm::transpose(glm::inverse(objMat)));
				glUniformMatrix3fv(m_pProg->GetNormalMatLoc(), 1, GL_FALSE,
					glm::value_ptr(normMat));
			}

			std::for_each(m_binders.begin(), m_binders.end(), BindBinder(m_pProg->GetProgram()));
			for(size_t texIx = 0; texIx < m_texBindings.size(); ++texIx)
			{
				const TextureBinding &binding = m_texBindings[texIx];
				glActiveTexture(GL_TEXTURE0 + binding.texUnit);
				glBindTexture(binding.pTex->GetType(), binding.pTex->GetTexture());
				glBindSampler(binding.texUnit, samplers[binding.sampler]);
			}

			m_pMesh->Render();

			for(size_t texIx = 0; texIx < m_texBindings.size(); ++texIx)
			{
				const TextureBinding &binding = m_texBindings[texIx];
				glActiveTexture(GL_TEXTURE0 + binding.texUnit);
				glBindTexture(binding.pTex->GetType(), 0);
				glBindSampler(binding.texUnit, 0);
			}
			std::for_each(m_binders.rbegin(), m_binders.rend(), UnbindBinder(m_pProg->GetProgram()));
			glUseProgram(0);
		}

		void NodeOffset(const glm::vec3 &offset)
		{
			m_nodeTm.m_trans += offset;
		}

		void NodeSetTrans(const glm::vec3 &offset)
		{
			m_nodeTm.m_trans = offset;
		}

		void SetStateBinder(StateBinder *pBinder)
		{
			m_binders.push_back(pBinder);
		}

		GLuint GetProgram() const
		{
			return m_pProg->GetProgram();
		}


	private:
		SceneMesh *m_pMesh;		//Unmanaged. We are deleted first, so these should always be real values.
		SceneProgram *m_pProg;	//Unmanaged. We are deleted first, so these should always be real values.

		std::vector<StateBinder*> m_binders;	//Unmanaged. These live beyond us.
		std::vector<TextureBinding> m_texBindings;

		Transform m_nodeTm;
		Transform m_objTm;
	};

	typedef std::map<std::string, SceneMesh*> MeshMap;
	typedef std::map<std::string, SceneTexture*> TextureMap;
	typedef std::map<std::string, SceneProgram*> ProgramMap;
	typedef std::map<std::string, SceneNode*> NodeMap;

	class SceneImpl
	{
	private:
		MeshMap m_meshes;
		TextureMap m_textures;
		ProgramMap m_progs;
		NodeMap m_nodes;

		std::vector<SceneNode *> m_rootNodes;

		std::vector<GLuint> m_samplers;

	public:
		SceneImpl(const std::string &filename)
		{
			std::string pathname = FindFileOrThrow(filename);

			std::ifstream fileStream(pathname.c_str());
			if(!fileStream.is_open())
				throw std::runtime_error("Could not open the scene file.");

			std::vector<char> fileData;
			fileData.reserve(2000);
			fileData.insert(fileData.end(), std::istreambuf_iterator<char>(fileStream),
				std::istreambuf_iterator<char>());
			fileData.push_back('\0');

			xml_document<> doc;

			try
			{
				doc.parse<0>(&fileData[0]);
			}
			catch(rapidxml::parse_error &e)
			{
				std::cout << filename << ": Parse error in scene file." << std::endl;
				std::cout << e.what() << std::endl << e.where<char>() << std::endl;
				throw;
			}

			xml_node<> *pSceneNode = doc.first_node("scene");
			PARSE_THROW(pSceneNode, "Scene node not found in scene file.");

			try
			{
				ReadMeshes(*pSceneNode);
				ReadTextures(*pSceneNode);
				ReadPrograms(*pSceneNode);
				ReadNodes(NULL, *pSceneNode);
			}
			catch(...)
			{
				std::for_each(m_nodes.begin(), m_nodes.end(), DeleteSecond<NodeMap::value_type>);
				std::for_each(m_progs.begin(), m_progs.end(), DeleteSecond<ProgramMap::value_type>);
				std::for_each(m_textures.begin(), m_textures.end(), DeleteSecond<TextureMap::value_type>);
				std::for_each(m_meshes.begin(), m_meshes.end(), DeleteSecond<MeshMap::value_type>);
				throw;
			}

			MakeSamplerObjects(m_samplers);
		}

		~SceneImpl()
		{
			glDeleteSamplers(m_samplers.size(), &m_samplers[0]);
			m_samplers.clear();

			std::for_each(m_nodes.begin(), m_nodes.end(), DeleteSecond<NodeMap::value_type>);
			std::for_each(m_progs.begin(), m_progs.end(), DeleteSecond<ProgramMap::value_type>);
			std::for_each(m_textures.begin(), m_textures.end(), DeleteSecond<TextureMap::value_type>);
			std::for_each(m_meshes.begin(), m_meshes.end(), DeleteSecond<MeshMap::value_type>);
		}

		void Render(const glm::mat4 &cameraMatrix) const
		{
			for(NodeMap::const_iterator theIt = m_nodes.begin();
				theIt != m_nodes.end();
				++theIt)
			{
				theIt->second->Render(m_samplers, cameraMatrix);
			}
		}

		NodeRef FindNode(const std::string &nodeName)
		{
			NodeMap::iterator theIt = m_nodes.find(nodeName);
			if(theIt == m_nodes.end())
				throw std::runtime_error("Could not find the node named: " + nodeName);

			return NodeRef(theIt->second);
		}

		GLuint FindProgram(const std::string &progName)
		{
			ProgramMap::iterator theIt = m_progs.find(progName);
			if(theIt == m_progs.end())
				throw std::runtime_error("Could not find the program named: " + progName);

			return theIt->second->GetProgram();
		}

		Mesh *FindMesh(const std::string &meshName)
		{
			MeshMap::iterator theIt = m_meshes.find(meshName);
			if(theIt == m_meshes.end())
				throw std::runtime_error("Could not find the mesh named: " + meshName);

			return theIt->second->GetMesh();
		}

		std::pair<GLuint, GLenum> FindTexture(const std::string &textureName)
		{
			TextureMap::iterator theIt = m_textures.find(textureName);
			if(theIt == m_textures.end())
				throw std::runtime_error("Could not find the texture named: " + textureName);

			return std::make_pair(theIt->second->GetTexture(), theIt->second->GetType());
		}

	private:

		void ReadMeshes(const xml_node<> &scene)
		{
			for(const xml_node<> *pMeshNode = scene.first_node("mesh");
				pMeshNode;
				pMeshNode = pMeshNode->next_sibling("mesh"))
			{
				ReadMesh(*pMeshNode);
			}
		}

		void ReadMesh(const xml_node<> &meshNode)
		{
			const xml_attribute<> *pNameNode = meshNode.first_attribute("xml:id");
			const xml_attribute<> *pFilenameNode = meshNode.first_attribute("file");

			PARSE_THROW(pNameNode, "Mesh found with no `xml:id` name specified.");
			PARSE_THROW(pFilenameNode, "Mesh found with no `file` filename specified.");

			std::string name = make_string(*pNameNode);
			if(m_meshes.find(name) != m_meshes.end())
				throw std::runtime_error("The mesh named \"" + name + "\" already exists.");

			m_meshes[name] = NULL;

			SceneMesh *pMesh = new SceneMesh(make_string(*pFilenameNode));

			m_meshes[name] = pMesh;
		}

		void ReadTextures(const xml_node<> &scene)
		{
			for(const xml_node<> *pTexNode = scene.first_node("texture");
				pTexNode;
				pTexNode = pTexNode->next_sibling("texture"))
			{
				ReadTexture(*pTexNode);
			}
		}

		void ReadTexture(const xml_node<> &TexNode)
		{
			const xml_attribute<> *pNameNode = TexNode.first_attribute("xml:id");
			const xml_attribute<> *pFilenameNode = TexNode.first_attribute("file");

			PARSE_THROW(pNameNode, "Texture found with no `xml:id` name specified.");
			PARSE_THROW(pFilenameNode, "Texture found with no `file` filename specified.");

			const xml_attribute<> *pSrgbNode = TexNode.first_attribute("srgb");

			std::string name = make_string(*pNameNode);
			if(m_textures.find(name) != m_textures.end())
				throw std::runtime_error("The texture named \"" + name + "\" already exists.");

			m_textures[name] = NULL;

			unsigned int creationFlags = 0;
			if(get_attrib_bool(TexNode, "srgb"))
				creationFlags |= glimg::FORCE_SRGB_COLORSPACE_FMT;

			SceneTexture *pTexture = new SceneTexture(make_string(*pFilenameNode), creationFlags);

			m_textures[name] = pTexture;
		}

		void ReadPrograms(const xml_node<> &scene)
		{
			for(const xml_node<> *pProgNode = scene.first_node("prog");
				pProgNode;
				pProgNode = pProgNode->next_sibling("prog"))
			{
				ReadProgram(*pProgNode);
			}
		}

		void ReadProgram(const xml_node<> &progNode)
		{
			const xml_attribute<> *pNameNode = progNode.first_attribute("xml:id");
			const xml_attribute<> *pVertexShaderNode = progNode.first_attribute("vert");
			const xml_attribute<> *pFragmentShaderNode = progNode.first_attribute("frag");
			const xml_attribute<> *pModelMatrixNode = progNode.first_attribute("model-to-camera");

			PARSE_THROW(pNameNode, "Program found with no `xml:id` name specified.");
			PARSE_THROW(pVertexShaderNode, "Program found with no `vert` vertex shader specified.");
			PARSE_THROW(pFragmentShaderNode, "Program found with no `frag` fragment shader specified.");
			PARSE_THROW(pModelMatrixNode, "Program found with no model-to-camera matrix uniform name specified.");

			//Optional.
			const xml_attribute<> *pNormalMatrixNode = progNode.first_attribute("normal-model-to-camera");
			const xml_attribute<> *pGeometryShaderNode = progNode.first_attribute("geom");

			std::string name = make_string(*pNameNode);
			if(m_progs.find(name) != m_progs.end())
				throw std::runtime_error("The program named \"" + name + "\" already exists.");

			m_progs[name] = NULL;

			std::vector<GLuint> shaders;
			GLuint program = 0;

			try
			{
				shaders.push_back(LoadShader(GL_VERTEX_SHADER, make_string(*pVertexShaderNode)));
				shaders.push_back(LoadShader(GL_FRAGMENT_SHADER, make_string(*pFragmentShaderNode)));
				if(pGeometryShaderNode)
					shaders.push_back(LoadShader(GL_GEOMETRY_SHADER, make_string(*pGeometryShaderNode)));
				program = glutil::LinkProgram(shaders);
			}
			catch(std::exception &)
			{
				std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
				throw;
			}

			std::for_each(shaders.begin(), shaders.end(), glDeleteShader);

			std::string matrixName = make_string(*pModelMatrixNode);
			GLint matrixLoc = glGetUniformLocation(program, matrixName.c_str());
			if(matrixLoc == -1)
			{
				glDeleteProgram(program);
				throw std::runtime_error("Could not find the matrix uniform " + matrixName +
					" in program " + name);
			}

			GLint normalMatLoc = -1;
			if(pNormalMatrixNode)
			{
				matrixName = make_string(*pNormalMatrixNode);
				normalMatLoc = glGetUniformLocation(program, matrixName.c_str());
				if(normalMatLoc == -1)
				{
					glDeleteProgram(program);
					throw std::runtime_error("Could not find the normal matrix uniform " + matrixName +
						" in program " + name);
				}
			}

			m_progs[name] = new SceneProgram(program, matrixLoc, normalMatLoc);

			ReadProgramContents(program, progNode);
		}

		void ReadProgramContents(GLuint program, const xml_node<> &progNode)
		{
			std::set<std::string> blockBindings;
			std::set<std::string> samplerBindings;

			for(const xml_node<> *pChildNode = progNode.first_node();
				pChildNode;
				pChildNode = pChildNode->next_sibling())
			{
				if(pChildNode->type() != rapidxml::node_element)
					continue;

				const std::string childName = std::string(pChildNode->name(), pChildNode->name_size());
				if(childName == "block")
				{
					const xml_attribute<> *pNameNode = pChildNode->first_attribute("name");
					const xml_attribute<> *pBindingNode = pChildNode->first_attribute("binding");

					PARSE_THROW(pNameNode, "Program `block` element with no `name`.");
					PARSE_THROW(pBindingNode, "Program `block` element with no `binding`.");

					std::string name = make_string(*pNameNode);
					if(blockBindings.find(name) != blockBindings.end())
						throw std::runtime_error("The uniform block " + name + " is used twice in the same program.");

					blockBindings.insert(name);

					GLuint blockIx = glGetUniformBlockIndex(program, name.c_str());
					if(blockIx == GL_INVALID_INDEX)
					{
						std::cout << "Warning: the uniform block " << name << " could not be found." << std::endl;
						continue;
					}

					int bindPoint = rapidxml::attrib_to_int(*pBindingNode, ThrowAttrib);
					glUniformBlockBinding(program, blockIx, bindPoint);
				}
				else if(childName == "sampler")
				{
					const xml_attribute<> *pNameNode = pChildNode->first_attribute("name");
					const xml_attribute<> *pTexunitNode = pChildNode->first_attribute("unit");

					PARSE_THROW(pNameNode, "Program `sampler` element with no `name`.");
					PARSE_THROW(pTexunitNode, "Program `sampler` element with no `unit`.");

					std::string name = make_string(*pNameNode);
					if(samplerBindings.find(name) != samplerBindings.end())
						throw std::runtime_error("A sampler " + name + " is used twice within the same program.");

					samplerBindings.insert(name);

					GLint samplerLoc = glGetUniformLocation(program, name.c_str());
					if(samplerLoc == -1)
					{
						std::cout << "Warning: the sampler " << name << " could not be found." << std::endl;
						continue;
					}

					GLint textureUnit = rapidxml::attrib_to_int(*pTexunitNode, ThrowAttrib);
					glUseProgram(program);
					glUniform1i(samplerLoc, textureUnit);
					glUseProgram(0);
				}
				else
				{
					//Bad node. Die.
					throw std::runtime_error("Unknown element found in program.");
				}
			}
		}

		void ReadNodes(SceneNode *pParent, const xml_node<> &scene)
		{
			for(const xml_node<> *pNodeNode = scene.first_node("node");
				pNodeNode;
				pNodeNode = pNodeNode->next_sibling("node"))
			{
				ReadNode(pParent, *pNodeNode);
			}
		}

		void ReadNode(SceneNode *pParent, const xml_node<> &nodeNode)
		{
			const xml_attribute<> *pNameNode = nodeNode.first_attribute("name");
			const xml_attribute<> *pMeshNode = nodeNode.first_attribute("mesh");
			const xml_attribute<> *pProgNode = nodeNode.first_attribute("prog");

			PARSE_THROW(pNameNode, "Node found with no `name` name specified.");
			PARSE_THROW(pMeshNode, "Node found with no `mesh` name specified.");
			PARSE_THROW(pProgNode, "Node found with no `prog` name specified.");

			const xml_attribute<> *pPositionNode = nodeNode.first_attribute("pos");
			const xml_attribute<> *pOrientNode = nodeNode.first_attribute("orient");
			const xml_attribute<> *pScaleNode = nodeNode.first_attribute("scale");

			PARSE_THROW(pPositionNode, "Node found with no `pos` specified.");

			std::string name = make_string(*pNameNode);
			if(m_nodes.find(name) != m_nodes.end())
				throw std::runtime_error("The node named \"" + name + "\" already exists.");

			m_nodes[name] = NULL;

			std::string meshName = make_string(*pMeshNode);
			MeshMap::iterator meshIt = m_meshes.find(meshName);
			if(meshIt == m_meshes.end())
			{
				throw std::runtime_error("The node named \"" + name + 
					"\" references the mesh \"" + meshName + "\" which does not exist.");
			}

			std::string progName = make_string(*pProgNode);
			ProgramMap::iterator progIt = m_progs.find(progName);
			if(progIt == m_progs.end())
			{
				throw std::runtime_error("The node named \"" + name + 
					"\" references the program \"" + progName + "\" which does not exist.");
			}

			glm::vec3 nodePos = rapidxml::attrib_to_vec3(*pPositionNode, ThrowAttrib);

			SceneNode *pNode = new SceneNode(meshIt->second, progIt->second, nodePos,
				ReadNodeTextures(nodeNode));
			m_nodes[name] = pNode;

			//TODO: parent/child nodes.
			if(!pParent)
				m_rootNodes.push_back(pNode);

			if(pOrientNode)
				pNode->SetNodeOrient(rapidxml::attrib_to_quat(*pOrientNode, ThrowAttrib));

			if(pScaleNode)
			{
				if(rapidxml::attrib_is_vec3(*pScaleNode))
					pNode->SetNodeScale(rapidxml::attrib_to_vec3(*pScaleNode, ThrowAttrib));
				else
				{
					float unifScale = rapidxml::attrib_to_float(*pScaleNode, ThrowAttrib);
					pNode->SetNodeScale(glm::vec3(unifScale));
				}
			}

			ReadNodeNotes(nodeNode);
		}

		void ReadNodeNotes(const xml_node<> &nodeNode)
		{
			for(const xml_node<> *pNoteNode = nodeNode.first_node("note");
				pNoteNode;
				pNoteNode = pNoteNode->next_sibling("note"))
			{
				const xml_node<> &noteNode = *pNoteNode;
				const xml_attribute<> *pNameNode = noteNode.first_attribute("name");
				PARSE_THROW(pNameNode, "Notations on nodes must have a `name` attribute.");
			}
		}

		std::vector<TextureBinding> ReadNodeTextures(const xml_node<> &nodeNode)
		{
			std::vector<TextureBinding> texBindings;
			std::set<GLuint> texUnits;

			for(const xml_node<> *pTexNode = nodeNode.first_node("texture");
				pTexNode;
				pTexNode = pTexNode->next_sibling("texture"))
			{
				const xml_node<> &texNode = *pTexNode;
				const xml_attribute<> *pNameNode = texNode.first_attribute("name");
				const xml_attribute<> *pUnitName = texNode.first_attribute("unit");
				const xml_attribute<> *pSamplerName = texNode.first_attribute("sampler");

				PARSE_THROW(pNameNode, "Textures on nodes must have a `name` attribute.");
				PARSE_THROW(pUnitName, "Textures on nodes must have a `unit` attribute.");
				PARSE_THROW(pSamplerName, "Textures on nodes must have a `sampler` attribute.");

				std::string textureName = make_string(*pNameNode);
				TextureMap::iterator texIt = m_textures.find(textureName);
				if(texIt == m_textures.end())
				{
					throw std::runtime_error("The node texture named \"" + textureName + 
						"\" is a texture which does not exist.");
				}

				TextureBinding binding;

				binding.pTex = texIt->second;
				binding.texUnit = rapidxml::attrib_to_int(*pUnitName, ThrowAttrib);
				binding.sampler = GetTypeFromName(make_string(*pSamplerName));

				if(texUnits.find(binding.texUnit) != texUnits.end())
					throw std::runtime_error("Multiply bound texture unit in node texture " + textureName);

				texBindings.push_back(binding);

				texUnits.insert(binding.texUnit);
			}

			return texBindings;
		}
	};

	void NodeRef::NodeSetScale( const glm::vec3 &scale )
	{
		m_pNode->NodeSetScale(scale);
	}

	void NodeRef::NodeSetScale( float scale )
	{
		m_pNode->NodeSetScale(glm::vec3(scale));
	}

	void NodeRef::NodeRotate( const glm::fquat &orient )
	{
		m_pNode->NodeRotate(orient);
	}

	void NodeRef::NodeSetOrient( const glm::fquat &orient )
	{
		m_pNode->NodeSetOrient(orient);
	}

	glm::fquat NodeRef::NodeGetOrient() const
	{
		return m_pNode->NodeGetOrient();
	}

	void NodeRef::NodeOffset( const glm::vec3 &offset )
	{
		m_pNode->NodeOffset(offset);
	}

	void NodeRef::NodeSetTrans( const glm::vec3 &offset )
	{
		m_pNode->NodeSetTrans(offset);
	}

	void NodeRef::SetStateBinder( StateBinder *pBinder )
	{
		m_pNode->SetStateBinder(pBinder);
	}

	GLuint NodeRef::GetProgram() const
	{
		return m_pNode->GetProgram();
	}

	Scene::Scene( const std::string &filename )
		: m_pImpl(new SceneImpl(filename))
	{}

	Scene::~Scene()
	{
		delete m_pImpl;
	}

	void Scene::Render( const glm::mat4 &cameraMatrix ) const
	{
		m_pImpl->Render(cameraMatrix);
	}

	Framework::NodeRef Scene::FindNode( const std::string &nodeName )
	{
		return m_pImpl->FindNode(nodeName);
	}

	GLuint Scene::FindProgram( const std::string &progName )
	{
		return m_pImpl->FindProgram(progName);
	}

	Mesh * Scene::FindMesh( const std::string &meshName )
	{
		return m_pImpl->FindMesh(meshName);
	}
}
