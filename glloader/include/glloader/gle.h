
#ifndef GLE_FILE_H
#define GLE_FILE_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


typedef enum GleLoadSucceeded
{
	GLE_LOAD_FUNCTIONS_ALL,
	GLE_LOAD_FUNCTIONS_SOME,
	GLE_LOAD_FAILED,
};

int gleLoadFunctions();

#ifdef WIN32
//Pass in a HDC as a void*.
int gleLoadWinFunctions(void *hdc);
#endif //WIN32

/**
This function retrieves the major GL version number. Only works after gleLoadFunctions has been called.
**/
int gleGetMajorVersion();

/**
This function retrieves the minor GL version number. Only works after gleLoadFunctions has been called.

\return Returns 0 if entirely successful.
**/
int gleGetMinorVersion();

///Returns non-zero if the current GL version is greater than or equal to the given version.
int gleIsVersionGEQ(int iMajorVersion, int iMinorVersion);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //GLE_FILE_H

