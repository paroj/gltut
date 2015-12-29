
require "lfs"
require "_util"

local data = dofile("_buildConfig.lua");

local outputDir = ...;
outputDir = outputDir or "../web/";

--Parameters
local params = {}
params["base.dir"] = ToUnix(outputDir);
params["chunk.quietly"] = "1";
params["html.stylesheet"] = "chunked.css";
params["ignore.image.scaling"] = "1";

--Auto-generate the main specialization file.
local filename = "website.xsl";

local hFile = io.open(filename, "wt");
hFile:write(
[[<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
]]);

hFile:write([[    <xsl:import href="]], ToUnix(data.docbookXSLBasepath .. "html/chunkfast.xsl"), "\"/>\n");

WriteParamsToFile(hFile, dofile("_commonParams.lua"));
WriteParamsToFile(hFile, params);

hFile:write([[
	<xsl:template name="system.head.content">
		<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
		<script type="text/javascript"
          src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=MML_HTMLorMML">
        </script>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/github-fork-ribbon-css/0.1.1/gh-fork-ribbon.min.css" />
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.0.0/styles/zenburn.min.css" />
        <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.0.0/highlight.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.0.0/languages/glsl.min.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
        <script>
            hljs.configure({"languages": ["c++", "glsl"]})
            $(document).ready(function() {
              $('pre').each(function(i, block) {
                hljs.highlightBlock(block);
              });
            });
        </script>
	</xsl:template>
	<xsl:template name="generate.html.title"/>
]]);

hFile:write([[
	<xsl:template name="user.footer.content">
        <div class="github-fork-ribbon-wrapper left">
            <div class="github-fork-ribbon">
                <a href="https://github.com/paroj/gltut">Fork me on GitHub</a>
            </div>
        </div>
	</xsl:template>
]]);


hFile:write([[</xsl:stylesheet> 
]]);

hFile:close();

--Create the command line.
command = {};
command[#command + 1] = "java"
command[#command + 1] = "-cp"
command[#command + 1] = "\"" .. table.concat({data.saxonFilepath, data.xercesJars}, ":") .. "\""
command[#command + 1] = "-Djavax.xml.parsers.DocumentBuilderFactory=org.apache.xerces.jaxp.DocumentBuilderFactoryImpl"
command[#command + 1] = "-Djavax.xml.parsers.SAXParserFactory=org.apache.xerces.jaxp.SAXParserFactoryImpl"
command[#command + 1] = "-Dorg.apache.xerces.xni.parser.XMLParserConfiguration=org.apache.xerces.parsers.XIncludeParserConfiguration"
command[#command + 1] = "com.icl.saxon.StyleSheet"
command[#command + 1] = "-o"
command[#command + 1] = "\"" .. outputDir .. "nothing.html\""
command[#command + 1] = "\"../Tutorials.xml\""
command[#command + 1] = filename

finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);
