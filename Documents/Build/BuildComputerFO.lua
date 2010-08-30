
require "lfs"

local function ToUnix(convString)
	return string.gsub(convString, "%\\", "/");
end

local data = dofile("_buildConfig.lua");

local outputDir = ...;
outputDir = outputDir or "..\\fo\\";
local foFilename = "..\\computerfo.fo";

--Auto-generate the main specialization file.
local filename = "fo.xsl";

local hFile = io.open(filename, "wt");
hFile:write(
[[<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:s6hl="java:net.sf.xslthl.ConnectorSaxon6"
    xmlns:xslthl="http://xslthl.sf.net"
    extension-element-prefixes="s6hl xslthl">
]]);

hFile:write([[    <xsl:import href="]], ToUnix(data.docbookXSLBasepath .. "fo\\docbook.xsl"), "\"/>\n");

hFile:write([[    <xsl:import href="colorfo-highlights.xsl"/>]], "\n");

hFile:write([[</xsl:stylesheet> 
]]);

hFile:close();

--Create the command line.
local command = {};
command[#command + 1] = "java"
command[#command + 1] = "-cp"
command[#command + 1] = "\"" .. table.concat({data.saxonFilepath, data.xercesJars, data.xslthlFilepath}, ";") .. "\""
command[#command + 1] = "-Djavax.xml.parsers.DocumentBuilderFactory=org.apache.xerces.jaxp.DocumentBuilderFactoryImpl"
command[#command + 1] = "-Djavax.xml.parsers.SAXParserFactory=org.apache.xerces.jaxp.SAXParserFactoryImpl"
command[#command + 1] = "-Dorg.apache.xerces.xni.parser.XMLParserConfiguration=org.apache.xerces.parsers.XIncludeParserConfiguration"
command[#command + 1] = "com.icl.saxon.StyleSheet"
command[#command + 1] = "-o"
command[#command + 1] = "\"" .. foFilename .. "\""
command[#command + 1] = "\"..\\Tutorials.xml\""
command[#command + 1] = filename
command[#command + 1] = "toc.max.depth=2"
command[#command + 1] = "toc.section.depth=1"
command[#command + 1] = "funcsynopsis.style=ansi"
command[#command + 1] = "body.start.indent=2pc"
command[#command + 1] = "draft.mode=no"
command[#command + 1] = "fop1.extensions=1"
command[#command + 1] = "page.margin.bottom=0.25in"
command[#command + 1] = "page.margin.inner=0.25in"
command[#command + 1] = "page.margin.outer=0.25in"
command[#command + 1] = "page.margin.top=0.25in"
command[#command + 1] = "paper.type=USLetter"
command[#command + 1] = "body.start.indent=0pt"
--command[#command + 1] = "highlight.source=1"
--command[#command + 1] = "\"highlight.xslthl.config=file:highlighting/xslthl-config.xml\""

local finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);


command = {};
command[#command + 1] = data.fopBatch
command[#command + 1] = "-fo"
command[#command + 1] = "\"" .. foFilename .. "\""
command[#command + 1] = "-pdf"
command[#command + 1] = "\"" .. outputDir .. "computerfo.pdf\""

finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);




