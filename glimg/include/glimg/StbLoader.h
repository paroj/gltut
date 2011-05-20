#ifndef GLIMG_STB_LOADER_H
#define GLIMG_STB_LOADER_H

#include <string>
#include "ImageSet.h"

namespace glimg
{
	namespace loaders
	{
		namespace stb
		{
			class StbLoaderException : public std::exception
			{
			public:

				virtual const char *what() {return message.c_str();}

			protected:
				std::string message;
			};

			class UnableToLoadException : public StbLoaderException
			{
			public:
				UnableToLoadException()
				{
					message = "The memory buffer could not be loaded by STB_image.";
				}

				explicit UnableToLoadException(const std::string filename)
				{
					message = "The file " + filename + " could not be loaded by STB_image.";
				}
			};

			ImageSet *LoadFromFile(const std::string &filename);
			ImageSet *LoadFromMemory(const unsigned char *buffer, size_t bufSize);
		}
	}
}


#endif //GLIMG_STB_LOADER_H
