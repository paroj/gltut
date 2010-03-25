// ==========================================================
// MNG Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
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

#include "FreeImage.h"
#include "Utilities.h"

#include "../LibMNG/libmng.h"
#include "../LibMNG/libmng_data.h"

// ==========================================================
// Plugin Interface
// ==========================================================

static int s_format_id;

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

typedef struct {
	FIBITMAP    *bitmap;    // pointer to the bitmap data
	FreeImageIO *io;        // pointer to the io functions
	fi_handle   file;	    // pointer to the file we're decoding
} mngstuff;

// ----------------------------------------------------------
//   Callbacks for the mng decoder
// ----------------------------------------------------------

mng_ptr
mymngalloc(mng_size_t size) {
	return (mng_ptr)calloc(1, size);
}

void
mymngfree(mng_ptr p, mng_size_t size) {
	free(p);
}

mng_bool
mymngopenstream(mng_handle mng) {
	// since the user is responsible for opening and closing the file,
	// we leave the default implementation open

	return MNG_TRUE;
}

mng_bool
mymngclosestream(mng_handle mng) {
	// since the user is responsible for opening and closing the file,
	// we leave the default implementation open

	return MNG_TRUE;
}

mng_bool
mymngreadstream(mng_handle mng, mng_ptr buffer, mng_uint32 size, mng_uint32 *bytesread) {
	mngstuff *mymng = (mngstuff *)mng_get_userdata(mng);

	*bytesread = mymng->io->read_proc(buffer, 1, size, mymng->file);

	return MNG_TRUE;
}

