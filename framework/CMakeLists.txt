# for apple support with our without cocoa so we know how to initialize opengl in framework.cpp
IF(FREEGLUT_COCOA)
    ADD_DEFINITIONS(-DUSE_COCOA=1)
ENDIF()

file(GLOB framework_SRCS "*.cpp")
add_library(framework STATIC ${framework_SRCS})
target_include_directories(framework PUBLIC . ${CMAKE_SOURCE_DIR}/glsdk/glm)
# is this the best way? isn't there a way to add this to glsdk/CMakeLists.txt where we are `add_subdirectory(freeglut)`
target_include_directories(framework PUBLIC . ${CMAKE_SOURCE_DIR}/glsdk/freeglut/include)
target_link_libraries(framework
    PUBLIC glload glimg glutil freeglut OpenGL::GL
)
if(UNIX AND NOT APPLE)
    target_link_libraries(framework PRIVATE X11)
endif()