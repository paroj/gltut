#include <string>
#include <strstream>
#include <vector>
#include <set>
#include <map>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <memory>

#include <istream>
#include <fstream>
#include <iostream>

#include <glload/gl_all.h>
#include "framework.h"
#include "Scene.h"
#include "Mesh.h"
#include <glutil/Shader.h>

#include "rapidxml.hpp"
#include "rapidxml_helpers.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


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

		void BindBinder(const StateBinder *pState) {pState->BindState();}
		void UnbindBinder(const StateBinder *pState) {pState->UnbindState();}
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

	private:
		Framework::Mesh *m_pMesh;
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

	class SceneNode
	{
	public:
		SceneNode(SceneMesh *pMesh, SceneProgram *pProg, const glm::vec3 &nodePos)
			: m_pMesh(pMesh)
			, m_pProg(pProg)
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

		void SetNodeOrient(const glm::fquat &nodeOrient)
		{
			m_nodeTm.m_orient = glm::normalize(nodeOrient);
		}

		void SetNodeScale(const glm::vec3 &nodeScale)
		{
			m_nodeTm.m_scale = nodeScale;
		}

		void Render(glm::mat4 baseMat) const
		{
			baseMat *= m_nodeTm.GetMatrix();
			glm::mat4 objMat = baseMat * m_objTm.GetMatrix();

			m_pProg->UseProgram();
			glUniformMatrix4fv(m_pProg->GetMatrixLoc(), 1, GL_FALSE, glm::value_ptr(objMat));

			if(m_pProg->GetNormalMatLoc() != -1)
			{
				glm::mat4 normMat = glm::transpose(glm::inverse(objMat));
				glUniformMatrix4fv(m_pProg->GetNormalMatLoc(), 1, GL_FALSE,
					glm::value_ptr(normMat));
			}

			std::for_each(m_binders.begin(), m_binders.end(), BindBinder);
			m_pMesh->Render();
			std::for_each(m_binders.rbegin(), m_binders.rend(), UnbindBinder);
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

	private:
		SceneMesh *m_pMesh;		//Unmanaged. We are deleted first, so these should always be real values.
		SceneProgram *m_pProg;	//Unmanaged. We are deleted first, so these should always be real values.

		std::vector<StateBinder*> m_binders;

		Transform m_nodeTm;
		Transform m_objTm;
	};

	typedef std::map<std::string, SceneMesh*> MeshMap;
	typedef std::map<std::string, SceneProgram*> ProgramMap;
	typedef std::map<std::string, SceneNode*> NodeMap;

	class SceneImpl
	{
	private:
		MeshMap m_meshes;
		ProgramMap m_progs;
		NodeMap m_nodes;

		std::vector<SceneNode *> m_rootNodes;

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
				ReadPrograms(*pSceneNode);
				ReadNodes(NULL, *pSceneNode);
			}
			catch(...)
			{
				std::for_each(m_meshes.begin(), m_meshes.end(), DeleteSecond<typename MeshMap::value_type>);
				std::for_each(m_progs.begin(), m_progs.end(), DeleteSecond<typename ProgramMap::value_type>);
				std::for_each(m_nodes.begin(), m_nodes.end(), DeleteSecond<typename NodeMap::value_type>);
				throw;
			}
		}

		~SceneImpl()
		{
			std::for_each(m_nodes.begin(), m_nodes.end(), DeleteSecond<typename NodeMap::value_type>);
			std::for_each(m_progs.begin(), m_progs.end(), DeleteSecond<typename ProgramMap::value_type>);
			std::for_each(m_meshes.begin(), m_meshes.end(), DeleteSecond<typename MeshMap::value_type>);
		}

		void Render(const glm::mat4 &cameraMatrix) const
		{
			for(NodeMap::const_iterator &theIt = m_nodes.begin();
				theIt != m_nodes.end();
				++theIt)
			{
				theIt->second->Render(cameraMatrix);
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

			std::cout << "Mesh: \"" << pNameNode->value() << "\", \"" << pFilenameNode->value()
				<< "\"" << std::endl;
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

			std::cout << "Program: \"" << pNameNode->value() << "\"" << std::endl;
			std::cout << "\tVertex Shader: \"" << pVertexShaderNode->value() << "\"" << std::endl;
			if(pGeometryShaderNode)
				std::cout << "\tGeometry Shader: \"" << pGeometryShaderNode->value() << "\"" << std::endl;
			std::cout << "\tFragment Shader: \"" << pFragmentShaderNode->value() << "\"" << std::endl;
			std::cout << "\tModel Matrix uniform: \"" << pModelMatrixNode->value() << "\"" << std::endl;
			if(pNormalMatrixNode)
				std::cout << "\tNormal Matrix uniform: \"" << pNormalMatrixNode->value() << "\"" << std::endl;

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
						throw std::runtime_error("The uniform block " + name + " could not be found.");

					int bindPoint = rapidxml::attrib_to_int(*pBindingNode, ThrowAttrib);
					glUniformBlockBinding(program, blockIx, bindPoint);

					std::cout << "\t->Block: \"" << pNameNode->value() << "\", "
						<< bindPoint << std::endl;
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
						throw std::runtime_error("The sampler " + name + " could not be found.");

					GLint textureUnit = rapidxml::attrib_to_int(*pTexunitNode, ThrowAttrib);
					glUseProgram(program);
					glUniform1i(samplerLoc, textureUnit);
					glUseProgram(0);

					std::cout << "\t->Sampler: \"" << pNameNode->value() << "\", "
						<<textureUnit << std::endl;
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

			SceneNode *pNode = new SceneNode(meshIt->second, progIt->second, nodePos);
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

			std::cout << "Node: \"" << pNameNode->value() << "\"";
			std::cout << "\tMesh: \"" << pMeshNode->value() << "\"";
			std::cout << "\tProgram: \"" << pProgNode->value() << "\"" << std::endl;

			std::cout << "\tPosition:    " << pPositionNode->value() << "\"" << std::endl;
			if(pOrientNode)
				std::cout << "\tOrientation: " << pOrientNode->value() << "\"" << std::endl;
			if(pScaleNode)
				std::cout << "\tScale:       " << pScaleNode->value() << "\"" << std::endl;

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

				std::cout << "\t->Note: \"" << pNameNode->value() << "\"" << std::endl;
				std::cout << "\t\t->" << noteNode.value() << "<-" << std::endl;
			}
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
}
