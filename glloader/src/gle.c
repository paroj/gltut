
#include <stdlib.h>
#include <string.h>
#include "gle_gl_ext.h"
#include "glloader/gle.h"

#ifdef WIN32
#include <windows.h>
#include "wgle_ext.h"
#endif

static StrToExtMap *GetExtEntry(const char *strExtensionName, StrToExtMap *pMapArray, int iNumEntries)
{
	int iLoop;
	StrToExtMap *pCurrLoc = pMapArray;
	for(iLoop = 0; iLoop < iNumEntries; iLoop++, pCurrLoc++)
	{
		if(_stricmp(strExtensionName, pCurrLoc->strExtensionName) == 0)
			return pCurrLoc;
	}

	return NULL;
}

static void ProcExt(StrToExtMap *pMapLoc)
{
	if(pMapLoc)
	{
		//Only try to load the extension if the extension variable is not set.
		if(!(*pMapLoc->pExtensionVariable))
		{
			if(pMapLoc->LoadExtension)
				*pMapLoc->pExtensionVariable = pMapLoc->LoadExtension();
			else
				*pMapLoc->pExtensionVariable = 1;
		}
	}
}

static void ProcExtFromExtString(const char *strExtList, StrToExtMap *pMapArray, int iNumEntries)
{
	size_t iExtListLen = strlen(strExtList);
	const char *strExtListEnd = strExtList + iExtListLen;
	const char *strCurrPos = strExtList;
	char strWorkBuff[256];

	while(*strCurrPos)
	{
		//Get the extension at our position.
		int iStrLen = 0;
		StrToExtMap *pMapLoc = NULL;
		const char *strEndStr = strchr(strCurrPos, ' ');
		int iStop = 0;
		if(strEndStr == NULL)
		{
			strEndStr = strExtListEnd;
			iStop = 1;
		}

		iStrLen = (int)((ptrdiff_t)strEndStr - (ptrdiff_t)strCurrPos);

		if(iStrLen > 255)
			return;

		strncpy(strWorkBuff, strCurrPos, iStrLen);
		strWorkBuff[iStrLen] = '\0';

		ProcExt(GetExtEntry(strWorkBuff, pMapArray, iNumEntries));

		strCurrPos = strEndStr + 1;
		if(iStop) break;
	}
}

//This will load the extension.
static void ProcExtFromList()
{
	GLint iLoop;
	GLint iNumExtensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = glGetStringi(GL_EXTENSIONS, iLoop);
		ProcExt(GetExtEntry(strExtensionName, gleIntExtensionMap, gleIntExtensionMapSize));
	}
}

static void GetGLVersion(int *pOutMajor, int *pOutMinor)
{
	const char *strVersion = NULL;
	const char *strDotPos = NULL;
	int iLength = 0;
	char strWorkBuff[10];
	*pOutMinor = 0;
	*pOutMajor = 0;

	strVersion = glGetString(GL_VERSION);
	strDotPos = strchr(strVersion, '.');
	if(!strDotPos)
		return;

	iLength = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
	strncpy(strWorkBuff, strVersion, iLength);
	strWorkBuff[iLength] = '\0';

	*pOutMajor = atoi(strWorkBuff);
	strDotPos = strchr(strVersion + iLength + 1, ' ');
	if(!strDotPos)
	{
		//No extra data. Take the whole rest of the string.
		strcpy(strWorkBuff, strVersion + iLength + 1);
	}
	else
	{
		//Copy only up until the space.
		int iLengthMinor = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
		iLengthMinor = iLengthMinor - (iLength + 1);
		strncpy(strWorkBuff, strVersion + iLength + 1, iLengthMinor);
		strWorkBuff[iLengthMinor] = '\0';
	}

	*pOutMinor = atoi(strWorkBuff);
}

int CheckCompatibilityExt()
{
	int iLoop = 0;
	int iNumExtensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = glGetStringi(GL_EXTENSIONS, iLoop);
		if(_stricmp(strExtensionName, "GL_ARB_compatibility") == 0)
		{
			return 1;
		}
	}

	return 0;
}

static int iMajorVersion = 0;
static int iMinorVersion = 0;

int gleLoadFunctions()
{
	int eCurrLoadStatus = GLE_LOAD_FUNCTIONS_ALL;

	iMajorVersion = 0;
	iMinorVersion = 0;

	//Clear the extensions, in case we loaded already.
	gleIntClear();

	//Get the base functions that we need just to process OpenGL.
	gleIntLoadBaseFuncs();

	//Get the version numbers.
	GetGLVersion(&iMajorVersion, &iMinorVersion);

	if(iMajorVersion < 3)
	{
		//Load the 2.1 core.
		if(!gleIntLoad_Version_2_1()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
	}
	else if(iMajorVersion == 3)
	{
		switch(iMinorVersion)
		{
		case 0:
			if(!gleIntLoad_Version_3_0()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
			break;
		case 1:
			//Check the ARB_compatibility extension.
			if(CheckCompatibilityExt())
			{
				if(!gleIntLoad_Version_3_1_Comp()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
			}
			else
			{
				if(!gleIntLoad_Version_3_1()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
			}
			break;
		default:
			{
				int iProfileMask = 0;
				glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &iProfileMask);
				if(iProfileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
				{
					if(!gleIntLoad_Version_3_2_Comp()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
				}
				else
				{
					if(!gleIntLoad_Version_3_2()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
				}
			}
			break;
		}
	}
	else
	{
		int iProfileMask = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &iProfileMask);
		if(iProfileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
		{
			if(!gleIntLoad_Version_3_2_Comp()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
		}
		else
		{
			if(!gleIntLoad_Version_3_2()) eCurrLoadStatus = GLE_LOAD_FUNCTIONS_SOME;
		}
	}

	//Now, process the extensions.
	//Use different methods if glGetStringi is available.
	if(iMajorVersion < 3)
	{
		ProcExtFromExtString(glGetString(GL_EXTENSIONS), gleIntExtensionMap, gleIntExtensionMapSize);
	}
	else
	{
		ProcExtFromList();
	}

	return eCurrLoadStatus;
}

int gleGetMajorVersion() { return iMajorVersion; }


int gleGetMinorVersion() { return iMinorVersion; }

int gleIsVersionGEQ( int iTestMajorVersion, int iTestMinorVersion )
{
	if(iMajorVersion > iTestMajorVersion) return 1;
	if(iMajorVersion < iTestMajorVersion) return 0;
	if(iMinorVersion >= iTestMinorVersion) return 1;
	return 0;
}

#ifdef WIN32
int gleLoadWinFunctions(void *hdc)
{
	HDC hDC = (HDC)hdc;

	wgleIntClear();
	wgleIntLoadBaseFuncs();

	gleIntLoadBaseFuncs();

	if(!wglGetExtensionsStringARB) return GLE_LOAD_FAILED;

	ProcExtFromExtString(wglGetExtensionsStringARB(hDC), wgleIntExtensionMap, wgleIntExtensionMapSize);

	return GLE_LOAD_FUNCTIONS_ALL;
}
#endif //WIN32


