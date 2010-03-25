// ==========================================================
// RAW camera image loader
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
#include "../Metadata/FreeImageTag.h"

#include "../LibRawLite/libraw/libraw.h"

// ==========================================================
// Plugin Interface
// ==========================================================

static int s_format_id;

// ==========================================================
// Internal functions
// ==========================================================

// ----------------------------------------------------------
//   FreeImage datastream wrapper
// ----------------------------------------------------------

class LibRaw_freeimage_datastream : public LibRaw_abstract_datastream {
private: 
	FreeImageIO *_io;
	fi_handle _handle;
	long _eof;

public:
	LibRaw_freeimage_datastream(FreeImageIO *io, fi_handle handle) : _io(io), _handle(handle) {
		long start_pos = io->tell_proc(handle);
		io->seek_proc(handle, 0, SEEK_END);
		_eof = io->tell_proc(handle);
		io->seek_proc(handle, start_pos, SEEK_SET);
	}
	~LibRaw_freeimage_datastream() {
	}
    virtual int valid() { 
		return (_io && _handle);
	}
    virtual int read(void *buffer, size_t size, size_t count) { 
		if(substream) return substream->read(buffer, size, count);
		return _io->read_proc(buffer, (unsigned)size, (unsigned)count, _handle);
	}	
    virtual int eof() { 
        if(substream) return substream->eof();
        return (_io->tell_proc(_handle) >= _eof);
    }
    virtual int seek(off_t offset, int origin) { 
        if(substream) return substream->seek(offset, origin);
		return _io->seek_proc(_handle, offset, origin);
	} 
    virtual int tell() { 
		if(substream) return substream->tell();
        return _io->tell_proc(_handle);
    }
    virtual int get_char() { 
		int c = 0;
		if(substream) return substream->get_char();
		if(!_io->read_proc(&c, 1, 1, _handle)) return -1;
		return c;
   }
	virtual char* gets(char *buffer, int length) { 
		if (substream) return substream->gets(buffer, length);
		memset(buffer, 0, length);
		for(int i = 0; i < length; i++) {
			if(!_io->read_proc(&buffer[i], 1, 1, _handle))
				return NULL;
			if(buffer[i] == 0x0A)
				break;
		}
		return buffer;
	}
	virtual int scanf_one(const char *fmt, void* val) {
		std::string buffer;
		char element = 0;
		bool bDone = false;
		if(substream) return substream->scanf_one(fmt,val);				
		do {
			if(_io->read_proc(&element, 1, 1, _handle) == 1) {
				switch(element) {
					case '0':
					case '\n':
					case ' ':
					case '\t':
						bDone = true;
						break;
					default:
						break;
				}
				buffer.append(&element, 1);
			} else {
				return 0;
			}
		} while(!bDone);

		return sscanf(buffer.c_str(), fmt, val);
	}
};

// ----------------------------------------------------------

/**
Convert a processed raw data array to a FIBITMAP
@param image Processed raw image
@return Returns the converted dib if successfull, returns NULL otherwise
*/
static FIBITMAP * 
libraw_ConvertToDib(libraw_processed_image_t *image) {
	FIBITMAP *dib = NULL;
	try {
		unsigned width = image->width;
		unsigned height = image->height;
		unsigned bpp = image->bits;
		if(bpp == 16) {
			// allocate output dib
			dib = FreeImage_AllocateT(FIT_RGB16, width, height);
			if(!dib) {
				throw FI_MSG_ERROR_DIB_MEMORY;
			}
			// write data
			unsigned short *raw_data = (unsigned short*)image->data;
			for(unsigned y = 0; y < height; y++) {
				FIRGB16 *output = (FIRGB16*)FreeImage_GetScanLine(dib, height - 1 - y);
				for(unsigned x = 0; x < width; x++) {
					output[x].red   = raw_data[0];
					output[x].green = raw_data[1];
					output[x].blue  = raw_data[2];
					raw_data += 3;
				}
			}
		} else if(bpp == 8) {
			// allocate output dib
			dib = FreeImage_AllocateT(FIT_BITMAP, width, height, 24);
			if(!dib) {
				throw FI_MSG_ERROR_DIB_MEMORY;
			}
			// write data
			BYTE *raw_data = (BYTE*)image->data;
			for(unsigned y = 0; y < height; y++) {
				RGBTRIPLE *output = (RGBTRIPLE*)FreeImage_GetScanLine(dib, height - 1 - y);
				for(unsigned x = 0; x < width; x++) {
					output[x].rgbtRed   = raw_data[0];
					output[x].rgbtGreen = raw_data[1];
					output[x].rgbtBlue  = raw_data[2];
					raw_data += 3;
				}
			}
		}

	} catch(const char *text) {
		FreeImage_OutputMessageProc(s_format_id, text);
	}

	return dib;
}

