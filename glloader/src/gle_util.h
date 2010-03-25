
#ifndef GLE_UTIL_H
#define GLE_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef int (*PFN_LOADEXTENSION)();

typedef struct StrToExtMap_s
{
	char *strExtensionName;
	int *pExtensionVariable;
	PFN_LOADEXTENSION LoadExtension;
} StrToExtMap;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //GLE_UTIL_H