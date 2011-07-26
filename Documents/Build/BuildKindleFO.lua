
require "lfs"
require "_util"

local data = dofile("_buildConfig.lua");

local outputDir = ...;
outputDir = outputDir or "..\\fo\\";
local foFilename = "..\\kindle.fo";

--Parameters
local params = {}
params["body.font.master"] = "10";
params["body.start.indent"] = "0pt";
params["page.height"] = "4.79in";
params["page.height.portrait"] = "4.79in";
params["page.width"] = "3.59in";
params["page.width.portrait"] = "3.59in";
params["page.margin.top"] = "0in";
params["page.margin.bottom"] = "0in";
params["page.margin.inner"] = "0in";
params["page.margin.outer"] = "0in";
params["title.margin.left"] = "0pt";
--params["highlight.source"] = "1";
--params["highlight.xslthl.config"] = "file:highlighting/xslthl-config.xml";


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
hFile:write([[    <xsl:import href="fo-common.xsl"/>]], "\n");

WriteParamsToFile(hFile, dofile("_commonParams.lua"));
WriteParamsToFile(hFile, dofile("_commonFOParams.lua"));
WriteParamsToFile(hFile, params);

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

local finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);


command = {};
command[#command + 1] = data.fopBatch
command[#command + 1] = "-fo"
command[#command + 1] = "\"" .. foFilename .. "\""
command[#command + 1] = "-pdf"
command[#command + 1] = "\"" .. outputDir .. "TutorialsKindle.pdf\""

finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);