/** 
Get the embedded JPEG preview image from RAW picture with included Exif Data. 
@param RawProcessor Libraw handle
@return Returns the loaded dib if successfull, returns NULL otherwise
*/
static FIBITMAP * 
libraw_LoadEmbeddedPreview(LibRaw& RawProcessor) {
	FIBITMAP *dib = NULL;
	libraw_processed_image_t *thumb_image = NULL;
	
	try {
		// unpack data
		if(RawProcessor.unpack_thumb() != LIBRAW_SUCCESS) {
			throw (char*)NULL;	// run silently "LibRaw : failed to run unpack_thumb"
		}

		// retrieve thumb image
		int error_code = 0;
		thumb_image = RawProcessor.dcraw_make_mem_thumb(&error_code);
		if(thumb_image) {
			if(thumb_image->type != LIBRAW_IMAGE_BITMAP) {
				int flags = 0;
				// attach the binary data to a memory stream
				FIMEMORY *hmem = FreeImage_OpenMemory((BYTE*)thumb_image->data, (DWORD)thumb_image->data_size);
				// get the file type
				FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(hmem, 0);
				if(fif == FIF_JPEG) {
					// rotate according to Exif orientation
					flags |= JPEG_EXIFROTATE;
				}
				// load an image from the memory stream
				dib = FreeImage_LoadFromMemory(fif, hmem, flags);
				// close the stream
				FreeImage_CloseMemory(hmem);
			} else {
				// convert processed data to output dib
				dib = libraw_ConvertToDib(thumb_image);
			}
		} else {
			throw "LibRaw : failed to run dcraw_make_mem_thumb";
		}

		// clean-up and return
		free(thumb_image);

		return dib;

	} catch(const char *text) {
		// clean-up and return
		if(thumb_image) {
			free(thumb_image);
		}
		if(text != NULL) {
			FreeImage_OutputMessageProc(s_format_id, text);
		}
	}

	return NULL;
}
/**
Load raw data and convert to FIBITMAP
@param RawProcessor Libraw handle
@param bitspersample Output bitdepth (8- or 16-bit)
@return Returns the loaded dib if successfull, returns NULL otherwise
*/
static FIBITMAP * 
libraw_LoadRawData(LibRaw& RawProcessor, int bitspersample) {
	FIBITMAP *dib = NULL;
	libraw_processed_image_t *processed_image = NULL;

	try {
		// set decoding parameters
		// -----------------------
		
		// (-4) Linear 16-bit or 8-bit
		RawProcessor.imgdata.params.output_bps = bitspersample;
		// (-w) Use camera white balance, if possible
		RawProcessor.imgdata.params.use_camera_wb = 1;
		// (-a) Average the whole image for white balance
		RawProcessor.imgdata.params.use_auto_wb = 1;
		// (-q 3) Adaptive homogeneity-directed demosaicing algorithm (AHD)
		RawProcessor.imgdata.params.user_qual = 3;

		// -----------------------

		// unpack data
		if(RawProcessor.unpack() != LIBRAW_SUCCESS) {
			throw "LibRaw : failed to unpack data";
		}

		// process data (... most consuming task ...)
		if(RawProcessor.dcraw_process() != LIBRAW_SUCCESS) {
			throw "LibRaw : failed to process data";
		}

		// retrieve processed image
		int error_code = 0;
		processed_image = RawProcessor.dcraw_make_mem_image(&error_code);
		if(processed_image) {
			// type SHOULD be LIBRAW_IMAGE_BITMAP, but we'll check
			if(processed_image->type != LIBRAW_IMAGE_BITMAP) {
				throw "invalid image type";
			}
			// only 3-color images supported...
			if(processed_image->colors != 3) {
				throw "only 3-color images supported";
			}
		} else {
			throw "LibRaw : failed to run dcraw_make_mem_image";
		}

		// convert processed data to output dib
		dib = libraw_ConvertToDib(processed_image);
	
		// clean-up and return
		free(processed_image);

		return dib;

	} catch(const char *text) {
		// clean-up and return
		if(processed_image) {
			free(processed_image);
		}
		FreeImage_OutputMessageProc(s_format_id, text);
	}

	return NULL;
}

