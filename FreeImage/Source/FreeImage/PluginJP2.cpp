// ==========================================================
// JPEG2000 JP2 file format Loader and Writer
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

#include "FreeImage.h"
#include "Utilities.h"
#include "../LibOpenJPEG/openjpeg.h"

// ==========================================================
// Plugin Interface
// ==========================================================

static int s_format_id;

// ==========================================================
// Helper functions (see J2KHelper.cpp)
// ==========================================================

FIBITMAP* J2KImageToFIBITMAP(int format_id, const opj_image_t *image);
opj_image_t* FIBITMAPToJ2KImage(int format_id, FIBITMAP *dib, const opj_cparameters_t *parameters);

// ==========================================================
// Internal functions
// ==========================================================

/**
OpenJPEG Error callback 
*/
static void jp2_error_callback(const char *msg, void *client_data) {
	FreeImage_OutputMessageProc(s_format_id, "Error: %s", msg);
}
/**
OpenJPEG Warning callback 
*/
static void jp2_warning_callback(const char *msg, void *client_data) {
	FreeImage_OutputMessageProc(s_format_id, "Warning: %s", msg);
}

// ==========================================================
// Plugin Implementation
// ==========================================================

static const char * DLL_CALLCONV
Format() {
	return "JP2";
}

static const char * DLL_CALLCONV
Description() {
	return "JPEG-2000 File Format";
}

static const char * DLL_CALLCONV
Extension() {
	return "jp2";
}

static const char * DLL_CALLCONV
RegExpr() {
	return NULL;
}

static const char * DLL_CALLCONV
MimeType() {
	return "image/jp2";
}

static BOOL DLL_CALLCONV
Validate(FreeImageIO *io, fi_handle handle) {
	BYTE jp2_signature[] = { 0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50, 0x20, 0x20, 0x0D, 0x0A, 0x87, 0x0A };
	BYTE signature[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	long tell = io->tell_proc(handle);
	io->read_proc(signature, 1, sizeof(jp2_signature), handle);
	io->seek_proc(handle, tell, SEEK_SET);

	return (memcmp(jp2_signature, signature, sizeof(jp2_signature)) == 0);
}

static BOOL DLL_CALLCONV
SupportsExportDepth(int depth) {
	return (
		(depth == 8) ||
		(depth == 24) || 
		(depth == 32)
	);
}

static BOOL DLL_CALLCONV 
SupportsExportType(FREE_IMAGE_TYPE type) {
	return (
		(type == FIT_BITMAP)  ||
		(type == FIT_UINT16)  ||
		(type == FIT_RGB16) || 
		(type == FIT_RGBA16)
	);
}

// ----------------------------------------------------------

static void * DLL_CALLCONV
Open(FreeImageIO *io, fi_handle handle, BOOL read) {
	return NULL;
}

static void DLL_CALLCONV
Close(FreeImageIO *io, fi_handle handle, void *data) {
}

// ----------------------------------------------------------

static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	if (handle) {
		opj_dparameters_t parameters;	// decompression parameters 
		opj_event_mgr_t event_mgr;		// event manager 
		opj_image_t *image = NULL;		// decoded image 

		BYTE *src = NULL; 
		long file_length;

		opj_dinfo_t* dinfo = NULL;	// handle to a decompressor 
		opj_cio_t *cio = NULL;

		FIBITMAP *dib = NULL;

		// check the file format
		if(!Validate(io, handle)) {
			return NULL;
		}

		// configure the event callbacks
		memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
		event_mgr.error_handler = jp2_error_callback;
		event_mgr.warning_handler = jp2_warning_callback;
		event_mgr.info_handler = NULL;

		// set decoding parameters to default values 
		opj_set_default_decoder_parameters(&parameters);

		try {
			// read the input file and put it in memory

			long start_pos = io->tell_proc(handle);
			io->seek_proc(handle, 0, SEEK_END);
			file_length = io->tell_proc(handle) - start_pos;
			io->seek_proc(handle, start_pos, SEEK_SET);
			src = (BYTE*)malloc(file_length * sizeof(BYTE));
			if(!src) {
				throw FI_MSG_ERROR_MEMORY;
			}
			if(io->read_proc(src, 1, file_length, handle) < 1) {
				throw "Error while reading input stream";
			}

			// decode the JPEG-2000 file

			// get a decoder handle 
			dinfo = opj_create_decompress(CODEC_JP2);
			
			// catch events using our callbacks
			opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, NULL);			

			// setup the decoder decoding parameters using user parameters 
			opj_setup_decoder(dinfo, &parameters);

			// open a byte stream 
			cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

			// decode the stream and fill the image structure 
			image = opj_decode(dinfo, cio);
			if(!image) {
				throw "Failed to decode image!\n";
			}
			
			// close the byte stream 
			opj_cio_close(cio);
			cio = NULL;

			// free the memory containing the code-stream 
			free(src);
			src = NULL;

			// free the codec context
			opj_destroy_decompress(dinfo);

			// create output image 
			dib = J2KImageToFIBITMAP(s_format_id, image);
			if(!dib) throw "Failed to import JPEG2000 image";

			// free image data structure
			opj_image_destroy(image);

			return dib;

		} catch (const char *text) {
			if(src) free(src);
			if(dib) FreeImage_Unload(dib);
			// free remaining structures
			opj_destroy_decompress(dinfo);
			opj_image_destroy(image);
			// close the byte stream
			if(cio) opj_cio_close(cio);

			FreeImage_OutputMessageProc(s_format_id, text);

			return NULL;
		}
	}

	return NULL;
}

