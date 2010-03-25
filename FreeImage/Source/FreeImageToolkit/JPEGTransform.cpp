// ==========================================================
// JPEG lossless transformations
//
// Design and implementation by
// - Petr Pytelka (pyta@lightcomp.com)
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

extern "C" {
#define XMD_H
#undef FAR
#include <setjmp.h>

#include "../LibJPEG/jinclude.h"
#include "../LibJPEG/jpeglib.h"
#include "../LibJPEG/jerror.h"
#include "../LibJPEG/transupp.h"
}

#include "FreeImage.h"
#include "Utilities.h"

// ----------------------------------------------------------
//   IO filename handling
// ----------------------------------------------------------

typedef struct tagFilenameIO {
	const char *src_file;
	const char *dst_file;
	const wchar_t *wsrc_file;
	const wchar_t *wdst_file;
} FilenameIO;

// ----------------------------------------------------------
//   Error handling
// ----------------------------------------------------------

/**
	Receives control for a fatal error.  Information sufficient to
	generate the error message has been stored in cinfo->err; call
	output_message to display it.  Control must NOT return to the caller;
	generally this routine will exit() or longjmp() somewhere.
*/
METHODDEF(void)
ls_jpeg_error_exit (j_common_ptr cinfo) {
	// always display the message
	(*cinfo->err->output_message)(cinfo);

	// allow JPEG with a premature end of file
	if((cinfo)->err->msg_parm.i[0] != 13) {
	
		// let the memory manager delete any temp files before we die
		jpeg_destroy(cinfo);
		
		throw FIF_JPEG;
	}
}

/**
	Actual output of any JPEG message.  Note that this method does not know
	how to generate a message, only where to send it.
*/
METHODDEF(void)
ls_jpeg_output_message (j_common_ptr cinfo) {
	char buffer[JMSG_LENGTH_MAX];

	// create the message
	(*cinfo->err->format_message)(cinfo, buffer);
	// send it to user's message proc
	FreeImage_OutputMessageProc(FIF_JPEG, buffer);
}

// ----------------------------------------------------------
//   Main program
// ----------------------------------------------------------

