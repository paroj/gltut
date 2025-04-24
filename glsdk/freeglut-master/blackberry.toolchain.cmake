# ------------------------------------------------------------------------------
#  BlackBerry CMake toolchain file, for use with the BlackBerry 10 NDK 
#  Requires cmake 2.6.3 or newer (2.8.3 or newer is recommended).
#
#  Usage Linux:
#   $ source /absolute/path/to/the/bbndk/bbndk-env.sh
#   $ mkdir build
#   $ cd build
#   $ cmake .. -DCMAKE_TOOLCHAIN_FILE="../blackberry.toolchain.cmake" -DBLACKBERRY_ARCHITECTURE=arm -DFREEGLUT_GLES=ON -DFREEGLUT_BUILD_DEMOS=NO -DCMAKE_VERBOSE_MAKEFILE=TRUE -G "Eclipse CDT4 - Unix Makefiles"
#   $ make -j8
#
#  Usage Mac:
#   Same as the steps on Linux
#
#  Usage Windows:
#   > /absolute/path/to/the/bbndk/bbndk-env.bat
#   > mkdir build
#   > cd build
#   > cmake .. -DCMAKE_TOOLCHAIN_FILE="../blackberry.toolchain.cmake" -DBLACKBERRY_ARCHITECTURE=arm -DFREEGLUT_GLES=ON -DFREEGLUT_BUILD_DEMOS=NO -DCMAKE_VERBOSE_MAKEFILE=TRUE -G "Eclipse CDT4 - Unix Makefiles"
#   > make -j8
#

cmake_minimum_required( VERSION 2.6.3 )

if( DEFINED CMAKE_CROSSCOMPILING )
  # Subsequent toolchain loading is not really needed
  return()
endif()

set( BLACKBERRY_TOOLCHAIN_ROOT "$ENV{QNX_HOST}" )
set( BLACKBERRY_TARGET_ROOT "$ENV{QNX_TARGET}" )
set( CMAKE_SYSTEM_NAME Linux )
set( CMAKE_SYSTEM_VERSION 1 )

# Check for PlayBook
if( EXISTS "${BLACKBERRY_TARGET_ROOT}/x86/lib/gcc/4.4.2" )
  set( PLAYBOOK True )
endif()

# Check for for GCC 4.8.2
if( EXISTS "${BLACKBERRY_TARGET_ROOT}/x86/lib/gcc/4.8.2" )
  set( BB_GCC_482 True )
endif()

# STL version: by default gnustl_static will be used
set( BLACKBERRY_USE_STLPORT FALSE CACHE BOOL "Experimental: use stlport_static instead of gnustl_static")
mark_as_advanced( BLACKBERRY_USE_STLPORT )

# Detect host platform
set( TOOL_OS_SUFFIX "" )
if( CMAKE_HOST_APPLE )
 set( BLACKBERRY_NDK_HOST_SYSTEM_NAME "darwin-x86" )
elseif( CMAKE_HOST_WIN32 )
 set( BLACKBERRY_NDK_HOST_SYSTEM_NAME "windows" )
 set( TOOL_OS_SUFFIX ".exe" )
elseif( CMAKE_HOST_UNIX )
 set(BLACKBERRY_NDK_HOST_SYSTEM_NAME "linux-x86" )
else()
 message( FATAL_ERROR "Cross-compilation on your platform is not supported by this cmake toolchain" )
endif()

# Specify the cross compiler
set( CMAKE_C_COMPILER   "$ENV{QNX_HOST}/usr/bin/qcc${TOOL_OS_SUFFIX}"                CACHE PATH "gcc" )
set( CMAKE_CXX_COMPILER "$ENV{QNX_HOST}/usr/bin/qcc${TOOL_OS_SUFFIX}"                CACHE PATH "g++" )
set( CMAKE_ASM_COMPILER "$ENV{QNX_HOST}/usr/bin/qcc${TOOL_OS_SUFFIX}"                CACHE PATH "Assembler" )
if( CMAKE_VERSION VERSION_LESS 2.8.5 )
 set( CMAKE_ASM_COMPILER_ARG1 "-c" )
endif()

# There may be a way to make cmake reduce these TODO
if( BLACKBERRY_ARCHITECTURE STREQUAL "arm" )
 set( NEUTRINO_ARCH "v7" )
else()
 set( NEUTRINO_ARCH "" )
