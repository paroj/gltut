
#ifndef GLIMG_DIRECT_DRAW_SURFACE_LOADER_H
#define GLIMG_DIRECT_DRAW_SURFACE_LOADER_H

#include <string>
#include "ImageSet.h"

namespace glimg
{
	namespace loaders
	{
		namespace dds
		{
			class DdsLoaderException : public std::exception
			{
			public:

				virtual const char *what() {return message.c_str();}

			protected:
				std::string message;
			};

			class DdsFileNotFoundException : public DdsLoaderException
			{
			public:
				explicit DdsFileNotFoundException(const std::string &filename)
				{
					message = "The file \"" + filename + "\" could not be found.";
				}
			};

			class DdsFileMalformedException : public DdsLoaderException
			{
			public:
				DdsFileMalformedException(const std::string &filename, const std::string &msg)
				{
					if(filename.empty())
						message = "The data is not a properly formatted DDS.\n";
					else
						message = "The file \"" + filename + "\" is not a proper DDS file.\n";

					message += msg;
				}
			};

			class DdsFileUnsupportedException : public DdsLoaderException
			{
			public:
				DdsFileUnsupportedException(const std::string &filename, const std::string &msg)
				{
					if(filename.empty())
						message = "The data uses DDS features that are not yet supported.\n";
					else
						message = "The file \"" + filename + "\" uses DDS features that are not yet supported.\n";

					message += msg;
				}
			};

			ImageSet *LoadFromFile(const std::string &filename);
			ImageSet *LoadFromMemory(const unsigned char *buffer, size_t bufSize);
		}
	}
}

#endif //GLIMG_DIRECT_DRAW_SURFACE_LOADER_H