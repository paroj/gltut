
function WriteParamsToFile(hFile, params)
	for param, value in pairs(params) do
		hFile:write([[    <xsl:param name="]],
			param,
			[[">]],
			value,
			[[</xsl:param>]],
			"\n");
	end
end

function ToUnix(convString)
	return string.gsub(convString, "%\\", "/");
end


