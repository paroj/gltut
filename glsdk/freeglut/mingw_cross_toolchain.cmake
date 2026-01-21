# CMake toolchain file, cf. README.mingw_cross
SET(CMAKE_SYSTEM_NAME Windows)
IF("${GNU_HOST}" STREQUAL "")
	SET(GNU_HOST x86_64-w64-mingw32)
ENDIF()
SET(CMAKE_C_COMPILER  ${GNU_HOST}-gcc)
SET(CMAKE_RC_COMPILER ${GNU_HOST}-windres)
