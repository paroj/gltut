dofile("framework/framework.lua")

SetupSolution("AllTutorials")

local dirList = os.matchdirs("*");

for i, theDir in ipairs(dirList) do
    local filename = string.format("%s/tutorials.lua", theDir);
	if(os.isfile(filename)) then
		dofile(filename)
	end
end

