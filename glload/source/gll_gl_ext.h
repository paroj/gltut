#ifndef GLL_GL_EXT_H
#define GLL_GL_EXT_H


#include "gll_util.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



extern StrToExtMap gleIntExtensionMap[];
extern int gleIntExtensionMapSize;

void gleIntClear();

int gleIntLoad_Version_2_1();
int gleIntLoad_Version_3_0();
int gleIntLoad_Version_3_1();
int gleIntLoad_Version_3_1_Comp();
int gleIntLoad_Version_3_2();
int gleIntLoad_Version_3_2_Comp();
int gleIntLoad_Version_3_3();
int gleIntLoad_Version_3_3_Comp();
int gleIntLoad_Version_4_0();
int gleIntLoad_Version_4_0_Comp();
int gleIntLoad_Version_4_1();
int gleIntLoad_Version_4_1_Comp();

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //GLL_GL_EXT_H

