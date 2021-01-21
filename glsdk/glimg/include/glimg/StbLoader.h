/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/


#ifndef GLIMG_STB_LOADER_H
#define GLIMG_STB_LOADER_H

#include <string>
#include "ImageSet.h"

/**
\file
\brief Has the STB-based image loading functions.

**/

namespace glimg
{
	namespace loaders
	{
		/**
		\brief Contains the loader for PNG, JPEG, TGA, BMP, and GIF formats
		
		\ingroup module_glimg_loaders
		**/
		namespace stb
		{
			///\addtogroup module_glimg_exceptions
			///@{

			///Base class for all exceptions thrown by the STB loaders.
			class StbLoaderException : public std::exception
			{
			public:
			    
			    virtual ~StbLoaderException() throw() {}

				virtual const char *what() const throw() {return message.c_str();}

			protected:
				std::string message;
			};

			///Thrown when the STB loader could not load the image.
			class UnableToLoadException : public StbLoaderException
			{
			public:
				UnableToLoadException()
				{
					message = "The memory buffer could not be loaded by STB_image.";
				}

				explicit UnableToLoadException(const std::string &filename)
				{
					message = "The file " + filename + " could not be loaded by STB_image.";
				}
			};
			///@}

			/**
			\brief Loads a file from the disk, given an ASCII filename.

			This loader uses the public domain STB library to process the files. It therefore
			can load the following image formats:

			\li PNG
			\li JPEG (non-progressive)
			\li BMP
			\li TGA
			\li GIF

			\throws StbLoaderException Could not load the image. There are derived classes from this type that could be thrown.
			\return An ImageSet that represents the loaded image data.
			**/
			ImageSet *LoadFromFile(const std::string &filename);

			///As LoadFromFile, but from an already loaded buffer. The buffer pointer may be deleted after this call.
			ImageSet *LoadFromMemory(const unsigned char *buffer, size_t bufSize);
		}
	}
}


#endif //GLIMG_STB_LOADER_H
