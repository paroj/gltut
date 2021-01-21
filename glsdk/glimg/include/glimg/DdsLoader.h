/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_DIRECT_DRAW_SURFACE_LOADER_H
#define GLIMG_DIRECT_DRAW_SURFACE_LOADER_H

#include <string>
#include "ImageSet.h"

/**
\file
\brief Has all of the DDS-based loaders.

**/

namespace glimg
{
	namespace loaders
	{
		/**
		\brief Contains the DDS loader functions and exceptions
		
		\ingroup module_glimg_loaders
		**/
		namespace dds
		{
			///\addtogroup module_glimg_exceptions
			///@{

			///Base class for all exceptions thrown by the DDS loaders.
			class DdsLoaderException : public std::exception
			{
			public:
			
			    virtual ~DdsLoaderException() throw() {}

				virtual const char *what() const throw() {return message.c_str();}

			protected:
				std::string message;
			};

			///Thrown if the DDS file could not be opened.
			class DdsFileNotFoundException : public DdsLoaderException
			{
			public:
				explicit DdsFileNotFoundException(const std::string &filename)
				{
					message = "The file \"" + filename + "\" could not be found.";
				}
			};

			///Thrown if the DDS data is not a valid DDS format.
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

			///Thrown if the DDS format uses features that the loader cannot yet handle.
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
			///@}

			/**
			\brief Loads a DDS file from the disk, given an ASCII filename.

			DDS is a good texture format, because it naturally fits the needs of textures. It
			supports features like mipmaps and arrays that other image formats do not.

			\throws DdsLoaderException The image could not be loaded.  There are derived classes from this type that could be thrown.
			\return An ImageSet that represents the loaded image data.

			\todo Flip the textures, or allow the user to decide not to.
			\todo Get 3D textures working.
			\todo Implement the D3D10 format.
			\todo Get array textures working. With mipmaps.
			\todo Get cubemap array textures working.
			**/
			ImageSet *LoadFromFile(const std::string &filename);

			///As LoadFromFile, but from an already loaded buffer. The buffer pointer may be deleted after this call.
			ImageSet *LoadFromMemory(const unsigned char *buffer, size_t bufSize);
		}
	}
}

#endif //GLIMG_DIRECT_DRAW_SURFACE_LOADER_H
