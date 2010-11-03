
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <glloader/gl_3_2_comp.h>
#include <glloader/wgl_exts.h>
#include <glloader/gle.h>
#include <GL/freeglut.h>
#include <tinyxml.h>
#include "framework.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


namespace Framework
{
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
	{
		GLuint shader = glCreateShader(eShaderType);
		const char *strFileData = strShaderFile.c_str();
		glShaderSource(shader, 1, &strFileData, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;
			switch(eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = "data\\" + strShaderFilename;
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		return CreateShader(eShaderType, shaderData.str());
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		GLuint program = glCreateProgram();

		for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glAttachShader(program, shaderList[iLoop]);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv (program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		return program;
	}

	struct RenderCmd
	{
		bool bIsIndexedCmd;
		GLenum ePrimType;
		GLuint start;
		GLuint elemCount;
		GLenum eIndexDataType;	//Only if bIsIndexedCmd is true.
		int primRestart;		//Only if bIsIndexedCmd is true.

		void Render()
		{
			if(bIsIndexedCmd)
				glDrawElements(ePrimType, elemCount, eIndexDataType, (void*)start);
			else
				glDrawArrays(ePrimType, start, elemCount);
		}
	};

	union AttribData
	{
		float fValue;
		GLuint uiValue;
		GLint iValue;
		GLushort usValue;
		GLshort sValue;
		GLubyte ubValue;
		GLbyte bValue;
	};

	struct PrimitiveType
	{
		const char *strPrimitiveName;
		GLenum eGLPrimType;
	};

	struct AttribType
	{
		const char *strNameFromFile;
		bool bNormalized;
		GLenum eGLType;
		int iNumBytes;
		void(*ParseFunc)(std::vector<AttribData> &, std::istream &);
		void(*WriteToBuffer)(GLenum, const std::vector<AttribData> &, int, size_t);
	};

#define PARSE_ARRAY_FUNCDEF(attribDataValue, funcName)\
	void funcName(std::vector<AttribData> &outputData, std::istream &inStream)\
	{\
		inStream.seekg(0, std::ios_base::beg);\
		inStream >> std::skipws;\
\
		while(!inStream.eof() && inStream.good())\
		{\
			AttribData theValue;\
			inStream >> theValue.attribDataValue >> std::ws;\
			if(inStream.fail())\
				throw std::exception("Parse error in array data stream.");\
			outputData.push_back(theValue);\
		}\
	}\

	void WriteFloatsToBuffer(GLenum eBuffer, const std::vector<AttribData> &theData,
		int iSize, size_t iOffset)
	{
		std::vector<float> tempBuffer;
		tempBuffer.reserve(theData.size());

		for(size_t iLoop = 0; iLoop < theData.size(); iLoop++)
			tempBuffer.push_back(theData[iLoop].fValue);

		glBufferSubData(eBuffer, iOffset, tempBuffer.size() * sizeof(float), &tempBuffer[0]);
	}

#define WRITE_ARRAY_FUNCDEF(attribDataValue, attribType, funcName) \
	void funcName(GLenum eBuffer, const std::vector<AttribData> &theData, \
		int iSize, size_t iOffset) \
	{ \
		std::vector<attribType> tempBuffer; \
		tempBuffer.reserve(theData.size()); \
 \
		for(size_t iLoop = 0; iLoop < theData.size(); iLoop++) \
			tempBuffer.push_back(theData[iLoop].attribDataValue); \
 \
		glBufferSubData(eBuffer, iOffset, tempBuffer.size() * sizeof(attribType), &tempBuffer[0]); \
	} \


	PARSE_ARRAY_FUNCDEF(fValue,		ParseFloats);
	PARSE_ARRAY_FUNCDEF(uiValue,	ParseUInts);
	PARSE_ARRAY_FUNCDEF(iValue,		ParseInts);
	PARSE_ARRAY_FUNCDEF(usValue,	ParseUShorts);
	PARSE_ARRAY_FUNCDEF(sValue,		ParseShorts);
	PARSE_ARRAY_FUNCDEF(ubValue,	ParseUBytes);
	PARSE_ARRAY_FUNCDEF(bValue,		ParseBytes);

	WRITE_ARRAY_FUNCDEF(fValue,		float,		WriteFloats);
	WRITE_ARRAY_FUNCDEF(uiValue,	GLuint,		WriteUInts);
	WRITE_ARRAY_FUNCDEF(iValue,		GLint,		WriteInts);
	WRITE_ARRAY_FUNCDEF(usValue,	GLushort,	WriteUShorts);
	WRITE_ARRAY_FUNCDEF(sValue,		GLshort,	WriteShorts);
	WRITE_ARRAY_FUNCDEF(ubValue,	GLubyte,	WriteUBytes);
	WRITE_ARRAY_FUNCDEF(bValue,		GLbyte,		WriteBytes);



	namespace
	{
		const AttribType g_allAttributeTypes[] =
		{
			{"float",		false,	GL_FLOAT,			sizeof(GLfloat),	ParseFloats,	WriteFloats},
			{"half",		false,	GL_HALF_FLOAT,		sizeof(GLhalfARB),	ParseFloats,	WriteFloats},
			{"int",			false,	GL_INT,				sizeof(GLint),		ParseInts,		WriteInts},
			{"uint",		false,	GL_UNSIGNED_INT,	sizeof(GLuint),		ParseUInts,		WriteUInts},
			{"norm-int",	true,	GL_INT,				sizeof(GLint),		ParseInts,		WriteInts},
			{"norm-uint",	true,	GL_UNSIGNED_INT,	sizeof(GLuint),		ParseUInts,		WriteUInts},
			{"short",		false,	GL_SHORT,			sizeof(GLshort),	ParseShorts,	WriteShorts},
			{"ushort",		false,	GL_UNSIGNED_SHORT,	sizeof(GLushort),	ParseUShorts,	WriteUShorts},
			{"norm-short",	true,	GL_SHORT,			sizeof(GLshort),	ParseShorts,	WriteShorts},
			{"norm-ushort",	true,	GL_UNSIGNED_SHORT,	sizeof(GLushort),	ParseUShorts,	WriteUShorts},
			{"byte",		false,	GL_BYTE,			sizeof(GLbyte),		ParseBytes,		WriteBytes},
			{"ubyte",		false,	GL_UNSIGNED_BYTE,	sizeof(GLubyte),	ParseUBytes,	WriteUBytes},
			{"norm-byte",	true,	GL_BYTE,			sizeof(GLbyte),		ParseBytes,		WriteBytes},
			{"norm-ubyte",	true,	GL_UNSIGNED_BYTE,	sizeof(GLubyte),	ParseUBytes,	WriteUBytes},
		};

		const PrimitiveType g_allPrimitiveTypes[] =
		{
			{"triangles", GL_TRIANGLES},
			{"tri-strip", GL_TRIANGLE_STRIP},
			{"tri-fan", GL_TRIANGLE_FAN},
			{"lines", GL_LINES},
			{"line-strip", GL_LINE_STRIP},
			{"line-loop", GL_LINE_LOOP},
			{"points", GL_POINTS},
		};
	}

	struct AttribTypeFinder
	{
		typedef std::string first_argument_type;
		typedef AttribType second_argument_type;
		typedef bool result_type;

		bool operator() (const std::string &compareString, const AttribType &attrib) const
		{
			return compareString == attrib.strNameFromFile;
		}

	};

	struct PrimitiveTypeFinder
	{
		typedef std::string first_argument_type;
		typedef PrimitiveType second_argument_type;
		typedef bool result_type;

		bool operator() (const std::string &compareString, const PrimitiveType &prim) const
		{
			return compareString == prim.strPrimitiveName;
		}

	};

	const AttribType *GetAttribType(const std::string &strType)
	{
		int iArrayCount = ARRAY_COUNT(g_allAttributeTypes);
		const AttribType *pAttrib = std::find_if(
			g_allAttributeTypes, &g_allAttributeTypes[iArrayCount], std::bind1st(AttribTypeFinder(), strType));

		if(pAttrib == &g_allAttributeTypes[iArrayCount])
			throw std::exception("Unknown 'type' field.");

		return pAttrib;
	}

	struct Attribute
	{
		Attribute()
			: iAttribIx(0xFFFFFFFF)
			, pAttribType(NULL)
			, iSize(-1)
			, bIsIntegral(false)
		{}

		explicit Attribute(const TiXmlElement *pAttribElem)
		{
			int iAttributeIndex;
			if(pAttribElem->QueryIntAttribute("index", &iAttributeIndex) != TIXML_SUCCESS)
				throw std::exception("Missing 'index' attribute in an 'attribute' element.");
			if(!((0 <= iAttributeIndex) && (iAttributeIndex < 16)))
				throw std::exception("Attribute index must be between 0 and 16.");
			iAttribIx = iAttributeIndex;

			int iVectorSize;
			if(pAttribElem->QueryIntAttribute("size", &iVectorSize) != TIXML_SUCCESS)
				throw std::exception("Missing 'size' attribute in an 'attribute' element.");
			if(!((1 <= iVectorSize) && (iVectorSize < 5)))
				throw std::exception("Attribute size must be between 1 and 4.");
			iSize = iVectorSize;

			std::string strType;
			if(pAttribElem->QueryStringAttribute("type", &strType) != TIXML_SUCCESS)
				throw std::exception("Missing 'type' attribute in an 'attribute' element.");

			pAttribType = GetAttribType(strType);

			std::string strIntegral;
			if(pAttribElem->QueryStringAttribute("integral", &strIntegral) != TIXML_SUCCESS)
				 bIsIntegral = false;
			else
			{
				if(strIntegral == "true")
					bIsIntegral = true;
				else if(strIntegral == "false")
					bIsIntegral = false;
				else
					throw std::exception("Incorrect 'integral' value for the 'attribute'.");

				if(pAttribType->bNormalized)
					throw std::exception("Attribute cannot be both 'integral' and a normalized 'type'.");

				if(pAttribType->eGLType == GL_FLOAT ||
					pAttribType->eGLType == GL_HALF_FLOAT ||
					pAttribType->eGLType == GL_DOUBLE)
					throw std::exception("Attribute cannot be both 'integral' and a floating-point 'type'.");
			}
		
			//Read the text data.
			std::stringstream strStream;
			for(const TiXmlNode *pNode = pAttribElem->FirstChild();
				pNode;
				pNode = pNode->NextSibling())
			{
				const TiXmlText *pText = pNode->ToText();
				if(pText)
				{
					strStream << pText->ValueStr() << " ";
				}
			}

			strStream.flush();
			const std::string &strTest = strStream.str();

			//Parse the text stream.
			pAttribType->ParseFunc(dataArray, strStream);
			if(dataArray.empty())
				throw std::exception("The attribute's must have an array of values.");
			if(dataArray.size() % iSize != 0)
				throw std::exception("The attribute's data must be a multiple of its size in elements.");
		}

		Attribute(const Attribute &rhs)
		{
			iAttribIx = rhs.iAttribIx;
			pAttribType = rhs.pAttribType;
			iSize = rhs.iSize;
			bIsIntegral = rhs.bIsIntegral;
			dataArray = rhs.dataArray;
		}

		Attribute &operator=(const Attribute &rhs)
		{
			iAttribIx = rhs.iAttribIx;
			pAttribType = rhs.pAttribType;
			iSize = rhs.iSize;
			bIsIntegral = rhs.bIsIntegral;
			dataArray = rhs.dataArray;
			return *this;
		}

		size_t NumElements() const
		{
			return dataArray.size() / iSize;
		}

		size_t CalcByteSize() const
		{
			return dataArray.size() * pAttribType->iNumBytes;
		}

		void FillBoundBufferObject(size_t iOffset) const
		{
			pAttribType->WriteToBuffer(GL_ARRAY_BUFFER, dataArray, iSize, iOffset);
		}

		void SetupAttributeArray(size_t iOffset) const
		{
			glEnableVertexAttribArray(iAttribIx);
			if(bIsIntegral)
			{
				glVertexAttribIPointer(iAttribIx, iSize, pAttribType->eGLType,
					0, (void*)iOffset);
			}
			else
			{
				glVertexAttribPointer(iAttribIx, iSize,
					pAttribType->eGLType, pAttribType->bNormalized ? GL_TRUE : GL_FALSE,
					0, (void*)iOffset);
			}
		}

		GLuint iAttribIx;
		const AttribType *pAttribType;
		int iSize;
		bool bIsIntegral;
		std::vector<AttribData> dataArray;
	};

	void ProcessVAO(const TiXmlElement *pVaoElem, std::string &strName, std::vector<GLuint> &attributes)
	{
		if(pVaoElem->QueryStringAttribute("name", &strName) != TIXML_SUCCESS)
			throw std::exception("Missing 'name' attribute in a 'vao' element.");

		for(const TiXmlElement *pNode = pVaoElem->FirstChildElement();
			pNode;
			pNode = pNode->NextSiblingElement())
		{
			int iAttrib = -1;
			if(pNode->QueryIntAttribute("attrib", &iAttrib) != TIXML_SUCCESS)
				throw std::exception("Missing 'attrib' attribute in a 'source' element.");

			attributes.push_back(iAttrib);
		}
	}

	struct IndexData
	{
		IndexData(const TiXmlElement *pIndexElem)
		{
			std::string strType;
			if(pIndexElem->QueryStringAttribute("type", &strType) != TIXML_SUCCESS)
				throw std::exception("Missing 'type' attribute in an 'index' element.");

			if(strType != "uint" && strType != "ushort" && strType != "ubyte")
				throw std::exception("Improper 'type' attribute value on 'index' element.");

			pAttribType = GetAttribType(strType);

			//Read the text data.
			std::stringstream strStream;
			for(const TiXmlNode *pNode = pIndexElem->FirstChild();
				pNode;
				pNode = pNode->NextSibling())
			{
				const TiXmlText *pText = pNode->ToText();
				if(pText)
				{
					strStream << pText->ValueStr() << " ";
				}
			}

			strStream.flush();
			const std::string &strTest = strStream.str();

			//Parse the text stream.
			pAttribType->ParseFunc(dataArray, strStream);
			if(dataArray.empty())
				throw std::exception("The index element must have an array of values.");
		}

		IndexData()
			: pAttribType(NULL)
		{}

		IndexData(const IndexData &rhs)
		{
			pAttribType = rhs.pAttribType;
			dataArray = rhs.dataArray;
		}

		IndexData &operator=(const IndexData &rhs)
		{
			pAttribType = rhs.pAttribType;
			dataArray = rhs.dataArray;
			return *this;
		}

		size_t CalcByteSize() const
		{
			return dataArray.size() * pAttribType->iNumBytes;
		}

		void FillBoundBufferObject(size_t iOffset) const
		{
			pAttribType->WriteToBuffer(GL_ELEMENT_ARRAY_BUFFER, dataArray, 1, iOffset);
		}

		const AttribType *pAttribType;
		std::vector<AttribData> dataArray;
	};

	RenderCmd ProcessRenderCmd(const TiXmlElement *pCmdElem)
	{
		RenderCmd cmd;

		std::string strCmdName;
		if(pCmdElem->QueryStringAttribute("cmd", &strCmdName) != TIXML_SUCCESS)
			throw std::exception("Missing 'cmd' attribute in an 'arrays' or 'indices' element.");

		int iArrayCount = ARRAY_COUNT(g_allAttributeTypes);
		const PrimitiveType *pPrim = std::find_if(
			g_allPrimitiveTypes, &g_allPrimitiveTypes[iArrayCount],
			std::bind1st(PrimitiveTypeFinder(), strCmdName));

		if(pPrim == &g_allPrimitiveTypes[iArrayCount])
			throw std::exception("Unknown 'cmd' field.");

		cmd.ePrimType = pPrim->eGLPrimType;

		if(pCmdElem->ValueStr() == "indices")
		{
			cmd.bIsIndexedCmd = true;
			int iPrimRestart;
			if(pCmdElem->QueryIntAttribute("prim-restart", &iPrimRestart) == TIXML_SUCCESS)
			{
				if(iPrimRestart < 0)
					throw std::exception("Attribute 'start' must be between 0 or greater.");
			}
			else
				iPrimRestart = -1;
			cmd.primRestart = iPrimRestart;
		}
		else if(pCmdElem->ValueStr() == "arrays")
		{
			cmd.bIsIndexedCmd = false;
			int iStart;
			if(pCmdElem->QueryIntAttribute("start", &iStart) != TIXML_SUCCESS)
				throw std::exception("Missing 'start' attribute in an 'arrays' element.");
			if(iStart < 0)
				throw std::exception("Attribute 'start' must be between 0 or greater.");
			cmd.start = iStart;

			int iCount;
			if(pCmdElem->QueryIntAttribute("count", &iCount) != TIXML_SUCCESS)
				throw std::exception("Missing 'count' attribute in an 'arrays' element.");
			if(iCount <= 0)
				throw std::exception("Attribute 'count' must be between 0 or greater.");
			cmd.elemCount = iCount;
		}
		else
			throw std::exception("Bad element. Must be 'indices' or 'arrays'.");

		return cmd;
	}

	typedef std::map<std::string, GLuint> VAOMap;
	typedef VAOMap::value_type VAOMapData;

	struct MeshData
	{
		MeshData()
			: oAttribArraysBuffer(0)
			, oIndexBuffer(0)
			, oVAO(0)
		{}

		GLuint oAttribArraysBuffer;
		GLuint oIndexBuffer;
		GLuint oVAO;

		VAOMap namedVAOs;

		std::vector<RenderCmd> primatives;
	};

	Mesh::Mesh( const std::string &strFilename )
		: m_pData(new MeshData)
	{
		std::vector<Attribute> attribs;
		attribs.reserve(16); //Max possible attributes

		std::vector<IndexData> indexData;

		std::vector<std::pair<std::string, std::vector<GLuint> > > namedVaoList;

		{
			std::string strDataFilename = "data\\" + strFilename;
			std::ifstream fileStream(strDataFilename.c_str());

			TiXmlDocument theDoc;

			fileStream >> theDoc;
			fileStream.close();

			if(theDoc.Error())
				throw std::exception(theDoc.ErrorDesc());

			TiXmlHandle docHandle(&theDoc);

			const TiXmlElement *pProcNode = docHandle.FirstChild("mesh").FirstChild().ToElement();
			while(pProcNode->ValueStr() == "attribute")
			{
				attribs.push_back(Attribute(pProcNode));
				pProcNode = pProcNode->NextSiblingElement();
			}

			while(pProcNode->ValueStr() == "vao")
			{
				namedVaoList.push_back(std::pair<std::string, std::vector<GLuint> >());
				std::pair<std::string, std::vector<GLuint> > &namedVao = namedVaoList.back();
				ProcessVAO(pProcNode, namedVao.first, namedVao.second);
				pProcNode = pProcNode->NextSiblingElement();
			}

			for(; pProcNode; pProcNode = pProcNode->NextSiblingElement())
			{
				m_pData->primatives.push_back(ProcessRenderCmd(pProcNode));
				if(pProcNode->ValueStr() == "indices")
					indexData.push_back(IndexData(pProcNode));
			}
		}

		//Figure out how big of a buffer object for the attribute data we need.
		size_t iAttrbBufferSize = 0;
		std::vector<size_t> attribStartLocs;
		attribStartLocs.reserve(attribs.size());
		int iNumElements = 0;
		for(size_t iLoop = 0; iLoop < attribs.size(); iLoop++)
		{
			iAttrbBufferSize = iAttrbBufferSize % 16 ?
				(iAttrbBufferSize + (16 - iAttrbBufferSize % 16)) : iAttrbBufferSize;

			attribStartLocs.push_back(iAttrbBufferSize);
			const Attribute &attrib = attribs[iLoop];

			iAttrbBufferSize += attrib.CalcByteSize();

			if(iNumElements)
			{
				if(iNumElements != attrib.NumElements())
					throw std::exception("Some of the attribute arrays have different element counts.");
			}
			else
				iNumElements = attrib.NumElements();
		}

		//Create our VAO.
		glGenVertexArrays(1, &m_pData->oVAO);
		glBindVertexArray(m_pData->oVAO);

		//Create the buffer object.
		glGenBuffers(1, &m_pData->oAttribArraysBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_pData->oAttribArraysBuffer);
		glBufferData(GL_ARRAY_BUFFER, iAttrbBufferSize, NULL, GL_STATIC_DRAW);

		//Fill in our data and set up the attribute arrays.
		for(size_t iLoop = 0; iLoop < attribs.size(); iLoop++)
		{
			const Attribute &attrib = attribs[iLoop];
			attrib.FillBoundBufferObject(attribStartLocs[iLoop]);
			attrib.SetupAttributeArray(attribStartLocs[iLoop]);
		}

		//Fill the named VAOs.
		for(size_t iLoop = 0; iLoop < namedVaoList.size(); iLoop++)
		{
			std::pair<std::string, std::vector<GLuint> > &namedVao = namedVaoList[iLoop];
			GLuint vao = -1;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			for(size_t iAttribIx = 0; iAttribIx < namedVao.second.size(); iAttribIx++)
			{
				GLuint iAttrib = namedVao.second[iAttribIx];
				const Attribute &attrib = attribs[iAttrib];
				attrib.SetupAttributeArray(attribStartLocs[iAttrib]);
			}

			m_pData->namedVAOs[namedVao.first] = vao;
		}

		glBindVertexArray(0);

		//Get the size of our index buffer data.
		size_t iIndexBufferSize = 0;
		std::vector<size_t> indexStartLocs;
		indexStartLocs.reserve(indexData.size());
		for(size_t iLoop = 0; iLoop < indexData.size(); iLoop++)
		{
			iIndexBufferSize = iIndexBufferSize % 16 ?
				(iIndexBufferSize + (16 - iIndexBufferSize % 16)) : iIndexBufferSize;

			indexStartLocs.push_back(iIndexBufferSize);
			const IndexData &currData = indexData[iLoop];

			iIndexBufferSize += currData.CalcByteSize();
		}

		//Create the index buffer object.
		if(iIndexBufferSize)
		{
			glBindVertexArray(m_pData->oVAO);

			glGenBuffers(1, &m_pData->oIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pData->oIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferSize, NULL, GL_STATIC_DRAW);

			//Fill with data.
			for(size_t iLoop = 0; iLoop < indexData.size(); iLoop++)
			{
				const IndexData &currData = indexData[iLoop];
				currData.FillBoundBufferObject(indexStartLocs[iLoop]);
			}

			//Fill in indexed rendering commands.
			size_t iCurrIndexed = 0;
			for(size_t iLoop = 0; iLoop < m_pData->primatives.size(); iLoop++)
			{
				RenderCmd &prim = m_pData->primatives[iLoop];
				if(prim.bIsIndexedCmd)
				{
					prim.start = (GLuint)indexStartLocs[iCurrIndexed];
					prim.elemCount = (GLuint)indexData[iCurrIndexed].dataArray.size();
					prim.eIndexDataType = indexData[iCurrIndexed].pAttribType->eGLType;
					iCurrIndexed++;
				}
			}

			VAOMap::iterator endIt = m_pData->namedVAOs.end();
			for(VAOMap::iterator currIt = m_pData->namedVAOs.begin();
				currIt != endIt;
				++currIt)
			{
				VAOMapData &data = *currIt;
				glBindVertexArray(data.second);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pData->oIndexBuffer);
			}

			glBindVertexArray(0);
		}
	}

	Mesh::~Mesh()
	{
		delete m_pData;
	}

	void Mesh::Render()
	{
		if(!m_pData->oVAO)
			return;

		glBindVertexArray(m_pData->oVAO);
		std::for_each(m_pData->primatives.begin(), m_pData->primatives.end(),
			std::mem_fun_ref(&RenderCmd::Render));
		glBindVertexArray(0);
	}

	void Mesh::Render( const std::string &strMeshName )
	{
		VAOMap::iterator theIt = m_pData->namedVAOs.find(strMeshName);
		if(theIt == m_pData->namedVAOs.end())
			return;

		glBindVertexArray(theIt->second);
		std::for_each(m_pData->primatives.begin(), m_pData->primatives.end(),
			std::mem_fun_ref(&RenderCmd::Render));
		glBindVertexArray(0);
	}

	void Mesh::DeleteObjects()
	{
		glDeleteBuffers(1, &m_pData->oAttribArraysBuffer);
		m_pData->oAttribArraysBuffer = 0;
		glDeleteBuffers(1, &m_pData->oIndexBuffer);
		m_pData->oIndexBuffer = 0;
		glDeleteVertexArrays(1, &m_pData->oVAO);
		m_pData->oVAO = 0;

		VAOMap::iterator endIt = m_pData->namedVAOs.end();
		for(VAOMap::iterator currIt = m_pData->namedVAOs.begin();
			currIt != endIt;
			++currIt)
		{
			VAOMapData &data = *currIt;
			glDeleteVertexArrays(1, &data.second);
			data.second = 0;
		}
	}

	float DegToRad(float fAngDeg)
	{
		const float fDegToRad = 3.14159f * 2.0f / 360.0f;
		return fAngDeg * fDegToRad;
	}

	void MatrixStack::Rotate( glm::vec3 &axisOfRotation, float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fInvCos = 1.0f - fCos;
		float fSin = sinf(fAngRad);
		float fInvSin = 1.0f - fSin;

		glm::vec3 axis = glm::normalize(axisOfRotation);

		glm::mat4 theMat(1.0f);
		theMat[0].x = (axis.x * axis.x) + ((1 - axis.x * axis.x) * fCos);
		theMat[1].x = axis.x * axis.y * (fInvCos) - (axis.z * fSin);
		theMat[2].x = axis.x * axis.z * (fInvCos) + (axis.y * fSin);

		theMat[0].y = axis.x * axis.y * (fInvCos) + (axis.z * fSin);
		theMat[1].y = (axis.y * axis.y) + ((1 - axis.y * axis.y) * fCos);
		theMat[2].y = axis.y * axis.z * (fInvCos) - (axis.x * fSin);

		theMat[0].z = axis.x * axis.z * (fInvCos) - (axis.y * fSin);
		theMat[1].z = axis.y * axis.z * (fInvCos) + (axis.x * fSin);
		theMat[2].z = (axis.z * axis.z) + ((1 - axis.z * axis.z) * fCos);
		m_currMat *= theMat;
	}

	void MatrixStack::RotateX( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[1].y = fCos; theMat[2].y = -fSin;
		theMat[1].z = fSin; theMat[2].z = fCos;

		m_currMat *= theMat;
	}

	void MatrixStack::RotateY( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[2].x = fSin;
		theMat[0].z = -fSin; theMat[2].z = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::RotateZ( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[1].x = -fSin;
		theMat[0].y = fSin; theMat[1].y = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::Scale( const glm::vec3 &scaleVec )
	{
		glm::mat4 scaleMat(1.0f);
		scaleMat[0].x = scaleVec.x;
		scaleMat[1].y = scaleVec.y;
		scaleMat[2].z = scaleVec.z;

		m_currMat *= scaleMat;
	}

	void MatrixStack::Translate( const glm::vec3 &offsetVec )
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(offsetVec, 1.0f);

		m_currMat *= translateMat;
	}

	void MatrixStack::ApplyMatrix( const glm::mat4 &theMatrix )
	{
		m_currMat *= theMatrix;
	}

	void MatrixStack::SetIdentity()
	{
		m_currMat = glm::mat4(1.0f);
	}

	void MatrixStack::Perspective( float fDegFOV, float fAspectRatio, float fZNear, float fZFar )
	{
		glm::mat4 persMat(0.0f);

		const float degToRad = 3.14159f * 2.0f / 360.0f;
		float fFovRad = fDegFOV * degToRad;
		float fFrustumScale = 1.0f / tan(fFovRad / 2.0f);

		persMat[0].x = fFrustumScale * fAspectRatio;
		persMat[1].y = fFrustumScale;
		persMat[2].z = (fZFar + fZNear) / (fZNear - fZFar);
		persMat[2].w = -1.0f;
		persMat[3].z = (2 * fZFar * fZNear) / (fZNear - fZFar);

		m_currMat *= persMat;
	}

	void MatrixStack::SetMatrix( const glm::mat4 &theMatrix )
	{
		m_currMat = theMatrix;
	}
}


void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL/* | GLUT_MULTISAMPLE | GLUT_SRGB*/);
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (300, 200);
	glutCreateWindow (argv[0]);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	gleLoadFunctions();
	init();

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