endif()
set( CMAKE_STRIP        "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}-strip${TOOL_OS_SUFFIX}"       CACHE PATH "strip" )
set( CMAKE_AR           "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}-ar${TOOL_OS_SUFFIX}"          CACHE PATH "archive" )
set( CMAKE_LINKER       "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}${NEUTRINO_ARCH}-ld${TOOL_OS_SUFFIX}"        CACHE PATH "linker" )
set( CMAKE_NM           "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}${NEUTRINO_ARCH}-nm${TOOL_OS_SUFFIX}"        CACHE PATH "nm" )
set( CMAKE_OBJCOPY      "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}${NEUTRINO_ARCH}-objcopy${TOOL_OS_SUFFIX}"   CACHE PATH "objcopy" )
set( CMAKE_OBJDUMP      "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}${NEUTRINO_ARCH}-objdump${TOOL_OS_SUFFIX}"   CACHE PATH "objdump" )
set( CMAKE_RANLIB       "$ENV{QNX_HOST}/usr/bin/nto${BLACKBERRY_ARCHITECTURE}-ranlib${TOOL_OS_SUFFIX}"      CACHE PATH "ranlib" )

# Installer
#if( APPLE )
# find_program( CMAKE_INSTALL_NAME_TOOL NAMES install_name_tool )
# if( NOT CMAKE_INSTALL_NAME_TOOL )
#  message( FATAL_ERROR "Could not find install_name_tool, please check your #installation." )
# endif()
# mark_as_advanced( CMAKE_INSTALL_NAME_TOOL )
# endif()

# Setup output directories
set( LIBRARY_OUTPUT_PATH_ROOT ${CMAKE_SOURCE_DIR}                                       CACHE PATH "root for library output, set this to change where android libs are installed to" )
set( CMAKE_INSTALL_PREFIX "${BLACKBERRY_TOOLCHAIN_ROOT}/user"                           CACHE STRING "path for installing" )

if( EXISTS "${CMAKE_SOURCE_DIR}/jni/CMakeLists.txt" )
 set( EXECUTABLE_OUTPUT_PATH "${LIBRARY_OUTPUT_PATH_ROOT}/bin/${ANDROID_NDK_ABI_NAME}"  CACHE PATH "Output directory for applications" )
else()
 set( EXECUTABLE_OUTPUT_PATH "${LIBRARY_OUTPUT_PATH_ROOT}/bin"                          CACHE PATH "Output directory for applications" )
endif()

# Includes
if( PLAYBOOK )
 list( APPEND BLACKBERRY_SYSTEM_INCLUDE_DIRS "${BLACKBERRY_TARGET_ROOT}/usr/include" )
else()
 list( APPEND BLACKBERRY_SYSTEM_INCLUDE_DIRS "${BLACKBERRY_TARGET_ROOT}/qnx6/usr/include" )
endif()

# Flags and preprocessor definitions
set( BB_USING_GCC_482 False )
if( PLAYBOOK )
  set( BLACKBERRY_COMP_DEF "-D__PLAYBOOK__" )
  set( BLACKBERRY_COMP_VERSION "4.4.2" )
else()
  set( BLACKBERRY_COMP_DEF "-D__QNX__" )
  if( BB_GCC_482 AND BLACKBERRY_USE_GCC_4_8 )
    set( BLACKBERRY_COMP_VERSION "4.8.2" )
    set( BB_USING_GCC_482 True )
  else()
    set( BLACKBERRY_COMP_VERSION "4.6.3" )
  endif()
endif()
if( BLACKBERRY_ARCHITECTURE STREQUAL "arm" )
  set( BLACKBERRY_COMP_TARGET "gcc_ntoarmv7le" )
else()
  set( BLACKBERRY_COMP_TARGET "gcc_ntox86" )
endif()
set( BLACKBERRY_CXX_COMP_LIB "" )
if( BLACKBERRY_DINKUM )
  set( DINKUM 1 )
  if( BB_USING_GCC_482 )
    set( BLACKBERRY_COMP_TARGET "${BLACKBERRY_COMP_TARGET}_cpp" )
  else()
    set( BLACKBERRY_CXX_COMP_LIB "-Y_cpp" )
  endif()
else()
  set( DINKUM 0 )
  if( BB_USING_GCC_482 )
    set( BLACKBERRY_COMP_TARGET "${BLACKBERRY_COMP_TARGET}_gpp" )
  else()
    set( BLACKBERRY_CXX_COMP_LIB "-Y_gpp" )
  endif()
