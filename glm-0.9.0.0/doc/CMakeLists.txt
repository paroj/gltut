set(NAME glm-doc)

file(GLOB ROOT_CPP src/*.cpp)
file(GLOB ROOT_XML src/*.xml)
file(GLOB ROOT_XSL src/*.xsl)

source_group("XML Files" FILES ${ROOT_XML})
source_group("XSL Files" FILES ${ROOT_XSL})

add_executable(${NAME} ${ROOT_CPP} ${ROOT_XML} ${ROOT_XSL})
