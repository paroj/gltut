--[[Always include this at the bottom of any use of headerFunc.]]

return [[
#ifdef GLE_REMOVE_APIENTRY
	#undef GLE_REMOVE_APIENTRY
	#undef APIENTRY
#endif //GLE_REMOVE_APIENTRY
]]