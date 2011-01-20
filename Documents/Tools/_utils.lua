

function ConstructSVGName(scriptName, suffix)
	local filename = scriptName:match("Gen(.*)%.lua");
	if(suffix) then
		return filename .. suffix .. ".svg";
	end
	return filename .. ".svg";
end

function StandardArrowheadPath()
	local arrowheadPath = SvgWriter.Path();
	arrowheadPath:M{10, 4}:L{0, 0}:L{0, 8}:Z();
	return arrowheadPath;
end

function WriteStandardArrowhead(writer, name, styles)
	writer:BeginMarker({10, 8}, {10, 4}, "auto", true, nil, name);
		writer:Path(StandardArrowheadPath(), styles);
	writer:EndMarker();
end

function WriteTipArrowhead(writer, name, styles)
	writer:BeginMarker({10, 8}, {0, 4}, "auto", true, nil, name);
		writer:Path(StandardArrowheadPath(), styles);
	writer:EndMarker();
end