// ==========================================================
// Plugin Implementation
// ==========================================================

static const char * DLL_CALLCONV
Format() {
	return "RAW";
}

static const char * DLL_CALLCONV
Description() {
	return "RAW camera image";
}

static const char * DLL_CALLCONV
Extension() {
	static const char *raw_extensions = 
		"bay,"   // Casio Digital Camera Raw File Format.
		"bmq,"   // NuCore Raw Image File.
		"cr2,"   // Canon Digital Camera RAW Image Format version 2.0. These images are based on the TIFF image standard.
		"crw,"   // Canon Digital Camera RAW Image Format version 1.0. 
		"cs1,"   // Capture Shop Raw Image File.
		"dc2,"   // Kodak DC25 Digital Camera File.
		"dcr,"   // Kodak Digital Camera Raw Image Format for these models: Kodak DSC Pro SLR/c, Kodak DSC Pro SLR/n, Kodak DSC Pro 14N, Kodak DSC PRO 14nx.
		"dng,"   // Adobe Digital Negative: DNG is publicly available archival format for the raw files generated by digital cameras. By addressing the lack of an open standard for the raw files created by individual camera models, DNG helps ensure that photographers will be able to access their files in the future. 
		"erf,"   // Epson Digital Camera Raw Image Format.
		"fff,"   // Imacon Digital Camera Raw Image Format.
		"hdr,"   // Leaf Raw Image File.
		"k25,"   // Kodak DC25 Digital Camera Raw Image Format.
		"kdc,"   // Kodak Digital Camera Raw Image Format.
		"mdc,"   // Minolta RD175 Digital Camera Raw Image Format.
		"mos,"   // Mamiya Digital Camera Raw Image Format.
		"mrw,"   // Minolta Dimage Digital Camera Raw Image Format.
		"nef,"   // Nikon Digital Camera Raw Image Format.
		"orf,"   // Olympus Digital Camera Raw Image Format.
		"pef,"   // Pentax Digital Camera Raw Image Format.
		"pxn,"   // Logitech Digital Camera Raw Image Format.
		"raf,"   // Fuji Digital Camera Raw Image Format.
		"raw,"   // Panasonic Digital Camera Image Format.
		"rdc,"   // Digital Foto Maker Raw Image File.
		"sr2,"   // Sony Digital Camera Raw Image Format.
		"srf,"   // Sony Digital Camera Raw Image Format for DSC-F828 8 megapixel digital camera or Sony DSC-R1
//		"x3f,"   // Sigma Digital Camera Raw Image Format for devices based on Foveon X3 direct image sensor.
		"arw,"   // Sony Digital Camera Raw Image Format for Alpha devices.
		"3fr,"   // Hasselblad Digital Camera Raw Image Format.
		"cine,"  // Phantom Software Raw Image File.
		"ia,"    // Sinar Raw Image File.
		"kc2,"   // Kodak DCS200 Digital Camera Raw Image Format.
		"mef,"   // Mamiya Digital Camera Raw Image Format.
		"nrw,"   // Nikon Digital Camera Raw Image Format.
		"qtk,"   // Apple Quicktake 100/150 Digital Camera Raw Image Format.
		"rw2,"   // Panasonic LX3 Digital Camera Raw Image Format.
		"sti,"   // Sinar Capture Shop Raw Image File.
		"drf,"   // Kodak Digital Camera Raw Image Format.
		"dsc,"   // Kodak Digital Camera Raw Image Format.
		"ptx,"   // Pentax Digital Camera Raw Image Format.
		"cap,"   // Phase One Digital Camera Raw Image Format.
		"iiq,"   // Phase One Digital Camera Raw Image Format.
		"rwz";   // Rawzor Digital Camera Raw Image Format.
	return raw_extensions;
}

