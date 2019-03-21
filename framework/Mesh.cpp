#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <iostream>
#include <glload/gl_3_2_comp.h>
#include <glload/gl_load.h>
#include <GL/freeglut.h>
#include "framework.h"
#include "Mesh.h"
#include "directories.h"
#include "rapidxml.hpp"
#include "rapidxml_helpers.h"

#define USE_RAPIDXML_PARSER

#define PARSE_THROW(cond, message)\
	if(!(cond))\
	throw std::runtime_error((message));

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
	while(inStream.good())\
	{\
	AttribData theValue;\
	inStream >> theValue.attribDataValue;\
	if(inStream.fail())\
	throw std::runtime_error("Parse error in array data stream.");\
	outputData.push_back(theValue);\
	inStream >> std::ws;\
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
			throw std::runtime_error("Unknown 'type' field.");

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

		explicit Attribute(const xml_node<> &attribElem)
		{
			int iAttributeIndex = rapidxml::get_attrib_int(attribElem, "index", ThrowAttrib);
			if(!((0 <= iAttributeIndex) && (iAttributeIndex < 16)))
				throw std::runtime_error("Attribute index must be between 0 and 16.");
			iAttribIx = iAttributeIndex;

			int iVectorSize = rapidxml::get_attrib_int(attribElem, "size", ThrowAttrib);
			if(!((1 <= iVectorSize) && (iVectorSize < 5)))
				throw std::runtime_error("Attribute size must be between 1 and 4.");
			iSize = iVectorSize;

			pAttribType = GetAttribType(rapidxml::get_attrib_string(attribElem, "type"));

			bIsIntegral = false;
			const xml_attribute<> *pIntegralAttrib = attribElem.first_attribute("integral");
			if(pIntegralAttrib)
			{
				std::string strIntegral = make_string(*pIntegralAttrib);
				if(strIntegral == "true")
					bIsIntegral = true;
				else if(strIntegral == "false")
					bIsIntegral = false;
				else
					throw std::runtime_error("Incorrect 'integral' value for the 'attribute'.");

				if(pAttribType->bNormalized)
					throw std::runtime_error("Attribute cannot be both 'integral' and a normalized 'type'.");

				if(pAttribType->eGLType == GL_FLOAT ||
					pAttribType->eGLType == GL_HALF_FLOAT ||
					pAttribType->eGLType == GL_DOUBLE)
					throw std::runtime_error("Attribute cannot be both 'integral' and a floating-point 'type'.");
			}

			//Parse text
			std::stringstream strStream;
			for(const xml_node<> *pChild = attribElem.first_node();
				pChild; pChild = pChild->next_sibling())
			{
				strStream.write(pChild->value(), pChild->value_size());
			}

			strStream.flush();
			pAttribType->ParseFunc(dataArray, strStream);

			if(dataArray.empty())
				throw std::runtime_error("The attribute must have an array of values.");
			if(dataArray.size() % iSize != 0)
				throw std::runtime_error("The attribute's data must be a multiple of its size in elements.");
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

	void ProcessVAO(const xml_node<> &vaoElem, std::string &strName, std::vector<GLuint> &attributes)
	{
		strName = rapidxml::get_attrib_string(vaoElem, "name");

		for(const xml_node<> *pSource = vaoElem.first_node("source");
			pSource;
			pSource = pSource->next_sibling("source"))
		{
			attributes.push_back(rapidxml::get_attrib_int(*pSource, "attrib", ThrowAttrib));
		}
	}


	struct IndexData
	{
		IndexData(const xml_node<> &indexElem)
		{
			std::string strType = rapidxml::get_attrib_string(indexElem, "type");

			if(strType != "uint" && strType != "ushort" && strType != "ubyte")
				throw std::runtime_error("Improper 'type' attribute value on 'index' element.");

			pAttribType = GetAttribType(strType);

			//Read the text
			std::stringstream strStream;
			for(const xml_node<> *pChild = indexElem.first_node();
				pChild; pChild = pChild->next_sibling())
			{
				strStream.write(pChild->value(), pChild->value_size());
			}
			strStream.flush();
			pAttribType->ParseFunc(dataArray, strStream);
			if(dataArray.empty())
				throw std::runtime_error("The index element must have an array of values.");
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

	RenderCmd ProcessRenderCmd(const xml_node<> &cmdElem)
	{
		RenderCmd cmd;

		const std::string strCmdName = rapidxml::get_attrib_string(cmdElem, "cmd");
		int iArrayCount = ARRAY_COUNT(g_allPrimitiveTypes);
		const PrimitiveType *pPrim = std::find_if(
			g_allPrimitiveTypes, &g_allPrimitiveTypes[iArrayCount],
			std::bind1st(PrimitiveTypeFinder(), strCmdName));

		if(pPrim == &g_allPrimitiveTypes[iArrayCount])
			throw std::runtime_error("Unknown 'cmd' field.");

		cmd.ePrimType = pPrim->eGLPrimType;

		const std::string strElemName = make_string_name(cmdElem);
		if(strElemName == "indices")
		{
			cmd.bIsIndexedCmd = true;
			cmd.primRestart = rapidxml::get_attrib_int(cmdElem, "prim-restart", -1);
		} 
		else if(strElemName == "arrays")
		{
			cmd.bIsIndexedCmd = false;
			cmd.start = rapidxml::get_attrib_int(cmdElem, "start", ThrowAttrib);
			if(cmd.start < 0)
				throw std::runtime_error("`array` 'start' index must be between 0 or greater.");

			cmd.elemCount = rapidxml::get_attrib_int(cmdElem, "count", ThrowAttrib);
			if(cmd.elemCount <= 0)
				throw std::runtime_error("`array` 'count' must be between 0 or greater.");
		}
		else
			throw std::runtime_error("Bad command element " + strElemName + ". Must be 'indices' or 'arrays'.");

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

		~MeshData()
		{
			glDeleteBuffers(1, &oAttribArraysBuffer);
			glDeleteBuffers(1, &oIndexBuffer);
			glDeleteVertexArrays(1, &oVAO);

			for(VAOMap::iterator curr = namedVAOs.begin(); curr != namedVAOs.end(); ++curr)
			{
				glDeleteVertexArrays(1, &curr->second);
			}
		}

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
		attribs.reserve(16);
		std::map<GLuint, int> attribIndexMap;	//Maps from attribute indices to 'attribs' indices.

		std::vector<IndexData> indexData;

		std::vector<std::pair<std::string, std::vector<GLuint> > > namedVaoList;

		{
			std::string strDataFilename = FindFileOrThrow(strFilename);
			std::ifstream fileStream(strDataFilename.c_str());
			if(!fileStream.is_open())
				throw std::runtime_error("Could not find the mesh file: " + strDataFilename);

			std::vector<char> fileData;
			fileData.reserve(2*1024*1024);
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
				std::cout << strDataFilename << ": Parse error in the mesh file." << std::endl;
				std::cout << e.what() << std::endl << e.where<char>() << std::endl;
				throw;
			}

			xml_node<> *pRootNode = doc.first_node("mesh");
			PARSE_THROW(pRootNode, ("`mesh` node not found in mesh file: " + strDataFilename));

			const xml_node<> *pNode = pRootNode->first_node("attribute");
			PARSE_THROW(pNode, ("`mesh` node must have at least one `attribute` child. File: " + strDataFilename));

			for(;
				pNode && (make_string_name(*pNode) == "attribute");
				pNode = rapidxml::next_element(pNode))
			{
				attribs.push_back(Attribute(*pNode));
				attribIndexMap[attribs.back().iAttribIx] = attribs.size() - 1;
			}

			for(;
				pNode && (make_string_name(*pNode) == "vao");
				pNode = rapidxml::next_element(pNode))
			{
				namedVaoList.push_back(std::pair<std::string, std::vector<GLuint> >());
				std::pair<std::string, std::vector<GLuint> > &namedVao = namedVaoList.back();
				ProcessVAO(*pNode, namedVao.first, namedVao.second);
			}

			for(;
				pNode;
				pNode = rapidxml::next_element(pNode))
			{
				m_pData->primatives.push_back(ProcessRenderCmd(*pNode));
				if(make_string_name(*pNode) == "indices")
					indexData.push_back(IndexData(*pNode));
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
					throw std::runtime_error("Some of the attribute arrays have different element counts.");
			}
			else
				iNumElements = attrib.NumElements();
		}

		//Create the "Everything" VAO.
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
				int iAttribOffset = -1;
				for(size_t iCount = 0; iCount < attribs.size(); iCount++)
				{
					if(attribs[iCount].iAttribIx == iAttrib)
					{
						iAttribOffset = iCount;
						break;
					}
				}

				const Attribute &attrib = attribs[iAttribOffset];
				attrib.SetupAttributeArray(attribStartLocs[iAttribOffset]);
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

	void Mesh::Render() const
	{
		if(!m_pData->oVAO)
			return;

		glBindVertexArray(m_pData->oVAO);
		std::for_each(m_pData->primatives.begin(), m_pData->primatives.end(),
			std::mem_fun_ref(&RenderCmd::Render));
		glBindVertexArray(0);
	}

	void Mesh::Render( const std::string &strMeshName ) const
	{
		VAOMap::const_iterator theIt = m_pData->namedVAOs.find(strMeshName);
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
}
