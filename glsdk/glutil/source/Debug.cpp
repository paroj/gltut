//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <stdio.h>
#include <string>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glutil/Debug.h"

namespace glutil
{
	namespace
	{
		GLDEBUGPROCARB g_oldProcARB = NULL;
		GLDEBUGPROC g_oldProcKHR = NULL;

		namespace arb
		{
			std::string GetErrorSource(GLenum source)
			{
				switch(source)
				{
				case gl::DEBUG_SOURCE_API_ARB: return "API";
				case gl::DEBUG_SOURCE_WINDOW_SYSTEM_ARB: return "Window System";
				case gl::DEBUG_SOURCE_SHADER_COMPILER_ARB: return "Shader Compiler";
				case gl::DEBUG_SOURCE_THIRD_PARTY_ARB: return "Third Party";
				case gl::DEBUG_SOURCE_APPLICATION_ARB: return "Application";
				case gl::DEBUG_SOURCE_OTHER_ARB: return "Other";
				default: return "WTF?";
				}
			}

			std::string GetErrorType(GLenum type)
			{
				switch(type)
				{
				case gl::DEBUG_TYPE_ERROR_ARB: return "Error";
				case gl::DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: return "Deprecated Functionality";
				case gl::DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: return "Undefined Behavior";
				case gl::DEBUG_TYPE_PORTABILITY_ARB: return "Portability";
				case gl::DEBUG_TYPE_PERFORMANCE_ARB: return "Performance";
				case gl::DEBUG_TYPE_OTHER_ARB: return "Other";
				default: return "WTF?";
				}
			}

			std::string GetErrorSeverity(GLenum severity)
			{
				switch(severity)
				{
				case gl::DEBUG_SEVERITY_HIGH_ARB: return "High";
				case gl::DEBUG_SEVERITY_MEDIUM_ARB: return "Medium";
				case gl::DEBUG_SEVERITY_LOW_ARB: return "Low";
				default: return "WTF?";
				}
			}
		}

		namespace khr
		{
			std::string GetErrorSource(GLenum source)
			{
				switch(source)
				{
				case gl::DEBUG_SOURCE_API: return "API";
				case gl::DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
				case gl::DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
				case gl::DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
				case gl::DEBUG_SOURCE_APPLICATION: return "Application";
				case gl::DEBUG_SOURCE_OTHER: return "Other";
				default: return "WTF?";
				}
			}

			std::string GetErrorType(GLenum type)
			{
				switch(type)
				{
				case gl::DEBUG_TYPE_ERROR: return "Error";
				case gl::DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Functionality";
				case gl::DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
				case gl::DEBUG_TYPE_PERFORMANCE: return "Performance";
				case gl::DEBUG_TYPE_PORTABILITY: return "Portability";
				case gl::DEBUG_TYPE_OTHER: return "Other";
				case gl::DEBUG_TYPE_MARKER: return "Marker";
				case gl::DEBUG_TYPE_PUSH_GROUP: return "Push group";
				case gl::DEBUG_TYPE_POP_GROUP: return "Pop group";
				default: return "WTF?";
				}
			}

			std::string GetErrorSeverity(GLenum severity)
			{
				switch(severity)
				{
				case gl::DEBUG_SEVERITY_HIGH: return "High";
				case gl::DEBUG_SEVERITY_MEDIUM: return "Medium";
				case gl::DEBUG_SEVERITY_LOW: return "Low";
				case gl::DEBUG_SEVERITY_NOTIFICATION: return "Notify";
				default: return "WTF?";
				}
			}
		}

