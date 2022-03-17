## freeglut
file(GLOB freeglut_SRCS freeglut/src/*.c)
add_library(freeglut STATIC ${freeglut_SRCS})
target_include_directories(freeglut PUBLIC freeglut/include freeglut)
target_compile_definitions(freeglut PUBLIC -DFREEGLUT_STATIC -DFREEGLUT_LIB_PRAGMAS=0)
if(UNIX)
    target_compile_definitions(freeglut PRIVATE -DHAVE_CONFIG_H)
    execute_process(COMMAND sh ./configure WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/freeglut)
else()
    target_link_libraries(freeglut PRIVATE winmm)
endif()

## glload
add_library(glload STATIC 
    glload/source/gl_load_cpp.cpp
    glload/source/gl_load.c)
target_include_directories(glload PUBLIC glload/include)

## glimg
file(GLOB glimg_SRCS glimg/source/*.cpp)
add_library(glimg STATIC 
    ${glimg_SRCS}
    glimg/source/stb_image.c)
target_include_directories(glimg PUBLIC glimg/include)
target_link_libraries(glimg PRIVATE glload)

## glutil
file(GLOB glutil_SRCS glutil/source/*.cpp)
add_library(glutil STATIC ${glutil_SRCS})
target_include_directories(glutil PUBLIC glutil/include glm)
target_link_libraries(glutil PRIVATE glimg glload)