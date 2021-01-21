//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <glload/gl_all.hpp>
#include "GenHelper.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glmesh
{
	namespace gen
	{
		namespace
		{
			const char *g_variantNames[] =
			{
				"color",
				"lit",
				"tex",
			};

			void CalcName(std::ostringstream &outStream, const std::vector<std::string> &nameList)
			{
				outStream.clear();
				outStream.str("");
				outStream << nameList[0];
				for(size_t loop = 1; loop < nameList.size(); ++loop)
					outStream << "-" << nameList[loop];
			}

			std::vector<std::string> GenerateNameList(const int components)
			{
				std::vector<std::string> currNames;
				currNames.reserve(4);

				for(size_t comp = 0; comp < ARRAY_COUNT(g_variantNames); ++comp)
				{
					if(components & (0x1 << comp))
						currNames.push_back(g_variantNames[comp]);
				}

				return currNames;
			}
		}

		std::string GenerateNameForVariant( const int components )
		{
			if(components == 0)
				return "flat";

			std::ostringstream theName;
			CalcName(theName, GenerateNameList(components));

			return theName.str();
		}

		void AddVariantToMap(MeshVariantMap &variantMap, GLuint vao, const int components)
		{
			if(components == 0)
			{
				variantMap["unlit"] = vao;
				variantMap["flat"] = vao;
				return;
			}

			std::vector<std::string> currNames = GenerateNameList(components);

			if(currNames.size() == 1)
			{
				variantMap[currNames[0]] = vao;
				return;
			}

			std::sort(currNames.begin(), currNames.end());

			std::ostringstream theName;
			do
			{
				CalcName(theName, currNames);

				variantMap[theName.str()] = vao;
			}
			while(std::next_permutation(currNames.begin(), currNames.end()));
		}

		void BuildVariations( MeshVariantMap &variantMap, const std::vector<int> &components,
			const VertexFormat &fmt, GLuint indexBuffer )
		{
			const int numVariations = (int)std::pow(2.0f, (float)components.size());
			std::vector<GLuint> vaos(numVariations);
			gl::GenVertexArrays(numVariations, &vaos[0]);
			for(int variant = 0; variant < numVariations; ++variant)
			{
				gl::GenVertexArrays(1, &vaos[variant]);
				gl::BindVertexArray(vaos[variant]);
				gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBuffer);
				fmt.BindAttribute(0, 0);

				int variation = 0;
				for(size_t comp = 0; comp < components.size(); ++comp)
				{
					if(variant & (0x1 << comp))
					{
						variation |= components[comp];
						fmt.BindAttribute(0, comp + 1);
					}
				}

				AddVariantToMap(variantMap, vaos[variant], variation);
			}

			gl::BindVertexArray(0);
		}
	}
}