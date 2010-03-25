// ==========================================================
// FreeImage 3 Test Script
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================


#include "TestSuite.h"

void testSaveMemIO(const char *lpszPathName) {
	FIMEMORY *hmem = NULL; 

	// load a regular file
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(lpszPathName);
	FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, 0);
	
	// open a memory handle
	hmem = FreeImage_OpenMemory();

	// save the file to memory
	FreeImage_SaveToMemory(fif, dib, hmem, 0);

	// at this point, hmem contains the entire PNG data in memory. 
	// the amount of space used by the memory is equal to file_size
	long file_size = FreeImage_TellMemory(hmem);
	printf("File size : %ld\n", file_size);


	// its easy load an image from memory as well

	// seek to the start of the memory stream
	FreeImage_SeekMemory(hmem, 0L, SEEK_SET);
	
	// get the file type
	FREE_IMAGE_FORMAT mem_fif = FreeImage_GetFileTypeFromMemory(hmem, 0);
	
	// load an image from the memory handle 
	FIBITMAP *check = FreeImage_LoadFromMemory(mem_fif, hmem, 0);

	// save as a regular file
	FreeImage_Save(FIF_PNG, check, "dump.png", PNG_DEFAULT);

	// make sure to free the data since FreeImage_SaveToMemory 
	// will cause it to be malloc'd
	FreeImage_CloseMemory(hmem);

	FreeImage_Unload(check);
	FreeImage_Unload(dib);
}

	//you could also have image data in memory via some other method, and just set
	//fmh.data to point to it, and set both fmh.datalen and fmh.filelen to the
	//size of that data, then FreeImage_LoadFromMemory could load the image from that memory

void testLoadMemIO(const char *lpszPathName) {
	struct stat buf;
	int result;

	// get data associated with lpszPathName
	result = stat(lpszPathName, &buf);
	if(result == 0) {
		// allocate a memory buffer and load temporary data
		BYTE *mem_buffer = (BYTE*)malloc(buf.st_size * sizeof(BYTE));
		if(mem_buffer) {
			FILE *stream = fopen(lpszPathName, "rb");
			if(stream) {
				fread(mem_buffer, sizeof(BYTE), buf.st_size, stream);
				fclose(stream);

				// attach the binary data to a memory stream
				FIMEMORY *hmem = FreeImage_OpenMemory(mem_buffer, buf.st_size);

				// get the file type
				FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(hmem, 0);

				// load an image from the memory stream
				FIBITMAP *check = FreeImage_LoadFromMemory(fif, hmem, PNG_DEFAULT);

				// save as a regular file
				FreeImage_Save(FIF_PNG, check, "blob.png", PNG_DEFAULT);
				FreeImage_Unload(check);
				
				// close the stream
				FreeImage_CloseMemory(hmem);

			}
		}
		// user is responsible for freeing the data
		free(mem_buffer);
	}
}

void testAcquireMemIO(const char *lpszPathName) {
	FIMEMORY *hmem = NULL; 

	// load a regular file
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(lpszPathName);
	FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, 0);

	// open and allocate a memory stream
	hmem = FreeImage_OpenMemory();

	// save the file to memory
	FreeImage_SaveToMemory(FIF_PNG, dib, hmem, PNG_DEFAULT);

	FreeImage_Unload(dib);

	// get the buffer from the memory stream
	BYTE *mem_buffer = NULL;
	DWORD size_in_bytes = 0;

	FreeImage_AcquireMemory(hmem, &mem_buffer, &size_in_bytes);

	// save the buffer in a file stream
	FILE *stream = fopen("buffer.png", "wb");
	if(stream) {
		fwrite(mem_buffer, sizeof(BYTE), size_in_bytes, stream);
		fclose(stream);
	}

	// close and free the memory stream
	FreeImage_CloseMemory(hmem);

}

void testMemIO(const char *lpszPathName) {
	testSaveMemIO(lpszPathName);
	testLoadMemIO(lpszPathName);
	testAcquireMemIO(lpszPathName);
}