mng_bool
mymngprocessheader(mng_handle mng, mng_uint32 width, mng_uint32 height) {
	mngstuff *client_data = (mngstuff *)mng_get_userdata(mng);
	BYTE bHasAlpha = mng_get_alphadepth(mng);

#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
	if(bHasAlpha) {
		// allocate a bitmap with the given dimensions
		FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		client_data->bitmap = bitmap;
		// tell the mng decoder about our bit-depth choice
		mng_set_canvasstyle(mng, MNG_CANVAS_RGBA8);
	} else {
		// allocate a bitmap with the given dimensions
		FIBITMAP *bitmap = FreeImage_Allocate(width, height, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		client_data->bitmap = bitmap;
		// tell the mng decoder about our bit-depth choice
		mng_set_canvasstyle(mng, MNG_CANVAS_RGB8);
	}
#else
	if(bHasAlpha) {
		// allocate a bitmap with the given dimensions
		FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		client_data->bitmap = bitmap;
		// tell the mng decoder about our bit-depth choice
		mng_set_canvasstyle(mng, MNG_CANVAS_BGRA8);
	} else {
		// allocate a bitmap with the given dimensions
		FIBITMAP *bitmap = FreeImage_Allocate(width, height, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		client_data->bitmap = bitmap;
		// tell the mng decoder about our bit-depth choice
		mng_set_canvasstyle(mng, MNG_CANVAS_BGR8);
	}
#endif // FREEIMAGE_COLORORDER_RGB

	return client_data->bitmap ? MNG_TRUE : MNG_FALSE;
}

mng_ptr
mymnggetcanvasline(mng_handle mng, mng_uint32 line) {
	FIBITMAP *bitmap = ((mngstuff *)mng_get_userdata(mng))->bitmap;

	return FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - line - 1);
}

mng_bool
mymngrefresh(mng_handle mng, mng_uint32 x, mng_uint32 y, mng_uint32 w, mng_uint32 h) {
	return MNG_TRUE;
}

mng_uint32
mymnggetticks(mng_handle mng) {
	return 0;
}

mng_bool
mymngsettimer(mng_handle mng, mng_uint32 msecs) {
	return MNG_TRUE;
}

mng_bool
mymngerror(mng_handle mng, mng_int32 code, mng_int8 severity, mng_chunkid chunktype, mng_uint32 chunkseq, mng_int32 extra1, mng_int32 extra2, mng_pchar text) {
	char msg[256];
	if((code == MNG_SEQUENCEERROR) && (chunktype == MNG_UINT_TERM)) {
		// ignore sequence error for TERM
		return MNG_TRUE;
	}
	if(text) {
		// text can be null depending on compiler options
		sprintf(msg, "Error reported by libmng (%d)\r\n\r\n%s", code, text);
	} else {
		sprintf(msg, "Error %d reported by libmng", code);
	}
	FreeImage_OutputMessageProc(s_format_id, msg);
	return MNG_FALSE;
}

// ==========================================================
// Plugin Implementation
// ==========================================================

static const char * DLL_CALLCONV
Format() {
	return "MNG";
}

static const char * DLL_CALLCONV
Description() {
	return "Multiple Network Graphics";
}

static const char * DLL_CALLCONV
Extension() {
	return "mng";
}

static const char * DLL_CALLCONV
RegExpr() {
	return NULL;
}

static const char * DLL_CALLCONV
MimeType() {
	return "video/x-mng";
}

static BOOL DLL_CALLCONV
SupportsExportDepth(int depth) {
	return FALSE;
}

static BOOL DLL_CALLCONV 
SupportsExportType(FREE_IMAGE_TYPE type) {
	return FALSE;
}

// ----------------------------------------------------------

static void * DLL_CALLCONV
Open(FreeImageIO *io, fi_handle handle, BOOL read) {
	mngstuff *mymng = (mngstuff *)calloc(1, sizeof(*mymng));
	mymng->io = io;
	mymng->file = handle;	

	return mymng;
}

static void DLL_CALLCONV
Close(FreeImageIO *io, fi_handle handle, void *data) {
	free((mngstuff *)data);
}

// ----------------------------------------------------------

static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	mng_handle hmng = NULL;

	if (handle != NULL) {
		try {
			// allocate our stream data structure
			mngstuff *mymng = (mngstuff *)data;

			// set up the mng decoder for our stream
			hmng = mng_initialize(mymng, mymngalloc, mymngfree, MNG_NULL);

			if (hmng == MNG_NULL) {
				throw "could not initialize libmng";			
			}
			
			// set the colorprofile, lcms uses this
			mng_set_srgb(hmng, MNG_TRUE );
			// set white as background color
			WORD wRed, wGreen, wBlue;
			wRed = wGreen = wBlue = (255 << 8) + 255;
			mng_set_bgcolor(hmng, wRed, wGreen, wBlue);
			// if PNG Background is available, use it
			mng_set_usebkgd(hmng, MNG_TRUE );
			// no need to store chunks
			mng_set_storechunks(hmng, MNG_FALSE);
			// no need to wait: straight reading
			mng_set_suspensionmode(hmng, MNG_FALSE);

			// set the callbacks
			mng_setcb_errorproc(hmng, mymngerror);
			mng_setcb_openstream(hmng, mymngopenstream);
			mng_setcb_closestream(hmng, mymngclosestream);
			mng_setcb_readdata(hmng, mymngreadstream);
			mng_setcb_processheader(hmng, mymngprocessheader);
			mng_setcb_getcanvasline(hmng, mymnggetcanvasline);
			mng_setcb_refresh(hmng, mymngrefresh);
			mng_setcb_gettickcount(hmng, mymnggetticks);
			mng_setcb_settimer(hmng, mymngsettimer);
	
			// read in the bitmap
			mng_readdisplay(hmng);

			// read all bitmaps
			int retval = MNG_NOERROR;
			mng_datap pData = (mng_datap)hmng;
			while(pData->bReading) {
				retval = mng_display_resume(hmng);
				if((retval == MNG_NEEDTIMERWAIT) || (retval == MNG_FUNCTIONINVALID))
					break;
			}

			// temp store the newly created bitmap
			FIBITMAP *bitmap = mymng->bitmap;

			// cleanup and return the temp stored bitmap
			mng_cleanup(&hmng);

			return bitmap;

		} catch (const char *message) {
			FIBITMAP *bitmap = ((mngstuff *)mng_get_userdata(hmng))->bitmap;
			if(bitmap) {
				FreeImage_Unload(bitmap);
			}
			mng_cleanup(&hmng);
			FreeImage_OutputMessageProc(s_format_id, message);
		}
	}

	return NULL;
}	

// ==========================================================
//   Init
// ==========================================================

void DLL_CALLCONV
InitMNG(Plugin *plugin, int format_id) {
	s_format_id = format_id;

	plugin->format_proc = Format;
	plugin->description_proc = Description;
	plugin->extension_proc = Extension;
	plugin->regexpr_proc = RegExpr;
	plugin->open_proc = Open;
	plugin->close_proc = Close;
	plugin->pagecount_proc = NULL;
	plugin->pagecapability_proc = NULL;
	plugin->load_proc = Load;
	plugin->save_proc = NULL;
	plugin->validate_proc = NULL;
	plugin->mime_proc = MimeType;
	plugin->supports_export_bpp_proc = SupportsExportDepth;
	plugin->supports_export_type_proc = SupportsExportType;
	plugin->supports_icc_profiles_proc = NULL;	// not implemented yet;
}
