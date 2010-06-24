--[[
Must manually generate the following first:
* Documents/web, generated with Oxygen template

May also generate the following:
* Documents/tutorials.pdf, generated with Oxygen template
* Documents/kindleTutorials.pdf, generated with Oxygen template
]]--

require "lfs"

local destDir, hgChangelist, versionNum = ...

--local test = {...}
--print(#test, ...)
assert(#({...}) == 3, "Not enough commandline parameters.");

lfs.mkdir(destDir);


-------------------------------------------
-- Use the other Lua script to copy the HTML to the destination.
local CopyWebsite = assert(loadfile("CopyWebsite.lua"));
CopyWebsite(destDir .. "html\\");


--------------------------------------------
-- Copy other files.
os.execute(string.format([[copy "documents\TutorialsPrint.pdf" "%s\"]], destDir));
os.execute(string.format([[copy "documents\TutorialsKindle.pdf" "%s\"]], destDir));
os.execute(string.format([[copy "documents\TutorialsComp.pdf" "%s\"]], destDir));

------------------------------------------
-- Use Mercurial to get a version in the destination directory.
local clone = [[hg archive -r "%s" "%s\"]];
clone = clone:format(hgChangelist, destDir);

print(clone);
os.execute(clone);

-------------------------------------------
-- Generate the ancillary README and index.html files.








