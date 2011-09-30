
solution "glload"
configurations {"Debug", "Release"}
defines {"_CRT_SECURE_NO_WARNINGS"}
defines {"_SCL_SECURE_NO_WARNINGS"}

dofile("glload.lua");

if(#os.matchfiles("Test/Test4.lua") ~= 0) then
	dofile("Test/Test4.lua");
end
