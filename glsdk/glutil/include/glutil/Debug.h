/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H

#include <string>
#include <vector>

/**
\file
\brief Includes a function for attaching to ARB/KHR_debug_output and printing error messages automatically. This header must be included after an OpenGL header.
**/

namespace glutil
{
	///\addtogroup module_glutil_debug
	///@{

	///Possible locations for debug outputs.
	enum OutputLocation
	{
		STD_OUT,	///<Output to standard out.
		STD_ERR,	///<Output to standard error.
	};

	/**
	\name Debug Output Piping
	**/

	///@{

	/**
	\brief Registers a function for automatically outputting debug messages.

	\ref module_glload "GL Load" must have been successfully initialized for this function to work.

	This function works with ARB_debug_output, KHR_debug_output, or GL 4.3. If the are not available, the
	function will return false. If you have registered a function before calling this one, then the registered
	function will pass the function through, including your void* argument.
	
	\param eLoc The destination where errors or other debug messages will be printed.
	\return true if the function was registered.
	**/
	bool RegisterDebugOutput(OutputLocation eLoc);

	///@}

	/**
	\name Error Codes
	These functions are used to convert OpenGL error codes into human-readable strings.
	**/

	///@{

	/**
	\brief Generates the enumerator string for an OpenGL error code.

	\returns The enumerator string for an error code. If \a errorCode is not an actual,
	valid OpenGL error code, it will return an empty string.
	**/
	std::string ErrorCodeToEnumString(GLenum errorCode);

	/**
	\brief Generates a string description for an OpenGL error code.

	This is a relatively short (sentence or two) length description of the meaning of an OpenGL error code.

	\returns A short (sentence or two) description of an OpenGL error code. If \a errorCode is not an
	actual, valid OpenGL error code, it will return an empty string.
	**/
	std::string ErrorCodeToDescription(GLenum errorCode);

	/**
	\brief Generates the enumerator string for an OpenGL framebuffer status code.

	This will generate a string representing the OpenGL enumerator for the status returned
	by <tt>glCheckFramebufferStatus</tt>.

	\returns The enumerator string for the framebuffer status. If \a framebufferStatus is not
	an actual, valid framebuffer status code, it will return an empty string.
	**/
	std::string FramebufferToEnumString(GLenum framebufferStatus);

	/**
	\brief Generates a description for an OpenGL framebuffer status code.
	
	This is a relatively short (sentence or two) length description of the meaning of an
	OpenGL framebuffer status code.

	\returns A short (sentence or two) description of a framebuffer status code. 
	If \a errorCode is not an actual, valid framebuffer status code, it will return an empty string.
	**/
	std::string FramebufferToDescription(GLenum framebufferStatus);
	///@}

	///@}
}


#endif //DEBUG_UTIL_H