static BOOL DLL_CALLCONV
Save(FreeImageIO *io, FIBITMAP *dib, fi_handle handle, int page, int flags, void *data) {
	if ((dib) && (handle)) {
		BOOL bSuccess;
		opj_cparameters_t parameters;		// compression parameters 
		opj_event_mgr_t event_mgr;			// event manager 
		opj_image_t *image = NULL;			// image to encode
		opj_cinfo_t* cinfo = NULL;			// codec context
		opj_cio_t *cio = NULL;				// memory byte stream

		// configure the event callbacks
		memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
		event_mgr.error_handler = jp2_error_callback;
		event_mgr.warning_handler = jp2_warning_callback;
		event_mgr.info_handler = NULL;

		// set encoding parameters to default values
		opj_set_default_encoder_parameters(&parameters);

		parameters.tcp_numlayers = 0;
		// if no rate entered, apply a 16:1 rate by default
		if(flags == JP2_DEFAULT) {
			parameters.tcp_rates[0] = (float)16;
		} else {
			// for now, the flags parameter is only used to specify the rate
			parameters.tcp_rates[0] = (float)flags;
		}
		parameters.tcp_numlayers++;
		parameters.cp_disto_alloc = 1;

		try {
			// convert the dib to a OpenJPEG image
			image = FIBITMAPToJ2KImage(s_format_id, dib, &parameters);
			if(!image) return FALSE;

			// encode the destination image

			// get a J2K compressor handle
			cinfo = opj_create_compress(CODEC_JP2);

			// catch events using our callbacks
			opj_set_event_mgr((opj_common_ptr)cinfo, &event_mgr, NULL);			

			// setup the encoder parameters using the current image and using user parameters
			opj_setup_encoder(cinfo, &parameters, image);

			// open a byte stream for writing, allocate memory for all tiles
			cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

			// encode the image
			bSuccess = opj_encode(cinfo, cio, image, NULL/*parameters.index*/);
			if (!bSuccess) {
				throw "Failed to encode image";
			}
			int codestream_length = cio_tell(cio);

			// write the buffer to user's IO handle
			io->write_proc(cio->buffer, 1, codestream_length, handle);

			// close and free the byte stream 
			opj_cio_close(cio);

			// free remaining compression structures
			opj_destroy_compress(cinfo);
			
			// free image data
			opj_image_destroy(image);

			return TRUE;

		} catch (const char *text) {
			if(cio) opj_cio_close(cio);
			if(cinfo) opj_destroy_compress(cinfo);
			if(image) opj_image_destroy(image);
			FreeImage_OutputMessageProc(s_format_id, text);
			return FALSE;
		}
	}

	return FALSE;
}

// ==========================================================
//   Init
// ==========================================================

void DLL_CALLCONV
InitJP2(Plugin *plugin, int format_id) {
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
	plugin->save_proc = Save;
	plugin->validate_proc = Validate;
	plugin->mime_proc = MimeType;
	plugin->supports_export_bpp_proc = SupportsExportDepth;
	plugin->supports_export_type_proc = SupportsExportType;
	plugin->supports_icc_profiles_proc = NULL;
}