static const char * DLL_CALLCONV
RegExpr() {
	return NULL;
}

static const char * DLL_CALLCONV
MimeType() {
	return "image/x-raw";
}

static BOOL DLL_CALLCONV
Validate(FreeImageIO *io, fi_handle handle) {
	LibRaw RawProcessor;
	
	try {
		// wrap the input datastream
		LibRaw_freeimage_datastream datastream(io, handle);

		// open the datastream
		if(RawProcessor.open_datastream(&datastream) != LIBRAW_SUCCESS) {
			throw(1);	// LibRaw : failed to open input stream (unknown format)
		}

		// clean-up internal memory allocations
		RawProcessor.recycle();

		return TRUE;

	} catch(int) {
		// clean-up and return
		RawProcessor.recycle();
	}

	return FALSE;
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

static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	FIBITMAP *dib = NULL;
	LibRaw RawProcessor;

	try {
		// wrap the input datastream
		LibRaw_freeimage_datastream datastream(io, handle);

		// open the datastream
		if(RawProcessor.open_datastream(&datastream) != LIBRAW_SUCCESS) {
			throw "LibRaw : failed to open input stream (unknown format)";
		}

		if((flags & RAW_PREVIEW) == RAW_PREVIEW) {
			// try to get the embedded JPEG
			dib = libraw_LoadEmbeddedPreview(RawProcessor);
			if(!dib) {
				// no JPEG preview: try to load as 8-bit
				dib = libraw_LoadRawData(RawProcessor, 8);
			}
		} else if((flags & RAW_DISPLAY) == RAW_DISPLAY) {
			// load raw data as RGB 24-bit
			dib = libraw_LoadRawData(RawProcessor, 8);
		} else {
			// default: load raw data as linear 16-bit
			dib = libraw_LoadRawData(RawProcessor, 16);
		}

		// save ICC profile if present
		if(NULL != RawProcessor.imgdata.color.profile) {
			FreeImage_CreateICCProfile(dib, RawProcessor.imgdata.color.profile, RawProcessor.imgdata.color.profile_length);
		}

		// clean-up internal memory allocations
		RawProcessor.recycle();

		return dib;

	} catch(const char *text) {
		if(dib) {
			FreeImage_Unload(dib);
		}
		RawProcessor.recycle();
		FreeImage_OutputMessageProc(s_format_id, text);
	}

	return NULL;
}

// ==========================================================
//   Init
// ==========================================================

void DLL_CALLCONV
InitRAW(Plugin *plugin, int format_id) {
	s_format_id = format_id;

	plugin->format_proc = Format;
	plugin->description_proc = Description;
	plugin->extension_proc = Extension;
	plugin->regexpr_proc = RegExpr;
	plugin->open_proc = NULL;
	plugin->close_proc = NULL;
	plugin->pagecount_proc = NULL;
	plugin->pagecapability_proc = NULL;
	plugin->load_proc = Load;
	plugin->save_proc = NULL;
	plugin->validate_proc = Validate;
	plugin->mime_proc = MimeType;
	plugin->supports_export_bpp_proc = SupportsExportDepth;
	plugin->supports_export_type_proc = SupportsExportType;
	plugin->supports_icc_profiles_proc = NULL;
}
