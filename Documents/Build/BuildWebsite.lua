
require "lfs"
require "_util"

local data = dofile("_buildConfig.lua");

local outputDir = ...;
outputDir = outputDir or "../web/";

--Parameters
local params = {}
params["base.dir"] = ToUnix(outputDir);
params["chunk.quietly"] = "1";
params["chunker.output.encoding"] = "UTF-8";
params["html.stylesheet"] = "chunked.css";
params["ignore.image.scaling"] = "1";

--Auto-generate the main specialization file.
local filename = "website.xsl";

local hFile = io.open(filename, "w");
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
    <script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
    <script id="MathJax-script" async="async" src="https://cdn.jsdelivr.net/npm/mathjax@3.0.1/es5/tex-mml-chtml.js"></script>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/github-fork-ribbon-css/0.2.0/gh-fork-ribbon.min.css" />
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/10.1.1/styles/zenburn.min.css" />
        <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/10.1.1/highlight.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/10.1.1/languages/glsl.min.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
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
        <a class="github-fork-ribbon left-top" href="https://github.com/paroj/gltut" title="Fork me on GitHub">Fork me on GitHub</a>
	</xsl:template>
]]);


hFile:write([[</xsl:stylesheet> 
]]);

hFile:close();

--Create the command line.
command = {};
command[#command + 1] = "xsltproc"
command[#command + 1] = "--xinclude"
command[#command + 1] = filename
command[#command + 1] = "\"../Tutorials.xml\""

finalCmd = table.concat(command, " ");
print(finalCmd);
print("");

os.execute(finalCmd);
