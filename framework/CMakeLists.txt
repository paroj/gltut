file(GLOB framework_SRCS "*.cpp")
add_library(framework STATIC ${framework_SRCS})
target_include_directories(framework PUBLIC . ${CMAKE_SOURCE_DIR}/glsdk/glm)
target_link_libraries(framework
    PUBLIC glload glimg glutil freeglut OpenGL::GL
)
if(UNIX AND NOT APPLE)
    target_link_libraries(framework PRIVATE X11)
endif()