static BOOL  
LosslessTransform(const FilenameIO *filenameIO, FREE_IMAGE_JPEG_OPERATION operation, const char *crop, BOOL perfect) {
	// We assume all-in-memory processing and can therefore use only a
	// single file pointer for sequential input and output operation
	FILE *fp = NULL;

	// check for UNICODE filenames - previous structure filling was done before
	bool bUseUnicode = filenameIO && filenameIO->wsrc_file && filenameIO->wdst_file;

	// Set up the jpeglib structures
	jpeg_decompress_struct srcinfo;
	jpeg_compress_struct dstinfo;
	jpeg_error_mgr jsrcerr, jdsterr;
	jvirt_barray_ptr *src_coef_arrays = NULL;
	jvirt_barray_ptr *dst_coef_arrays = NULL;
	// Support for copying optional markers from source to destination file
	JCOPY_OPTION copyoption;
	// Image transformation options
	jpeg_transform_info transfoptions;
	
	// Initialize structures
	memset(&srcinfo, 0, sizeof(srcinfo));
	memset(&jsrcerr, 0, sizeof(jsrcerr));
	memset(&jdsterr, 0, sizeof(jdsterr));
	memset(&dstinfo, 0, sizeof(dstinfo));
	memset(&transfoptions, 0, sizeof(transfoptions));
	
	// Copy all extra markers from source file
	copyoption = JCOPYOPT_ALL;
	
	// Set up default JPEG parameters
	transfoptions.force_grayscale = FALSE;
	transfoptions.crop = FALSE;

	// Select the transform option
	switch(operation) {
		case FIJPEG_OP_FLIP_H:		// horizontal flip
			transfoptions.transform = JXFORM_FLIP_H;
			break;
		case FIJPEG_OP_FLIP_V:		// vertical flip
			transfoptions.transform = JXFORM_FLIP_V;
			break;
		case FIJPEG_OP_TRANSPOSE:	// transpose across UL-to-LR axis
			transfoptions.transform = JXFORM_TRANSPOSE;
			break;
		case FIJPEG_OP_TRANSVERSE:	// transpose across UR-to-LL axis
			transfoptions.transform = JXFORM_TRANSVERSE;
			break;
		case FIJPEG_OP_ROTATE_90:	// 90-degree clockwise rotation
			transfoptions.transform = JXFORM_ROT_90;
			break;
		case FIJPEG_OP_ROTATE_180:	// 180-degree rotation
			transfoptions.transform = JXFORM_ROT_180;
			break;
		case FIJPEG_OP_ROTATE_270:	// 270-degree clockwise (or 90 ccw)
			transfoptions.transform = JXFORM_ROT_270;
			break;
		default:
		case FIJPEG_OP_NONE:		// no transformation
			transfoptions.transform = JXFORM_NONE;
			break;
	}
	// (perfect == TRUE) ==> fail if there is non-transformable edge blocks
	transfoptions.perfect = (perfect == TRUE) ? TRUE : FALSE;
	// Drop non-transformable edge blocks: trim off any partial edge MCUs that the transform can't handle.
	transfoptions.trim = TRUE;

	try {

		// Initialize the JPEG decompression object with default error handling
		srcinfo.err = jpeg_std_error(&jsrcerr);
		srcinfo.err->error_exit = ls_jpeg_error_exit;
		srcinfo.err->output_message = ls_jpeg_output_message;
		jpeg_create_decompress(&srcinfo);

		// Initialize the JPEG compression object with default error handling
		dstinfo.err = jpeg_std_error(&jdsterr);
		dstinfo.err->error_exit = ls_jpeg_error_exit;
		dstinfo.err->output_message = ls_jpeg_output_message;
		jpeg_create_compress(&dstinfo);

		// crop option
		if(crop != NULL) {
			if(!jtransform_parse_crop_spec(&transfoptions, crop)) {
				FreeImage_OutputMessageProc(FIF_JPEG, "Bogus crop argument %s", crop);
				throw(1);
			}
		}

		// Open the input file
		if(bUseUnicode) {
#ifdef _WIN32
			if((fp = _wfopen(filenameIO->wsrc_file, L"rb")) == NULL) {
				FreeImage_OutputMessageProc(FIF_JPEG, "Cannot open input file for reading");
			}
#else
			fp = NULL;
#endif // _WIN32
		} else {
			if((fp = fopen(filenameIO->src_file, "rb")) == NULL) {
				FreeImage_OutputMessageProc(FIF_JPEG, "Cannot open %s for reading", filenameIO->src_file);
			}
		}
		if(fp == NULL) {
			jpeg_destroy_compress(&dstinfo);
			jpeg_destroy_decompress(&srcinfo);
			return FALSE;
		}
		
		// Specify data source for decompression
		jpeg_stdio_src(&srcinfo, fp);
		
		// Enable saving of extra markers that we want to copy
		jcopy_markers_setup(&srcinfo, copyoption);
		
		// Read the file header
		jpeg_read_header(&srcinfo, TRUE);
		
		// Any space needed by a transform option must be requested before
		// jpeg_read_coefficients so that memory allocation will be done right

		// Fails right away if perfect flag is TRUE and transformation is not perfect
		if(transfoptions.perfect && 
			!jtransform_perfect_transform(srcinfo.image_width, srcinfo.image_height, 
			srcinfo.max_h_samp_factor * DCTSIZE, srcinfo.max_v_samp_factor * DCTSIZE, 
			transfoptions.transform)) {
			FreeImage_OutputMessageProc(FIF_JPEG, "Transformation is not perfect");
			throw(1);
		}
		// Prepare transformation workspace
		jtransform_request_workspace(&srcinfo, &transfoptions);
		
		// Read source file as DCT coefficients
		src_coef_arrays = jpeg_read_coefficients(&srcinfo);
		
		// Initialize destination compression parameters from source values
		jpeg_copy_critical_parameters(&srcinfo, &dstinfo);

		// Adjust destination parameters if required by transform options;
		// also find out which set of coefficient arrays will hold the output
		dst_coef_arrays = jtransform_adjust_parameters(&srcinfo, &dstinfo, src_coef_arrays, &transfoptions);
		
		// Close the input file.
		// Note: we assume that jpeg_read_coefficients consumed all input
		// until JPEG_REACHED_EOI, and that jpeg_finish_decompress will
		// only consume more while (! cinfo->inputctl->eoi_reached).
		// We cannot call jpeg_finish_decompress here since we still need the
		// virtual arrays allocated from the source object for processing.
		fclose(fp);

		// Open the output file
		if(bUseUnicode) {
#ifdef _WIN32
			if((fp = _wfopen(filenameIO->wdst_file, L"wb")) == NULL) {
				FreeImage_OutputMessageProc(FIF_JPEG, "Cannot open output file for writing");
			}
#else
			fp = NULL;
#endif // _WIN32
		} else {
			if((fp = fopen(filenameIO->dst_file, "wb")) == NULL) {
				FreeImage_OutputMessageProc(FIF_JPEG, "Cannot open %s for writing", filenameIO->dst_file);
			}
		}
		if(fp == NULL) {
			throw(1);
		}
		
		// Specify data destination for compression
		jpeg_stdio_dest(&dstinfo, fp);
		
		// Start compressor (note no image data is actually written here)
		jpeg_write_coefficients(&dstinfo, dst_coef_arrays);
		
		// Copy to the output file any extra markers that we want to preserve
		jcopy_markers_execute(&srcinfo, &dstinfo, copyoption);
		
		// Execute image transformation, if any
		jtransform_execute_transformation(&srcinfo, &dstinfo, src_coef_arrays, &transfoptions);
		
		// Finish compression and release memory
		jpeg_finish_compress(&dstinfo);
		jpeg_destroy_compress(&dstinfo);
		jpeg_finish_decompress(&srcinfo);
		jpeg_destroy_decompress(&srcinfo);
		
		// Close output file and return
		fclose(fp);
	}
	catch(...) {
		if(fp) fclose(fp);
		jpeg_destroy_compress(&dstinfo);
		jpeg_destroy_decompress(&srcinfo);
		return FALSE;
	}

	return TRUE;
}