		void APIENTRY DebugFuncARBStdOut(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const GLvoid* userParam)
		{
			if(g_oldProcARB)
				g_oldProcARB(source, type, id, severity, length, message, userParam);

			std::string srcName = arb::GetErrorSource(source);
			std::string errorType = arb::GetErrorType(type);
			std::string typeSeverity = arb::GetErrorSeverity(severity);

			printf("************************\n%s from %s,\t%s priority\nMessage: %s\n",
				errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
		}

		void APIENTRY DebugFuncARBStdErr(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const GLvoid* userParam)
		{
			if(g_oldProcARB)
				g_oldProcARB(source, type, id, severity, length, message, userParam);

			std::string srcName = arb::GetErrorSource(source);
			std::string errorType = arb::GetErrorType(type);
			std::string typeSeverity = arb::GetErrorSeverity(severity);

			fprintf(stderr, "************************\n%s from %s,\t%s priority\nMessage: %s\n",
				errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
		}

		void APIENTRY DebugFuncKHRStdOut(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const GLvoid* userParam)
		{
			if(g_oldProcKHR)
				g_oldProcKHR(source, type, id, severity, length, message, userParam);

			std::string srcName = khr::GetErrorSource(source);
			std::string errorType = khr::GetErrorType(type);
			std::string typeSeverity = khr::GetErrorSeverity(severity);

			printf("************************\n%s from %s,\t%s priority\nMessage: %s\n",
				errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
		}

		void APIENTRY DebugFuncKHRStdErr(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, GLvoid* userParam)
		{
			if(g_oldProcKHR)
				g_oldProcKHR(source, type, id, severity, length, message, userParam);

			std::string srcName = khr::GetErrorSource(source);
			std::string errorType = khr::GetErrorType(type);
			std::string typeSeverity = khr::GetErrorSeverity(severity);

			fprintf(stderr, "************************\n%s from %s,\t%s priority\nMessage: %s\n",
				errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
		}
	}

	bool RegisterDebugOutput( OutputLocation eLoc )
	{
		if(glload::IsVersionGEQ(4, 3) || gl::exts::var_KHR_debug)
		{
			void *pData = NULL;
			gl::GetPointerv(gl::DEBUG_CALLBACK_FUNCTION, (void**)(&g_oldProcKHR));
			if(g_oldProcKHR)
				gl::GetPointerv(gl::DEBUG_CALLBACK_USER_PARAM, &pData);

			gl::Enable(gl::DEBUG_OUTPUT_SYNCHRONOUS);

			switch(eLoc)
			{
			case STD_OUT:
				gl::DebugMessageCallbackARB(DebugFuncARBStdOut, pData);
				break;
			case STD_ERR:
				gl::DebugMessageCallbackARB(DebugFuncARBStdErr, pData);
				break;
			}

			return true;
		}

		if(gl::exts::var_ARB_debug_output)
		{
			void *pData = NULL;
			gl::GetPointerv(gl::DEBUG_CALLBACK_FUNCTION_ARB, (void**)(&g_oldProcARB));
			if(g_oldProcARB)
				gl::GetPointerv(gl::DEBUG_CALLBACK_USER_PARAM_ARB, &pData);

			gl::Enable(gl::DEBUG_OUTPUT_SYNCHRONOUS_ARB);

			switch(eLoc)
			{
			case STD_OUT:
				gl::DebugMessageCallbackARB(DebugFuncARBStdOut, pData);
				break;
			case STD_ERR:
				gl::DebugMessageCallbackARB(DebugFuncARBStdErr, pData);
				break;
			}

			return true;
		}

		return false;
	}

	std::string ErrorCodeToEnumString( GLenum errorCode )
	{
		switch(errorCode)
		{
		case gl::INVALID_ENUM:
			return "GL_INVALID_ENUM";
		case gl::INVALID_VALUE:
			return "GL_INVALID_VALUE";
		case gl::INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
		case gl::OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
		case gl::INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case gl::STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW";
		case gl::STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW";
		case gl::TABLE_TOO_LARGE:
			return "GL_TABLE_TOO_LARGE";
		}

		return std::string();
	}

	std::string ErrorCodeToDescription( GLenum errorCode )
	{
		switch(errorCode)
		{
		case gl::INVALID_ENUM:
			return "An enumerator passed to a function is not an acceptable enumerator.";
		case gl::INVALID_VALUE:
			return "One of the integer or float values passed to a function is outside the accepted range.";
		case gl::INVALID_OPERATION:
			return "A combination of parameters to a function or the interaction with context state is not acceptable.";
		case gl::OUT_OF_MEMORY:
			return "OpenGL cannot allocate that much memory";
		case gl::INVALID_FRAMEBUFFER_OPERATION:
			return "The current draw or read framebuffer is not complete.";
		case gl::STACK_OVERFLOW:
			return "An operation attempted to push onto a stack that exceeded the stack's size.";
		case gl::STACK_UNDERFLOW:
			return "An operation attempted to pop from an empty stack.";
		case gl::TABLE_TOO_LARGE:
			return "The color lookup or histogram table is too large.";
		}

		return std::string();
	}

	std::string FramebufferToEnumString( GLenum framebufferStatus )
	{
		switch(framebufferStatus)
		{
		case gl::FRAMEBUFFER_UNDEFINED:
			return "GL_FRAMEBUFFER_UNDEFINED";
		case gl::FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
		case gl::FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
		case gl::FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
		case gl::FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
		case gl::FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
		case gl::FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
		case gl::FRAMEBUFFER_UNSUPPORTED:
			return "GL_FRAMEBUFFER_UNSUPPORTED";
		case gl::FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			return "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT";
		case gl::FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			return "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT";
		}

		return std::string();
	}

	std::string FramebufferToDescription( GLenum framebufferStatus )
	{
		switch(framebufferStatus)
		{
		case gl::FRAMEBUFFER_UNDEFINED:
			return "The framebuffer is the default framebuffer, and the default framebuffer does not exist.";
		case gl::FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			return "One of the framebuffer's attachments is incomplete.";
		case gl::FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			return "No image is attached, and no default width/height parameters are set.";
		case gl::FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			return "One of the images specified in the draw buffers array does not have an image attached.";
		case gl::FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			return "One of the images specified in the read buffers array does not have an image attached.";
		case gl::FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			return "The attached images have an inconsistent number of samples.";
		case gl::FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			return "The attached images have an inconsistent layering attachment. Some are layered and some are not.";
		case gl::FRAMEBUFFER_UNSUPPORTED:
			return "The combination of image formats is not supported in this implementation.";
		case gl::FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			return "The attached images have inconsistent widths/heights.";
		case gl::FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			return "The color attachments have inconsistent internal formats.";
		}

		return std::string();
	}
}

