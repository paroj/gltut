## freeglut
add_subdirectory(freeglut)

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