// ----------------------------------------------------------
//   FreeImage interface
// ----------------------------------------------------------

BOOL DLL_CALLCONV 
FreeImage_JPEGTransform(const char *src_file, const char *dst_file, FREE_IMAGE_JPEG_OPERATION operation, BOOL perfect) {
	try {
		// check the src file format
		if(FreeImage_GetFileType(src_file) != FIF_JPEG) {
			throw FI_MSG_ERROR_MAGIC_NUMBER;
		}

		// setup IO
		FilenameIO filenameIO;
		memset(&filenameIO, 0, sizeof(FilenameIO));
		filenameIO.src_file = src_file;
		filenameIO.dst_file = dst_file;

		// perform the transformation
		return LosslessTransform(&filenameIO, operation, NULL, perfect);

	} catch(const char *text) {
		FreeImage_OutputMessageProc(FIF_JPEG, text);
		return FALSE;
	}
}

BOOL DLL_CALLCONV 
FreeImage_JPEGCrop(const char *src_file, const char *dst_file, int left, int top, int right, int bottom) {
	char crop[64];

	try {
		// check the src file format
		if(FreeImage_GetFileType(src_file) != FIF_JPEG) {
			throw FI_MSG_ERROR_MAGIC_NUMBER;
		}
		
		// normalize the rectangle
		if(right < left) {
			INPLACESWAP(left, right);
		}
		if(bottom < top) {
			INPLACESWAP(top, bottom);
		}

		// build the crop option
		sprintf(crop, "%dx%d+%d+%d", right - left, bottom - top, left, top);

		// setup IO
		FilenameIO filenameIO;
		memset(&filenameIO, 0, sizeof(FilenameIO));
		filenameIO.src_file = src_file;
		filenameIO.dst_file = dst_file;

		// perform the transformation
		return LosslessTransform(&filenameIO, FIJPEG_OP_NONE, crop, FALSE);

	} catch(const char *text) {
		FreeImage_OutputMessageProc(FIF_JPEG, text);
		return FALSE;
	}
}

BOOL DLL_CALLCONV 
FreeImage_JPEGTransformU(const wchar_t *src_file, const wchar_t *dst_file, FREE_IMAGE_JPEG_OPERATION operation, BOOL perfect) {
#ifdef _WIN32
	try {
		// check the src file format
		if(FreeImage_GetFileTypeU(src_file) != FIF_JPEG) {
			throw FI_MSG_ERROR_MAGIC_NUMBER;
		}

		// setup IO
		FilenameIO filenameIO;
		memset(&filenameIO, 0, sizeof(FilenameIO));
		filenameIO.wsrc_file = src_file;
		filenameIO.wdst_file = dst_file;

		// perform the transformation
		return LosslessTransform(&filenameIO, operation, NULL, perfect);

	} catch(const char *text) {
		FreeImage_OutputMessageProc(FIF_JPEG, text);
	}
#endif /// _WIN32
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_JPEGCropU(const wchar_t *src_file, const wchar_t *dst_file, int left, int top, int right, int bottom) {
#ifdef _WIN32
	char crop[64];

	try {
		// check the src file format
		if(FreeImage_GetFileTypeU(src_file) != FIF_JPEG) {
			throw FI_MSG_ERROR_MAGIC_NUMBER;
		}
		
		// normalize the rectangle
		if(right < left) {
			INPLACESWAP(left, right);
		}
		if(bottom < top) {
			INPLACESWAP(top, bottom);
		}

		// build the crop option
		sprintf(crop, "%dx%d+%d+%d", right - left, bottom - top, left, top);

		// setup IO
		FilenameIO filenameIO;
		memset(&filenameIO, 0, sizeof(FilenameIO));
		filenameIO.wsrc_file = src_file;
		filenameIO.wdst_file = dst_file;

		// perform the transformation
		return LosslessTransform(&filenameIO, FIJPEG_OP_NONE, crop, FALSE);

	} catch(const char *text) {
		FreeImage_OutputMessageProc(FIF_JPEG, text);
	}
#endif // _WIN32
	return FALSE;
}
