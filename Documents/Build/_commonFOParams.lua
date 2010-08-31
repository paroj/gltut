local params = ...;
params = params or {};

params["fop1.extensions"] = "1";
params["generate.toc"] = "appendix  toc,title article/appendix  nop article   toc,title book      toc,title chapter   toc,title part      toc,title preface   toc,title qandadiv  toc qandaset  toc reference toc,title sect1     toc sect2     toc sect3     toc sect4     toc sect5     toc section   toc set       toc,title"

return params;
