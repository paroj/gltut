
solution "glimg"
configurations {"Debug", "Release"}
defines {"_CRT_SECURE_NO_WARNINGS"}
defines {"_SCL_SECURE_NO_WARNINGS"}

dofile("glimg.lua")
dofile("../glload/glload.lua");
dofile("Test/Test4.lua");