endif()
set( BLACKBERRY_CC_FLAGS  " -V${BLACKBERRY_COMP_VERSION},${BLACKBERRY_COMP_TARGET} ${BLACKBERRY_COMP_DEF}" )
set( BLACKBERRY_CXX_FLAGS " -V${BLACKBERRY_COMP_VERSION},${BLACKBERRY_COMP_TARGET} ${BLACKBERRY_CXX_COMP_LIB} ${BLACKBERRY_COMP_DEF}" )
set( BLACKBERRY 1 )

# NDK flags
if( DINKUM )
  set( CMAKE_CXX_FLAGS "${BLACKBERRY_CXX_FLAGS} -DBLACKBERRY_DINKUM=1" )
  set( CMAKE_C_FLAGS "${BLACKBERRY_CC_FLAGS} -DBLACKBERRY_DINKUM=1" )
else()
  set( CMAKE_CXX_FLAGS "${BLACKBERRY_CXX_FLAGS}" )
  set( CMAKE_C_FLAGS "${BLACKBERRY_CC_FLAGS}" )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions" )

# Release and Debug flags
if( BLACKBERRY_ARCHITECTURE STREQUAL "arm" )
 set( CMAKE_CXX_FLAGS_RELEASE "-mthumb -O3" )
 set( CMAKE_C_FLAGS_RELEASE   "-mthumb -O3" )
 set( CMAKE_CXX_FLAGS_DEBUG   "-marm -Os -finline-limit=64" )
 set( CMAKE_C_FLAGS_DEBUG     "-marm -Os -finline-limit=64" )
else()
 set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=i486" )
 set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i486" )
endif()

# Cache flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "c++ flags" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "c flags" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "c++ Release flags" )
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "c Release flags" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "c++ Debug flags" )
set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "c Debug flags" )
set( CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "linker flags" )
SET( CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" CACHE STRING "linker flags")
SET( CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" CACHE STRING "linker flags")
set( CMAKE_MODULE_LINKER_FLAGS "" CACHE STRING "linker flags" )
set( CMAKE_EXE_LINKER_FLAGS "-lstdc++" CACHE STRING "linker flags" )

# Finish flags
set( BLACKBERRY_CXX_FLAGS    "${BLACKBERRY_CXX_FLAGS}"    CACHE INTERNAL "Extra BlackBerry compiler flags")
set( BLACKBERRY_LINKER_FLAGS "${BLACKBERRY_LINKER_FLAGS}" CACHE INTERNAL "Extra BlackBerry linker flags")
set( CMAKE_CXX_FLAGS  "${BLACKBERRY_CXX_FLAGS} ${CMAKE_CXX_FLAGS}" )
set( CMAKE_C_FLAGS    "${BLACKBERRY_CXX_FLAGS} ${CMAKE_C_FLAGS}" )

# Global flags for cmake client scripts to change behavior
set( BLACKBERRY True )
# Find the Target environment 
set( CMAKE_FIND_ROOT_PATH "${CMAKE_SOURCE_DIR}" "${BLACKBERRY_TARGET_ROOT}"  "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_PREFIX}/share" )
# Search for libraries and includes in the ndk toolchain
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

# Macro to find packages on the host OS
macro( find_host_package )
 set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
 set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
 set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )
 if( CMAKE_HOST_WIN32 )
  SET( WIN32 1 )
  SET( UNIX )
 elseif( CMAKE_HOST_APPLE )
  SET( APPLE 1 )
  SET( UNIX )
 endif()
 find_package( ${ARGN} )
 SET( WIN32 )
 SET( APPLE )
 SET( UNIX 1 )
 set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
 set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
 set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
endmacro()

# Macro to find programs on the host OS
macro( find_host_program )
 set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
 set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
 set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )
 if( CMAKE_HOST_WIN32 )
  SET( WIN32 1 )
  SET( UNIX )
 elseif( CMAKE_HOST_APPLE )
  SET( APPLE 1 )
  SET( UNIX )
 endif()
 find_program( ${ARGN} )
 SET( WIN32 )
 SET( APPLE )
 SET( UNIX 1 )
 set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
 set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
 set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
endmacro()

# We are doing cross compiling, reset the OS information of the Building system
UNSET( APPLE )
UNSET( WIN32 )
UNSET( UNIX )
