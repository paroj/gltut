///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-11-13
// Updated : 2010-01-28
// Licence : This source is under MIT License
// File    : glm/setup.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_setup
#define glm_setup

///////////////////////////////////////////////////////////////////////////////////////////////////
// Version

#define GLM_VERSION					90
#define GLM_VERSION_MAJOR			0
#define GLM_VERSION_MINOR			9
#define GLM_VERSION_PATCH			0
#define GLM_VERSION_REVISION		0

///////////////////////////////////////////////////////////////////////////////////////////////////
// Common values

#define GLM_DISABLE					0x00000000
#define GLM_ENABLE					0x00000001

///////////////////////////////////////////////////////////////////////////////////////////////////
// Message

#define GLM_MESSAGE_QUIET			0x00000000

#define GLM_MESSAGE_WARNING			0x00000001
#define GLM_MESSAGE_NOTIFICATION	0x00000002
#define GLM_MESSAGE_CORE			0x00000004
#define GLM_MESSAGE_EXTS			0x00000008
#define GLM_MESSAGE_SETUP			0x00000010

#define GLM_MESSAGE_ALL				GLM_MESSAGE_WARNING | GLM_MESSAGE_NOTIFICATION | GLM_MESSAGE_CORE | GLM_MESSAGE_EXTS | GLM_MESSAGE_SETUP

//! By default:
// #define GLM_MESSAGE				GLM_MESSAGE_QUIET

///////////////////////////////////////////////////////////////////////////////////////////////////
// Precision

#define GLM_PRECISION_NONE			0x00000000

#define GLM_PRECISION_LOWP_FLOAT	0x00000011
#define GLM_PRECISION_MEDIUMP_FLOAT	0x00000012
#define GLM_PRECISION_HIGHP_FLOAT	0x00000013	

#define GLM_PRECISION_LOWP_INT		0x00001100
#define GLM_PRECISION_MEDIUMP_INT	0x00001200
#define GLM_PRECISION_HIGHP_INT		0x00001300

#define GLM_PRECISION_LOWP_UINT		0x00110000
#define GLM_PRECISION_MEDIUMP_UINT	0x00120000
#define GLM_PRECISION_HIGHP_UINT	0x00130000	

///////////////////////////////////////////////////////////////////////////////////////////////////
// Compiler

#define GLM_COMPILER_UNKNOWNED		0x00000000

// Visual C++ defines
#define GLM_COMPILER_VC				0x01000000
#define GLM_COMPILER_VC2005			0x01000010
#define GLM_COMPILER_VC2008			0x01000020
#define GLM_COMPILER_VC2010			0x01000040

// GCC defines
#define GLM_COMPILER_GCC            0x02000000
#define GLM_COMPILER_GCC32			0x02000040
#define GLM_COMPILER_GCC33			0x02000080
#define GLM_COMPILER_GCC34			0x02000100
#define GLM_COMPILER_GCC35			0x02000200
#define GLM_COMPILER_GCC40			0x02000400
#define GLM_COMPILER_GCC41			0x02000800
#define GLM_COMPILER_GCC42			0x02001000
#define GLM_COMPILER_GCC43			0x02002000
#define GLM_COMPILER_GCC44			0x02004000
#define GLM_COMPILER_GCC45			0x02008000
#define GLM_COMPILER_GCC46			0x02010000
#define GLM_COMPILER_GCC50			0x02020000

// Borland C++ defines. How to identify BC?
#define GLM_COMPILER_BC				0x03000000
#define GLM_COMPILER_BCB4			0x03000400
#define GLM_COMPILER_BCB5			0x03000800
#define GLM_COMPILER_BCB6			0x03001000
//#define GLM_COMPILER_BCBX			0x03002000 // What's the version value?
#define GLM_COMPILER_BCB2009		0x03004000

#define GLM_MODEL_32				0x00000010
#define GLM_MODEL_64				0x00000020

#ifndef GLM_COMPILER

// CodeWarrior
#define GLM_COMPILER_CODEWARRIOR	0x04000000

/////////////////
// Visual C++ //

#ifdef _MSC_VER

#if defined(_WIN64)
#define GLM_MODEL	GLM_MODEL_64
#else
#define GLM_MODEL	GLM_MODEL_32
#endif//_WIN64

#if _MSC_VER == 1400
#define GLM_COMPILER GLM_COMPILER_VC2005
#elif _MSC_VER == 1500
#define GLM_COMPILER GLM_COMPILER_VC2008
#elif _MSC_VER == 1600
#define GLM_COMPILER GLM_COMPILER_VC2010
#else//_MSC_VER
#define GLM_COMPILER GLM_COMPILER_VC
#endif//_MSC_VER

//////////////////
// GCC defines //

#elif defined(__GNUC__)

#if(defined(__WORDSIZE) && (__WORDSIZE == 64)) || defined(__arch64__)
#define GLM_MODEL	GLM_MODEL_64
#else
#define GLM_MODEL	GLM_MODEL_32
#endif//

