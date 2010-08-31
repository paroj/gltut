local params = ...;
params = params or {};

params["funcsynopsis.style"] = "ansi";
params["draft.mode"] = "no";
params["toc.max.depth"] = "2";
params["toc.section.depth"] = "1";

return params;