
local filename = ...;

local outname = filename:match("(.+)%.dotgraph$") .. ".svg";

local cmd = {};
cmd[#cmd + 1] = "dot.exe";
cmd[#cmd + 1] = [[-Tsvg]];
--cmd[#cmd + 1] = [[-Kneato]];
cmd[#cmd + 1] = [["-o]] .. outname .. [["]];
cmd[#cmd + 1] = [["]] .. filename .. [["]];

print(table.concat(cmd, " "));
os.execute(table.concat(cmd, " "));