#if   (__GNUC__ == 3) && (__GNUC_MINOR__ == 2)
#define GLM_COMPILER GLM_COMPILER_GCC32
#elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
#define GLM_COMPILER GLM_COMPILER_GCC33
#elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 4)
#define GLM_COMPILER GLM_COMPILER_GCC34
#elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 5)
#define GLM_COMPILER GLM_COMPILER_GCC35
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 0)
#define GLM_COMPILER GLM_COMPILER_GCC40
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 1)
#define GLM_COMPILER GLM_COMPILER_GCC41
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 2)
#define GLM_COMPILER GLM_COMPILER_GCC42
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
#define GLM_COMPILER GLM_COMPILER_GCC43
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#define GLM_COMPILER GLM_COMPILER_GCC44
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 5)
#define GLM_COMPILER GLM_COMPILER_GCC45
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 6)
#define GLM_COMPILER GLM_COMPILER_GCC46
#elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 0)
#define GLM_COMPILER GLM_COMPILER_GCC50
#else
#define GLM_COMPILER GLM_COMPILER_GCC
#endif

#elif defined(_BORLANDC_)

#if defined(VER125)
#define GLM_COMPILER GLM_COMPILER_BCB4
#elif defined(VER130)
#define GLM_COMPILER GLM_COMPILER_BCB5
#elif defined(VER140)
#define GLM_COMPILER GLM_COMPILER_BCB6
#elif defined(VER200)
#define GLM_COMPILER GLM_COMPILER_BCB2009
#else
#define GLM_COMPILER GLM_COMPILER_BC
#endif

#elif defined(__MWERKS__)

#define GLM_COMPILER GLM_COMPILER_CODEWARRIOR

#else
#define GLM_COMPILER GLM_COMPILER_UNKNOWNED
#endif//__GNUC__

#endif//GLM_COMPILER

#ifndef GLM_COMPILER
#error "GLM_COMPILER undefined, your compiler may not be supported by GLM. Add #define GLM_COMPILER 0 to ignore this message."
#endif//GLM_COMPILER

#if(!defined(GLM_MODEL) && GLM_COMPILER != 0)
#error "GLM_MODEL undefined, your compiler may not be supported by GLM. Add #define GLM_MODEL 0 to ignore this message."
#endif//GLM_MODEL

#if(defined(GLM_MESSAGE) && (GLM_MESSAGE & (GLM_MESSAGE_SETUP | GLM_MESSAGE_NOTIFICATION)))
#	if(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_VC)
#		pragma message("GLM message: Compiled with Visual C++")
#	elif(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_GCC)
#		pragma message("GLM message: Compiled with GCC")
#	else
#		pragma message("GLM warning: Compiler not detected")
#	endif
#endif//GLM_MESSAGE

#if(defined(GLM_MESSAGE) && (GLM_MESSAGE & (GLM_MESSAGE_SETUP | GLM_MESSAGE_NOTIFICATION)))
#	if(GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM message: 64 bits model")
#	elif(GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM message: 32 bits model")
#	endif//GLM_MODEL
#endif//GLM_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Swizzle operators

#define GLM_SWIZZLE_NONE            0x00000000
#define GLM_SWIZZLE_XYZW            0x00000002
#define GLM_SWIZZLE_RGBA            0x00000004
#define GLM_SWIZZLE_STQP            0x00000008
#define GLM_SWIZZLE_FULL            (GLM_SWIZZLE_XYZW | GLM_SWIZZLE_RGBA | GLM_SWIZZLE_STQP)

//! By default:
// #define GLM_SWIZZLE GLM_SWIZZLE_NONE

#if(defined(GLM_MESSAGE) && (GLM_MESSAGE & (GLM_MESSAGE_SETUP | GLM_MESSAGE_NOTIFICATION)))
#	if !defined(GLM_SWIZZLE)|| (defined(GLM_SWIZZLE) && GLM_SWIZZLE == GLM_SWIZZLE_NONE)
#		pragma message("GLM message: No swizzling operator used")
#	elif(defined(GLM_SWIZZLE) && GLM_SWIZZLE == GLM_SWIZZLE_FULL)
#		pragma message("GLM message: Full swizzling operator support enabled")
#	elif(defined(GLM_SWIZZLE) && GLM_SWIZZLE & GLM_SWIZZLE_FULL)
#		pragma message("GLM message: Partial swizzling operator support enabled")
#	endif//GLM_SWIZZLE
#endif//GLM_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Use options

// To disable multiple vector component names access.
// GLM_USE_ONLY_XYZW

// To use anonymous union to provide multiple component names access for class valType. Visual C++ only.
// GLM_USE_ANONYMOUS_UNION

#if(defined(GLM_USE_ANONYMOUS_UNION) && !(GLM_COMPILER & GLM_COMPILER_VC))
#error "GLM_USE_ANONYMOUS_UNION is defined to use anonymous union implementation of vector types. Anonymous unions can't be used with GCC."
#endif//GLM_USE_ANONYMOUS_UNION

///////////////////////////////////////////////////////////////////////////////////////////////////
// Static assert

#if(defined(BOOST_STATIC_ASSERT))
#define GLM_STATIC_ASSERT(x) BOOST_STATIC_ASSERT(x)
#else
#define GLM_STATIC_ASSERT(x) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#endif//GLM_DEPENDENCE

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif//glm_setup
