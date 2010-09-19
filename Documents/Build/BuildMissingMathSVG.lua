require "lfs"

local theDir = ...;
theDir = theDir or ".";

for filename in lfs.dir(theDir) do
	if(filename:match("%.mathml$")) then
		local outname = filename:match("(.+)%.mathml$") .. ".svg";
		if(not lfs.attributes(outname)) then
			local cmd = {};
			cmd[#cmd + 1] = "python";
			cmd[#cmd + 1] = [["\Projects\XMLTools\Python26\SVGMath\math2svg.py"]];
			cmd[#cmd + 1] = "-o";
			cmd[#cmd + 1] = [["]] .. outname .. [["]];
			cmd[#cmd + 1] = [["]] .. filename .. [["]];

			print(table.concat(cmd, " "));
			os.execute(table.concat(cmd, " "));
		end
	end
end
