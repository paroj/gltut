// ==========================================================
// EXR Loader and writer
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
#include "../OpenEXR/IlmImf/ImfIO.h"
#include "../OpenEXR/Iex/Iex.h"
#include "../OpenEXR/IlmImf/ImfOutputFile.h"
#include "../OpenEXR/IlmImf/ImfInputFile.h"
#include "../OpenEXR/IlmImf/ImfRgbaFile.h"
#include "../OpenEXR/IlmImf/ImfChannelList.h"
#include "../OpenEXR/IlmImf/ImfRgba.h"
#include "../OpenEXR/IlmImf/ImfArray.h"
#include "../OpenEXR/Half/half.h"


// ==========================================================
// Plugin Interface
// ==========================================================

static int s_format_id;

// ----------------------------------------------------------

/**
FreeImage input stream wrapper
*/
class C_IStream: public Imf::IStream {
public:
	C_IStream (FreeImageIO *io, fi_handle handle):
	IStream(""), _io (io), _handle(handle) {}

	virtual bool	read (char c[/*n*/], int n);
	virtual Imf::Int64	tellg ();
	virtual void	seekg (Imf::Int64 pos);
	virtual void	clear () {};

private:
    FreeImageIO *_io;
	fi_handle _handle;
};


/**
FreeImage output stream wrapper
*/
class C_OStream: public Imf::OStream {
public:
	C_OStream (FreeImageIO *io, fi_handle handle):
	OStream(""), _io (io), _handle(handle) {}

    virtual void	write (const char c[/*n*/], int n);
	virtual Imf::Int64	tellp ();
	virtual void	seekp (Imf::Int64 pos);

private:
    FreeImageIO *_io;
	fi_handle _handle;
};


bool
C_IStream::read (char c[/*n*/], int n) {
	return ((unsigned)n != _io->read_proc(c, 1, n, _handle));
}

Imf::Int64
C_IStream::tellg () {
	return _io->tell_proc(_handle);
}

void
C_IStream::seekg (Imf::Int64 pos) {
	_io->seek_proc(_handle, (unsigned)pos, SEEK_SET);
}

void
C_OStream::write (const char c[/*n*/], int n) {
	if((unsigned)n != _io->write_proc((void*)&c[0], 1, n, _handle)) {
		Iex::throwErrnoExc();
	}
}

Imf::Int64
C_OStream::tellp () {
	return _io->tell_proc(_handle);
}

void
C_OStream::seekp (Imf::Int64 pos) {
	_io->seek_proc(_handle, (unsigned)pos, SEEK_SET);
}

// ----------------------------------------------------------


// ==========================================================
// Plugin Implementation
// ==========================================================

static const char * DLL_CALLCONV
Format() {
	return "EXR";
}

static const char * DLL_CALLCONV
Description() {
	return "ILM OpenEXR";
}

static const char * DLL_CALLCONV
Extension() {
	return "exr";
}

static const char * DLL_CALLCONV
RegExpr() {
	return NULL;
}

static const char * DLL_CALLCONV
MimeType() {
	return "image/exr";
}

static BOOL DLL_CALLCONV
Validate(FreeImageIO *io, fi_handle handle) {
	BYTE exr_signature[] = { 0x76, 0x2F, 0x31, 0x01 };
	BYTE signature[] = { 0, 0, 0, 0 };

	io->read_proc(signature, 1, 4, handle);
	return (memcmp(exr_signature, signature, 4) == 0);
}

static BOOL DLL_CALLCONV
SupportsExportDepth(int depth) {
	return FALSE;
}

static BOOL DLL_CALLCONV 
SupportsExportType(FREE_IMAGE_TYPE type) {
	return (
		(type == FIT_FLOAT) ||
		(type == FIT_RGBF)  ||
		(type == FIT_RGBAF)
	);
}

// --------------------------------------------------------------------------

static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	bool bUseRgbaInterface = false;
	FIBITMAP *dib = NULL;	

	if(handle) {
		try {
			// save the stream starting point
			long stream_start = io->tell_proc(handle);

			// wrap the FreeImage IO stream
			C_IStream istream(io, handle);

			// open the file
			Imf::InputFile file(istream);

			// get file info			
			const Imath::Box2i &dataWindow = file.header().dataWindow();
			int width  = dataWindow.max.x - dataWindow.min.x + 1;
			int height = dataWindow.max.y - dataWindow.min.y + 1;

			//const Imf::Compression &compression = file.header().compression();

			if((dataWindow.min.x > 0) || (dataWindow.min.x < 0) || (dataWindow.min.y > 0) || (dataWindow.min.y < 0)) {
				THROW (Iex::InputExc, "Invalid data window " << 
					"[" << dataWindow.min.x << "," << dataWindow.min.y << "," << dataWindow.max.x << "," << dataWindow.max.y << "]");
			}
            			
			const Imf::ChannelList &channels = file.header().channels();

			// check the number of components and check for a coherent format

			std::string exr_color_model;
			Imf::PixelType pixel_type = Imf::HALF;
			FREE_IMAGE_TYPE image_type = FIT_UNKNOWN;
			int components = 0;
			bool bMixedComponents = false;

			for (Imf::ChannelList::ConstIterator i = channels.begin(); i != channels.end(); ++i) {
				components++;
				if(components == 1) {
					exr_color_model += i.name();
					pixel_type = i.channel().type;
				} else {
					exr_color_model += "/";
					exr_color_model += i.name();
					if (i.channel().type != pixel_type) {
						bMixedComponents = true;
					}
				}
			}
			if(bMixedComponents) {
				bool bHandled = false;
				// we may have a RGBZ or RGBAZ image ... 
				if(components > 4) {
					if(channels.findChannel("R") && channels.findChannel("G") && channels.findChannel("B") && channels.findChannel("A")) {
						std::string msg = "Warning: converting color model " + exr_color_model + " to RGBA color model";
						FreeImage_OutputMessageProc(s_format_id, msg.c_str());
						bHandled = true;
					}
				}
				else if(components > 3) {
					if(channels.findChannel("R") && channels.findChannel("G") && channels.findChannel("B")) {
						std::string msg = "Warning: converting color model " + exr_color_model + " to RGB color model";
						FreeImage_OutputMessageProc(s_format_id, msg.c_str());
						bHandled = true;
					}
				}
				if(!bHandled) {
					THROW (Iex::InputExc, "Unable to handle mixed component types (color model = " << exr_color_model << ")");
				} 
			}
			switch(pixel_type) {
				case Imf::UINT:
					THROW (Iex::InputExc, "Unsupported format: UINT");
					break;
				case Imf::HALF:
				case Imf::FLOAT:
				default:
					break;
			}
			// check for supported image color models
			if((components == 1) || (components == 2)) {				
				// if the image is gray-alpha (YA), ignore the alpha channel
				if(channels.findChannel("Y")) {
					image_type = FIT_FLOAT;
					components = 1;
				} else if(components == 1) {
					std::string msg = "Warning: loading color model " + exr_color_model + " as Y color model";
					FreeImage_OutputMessageProc(s_format_id, msg.c_str());
					image_type = FIT_FLOAT;
				}
			} else if(components == 3) {
				if(channels.findChannel("R") && channels.findChannel("G") && channels.findChannel("B")) {
					image_type = FIT_RGBF;
				}
				else if(channels.findChannel("BY") && channels.findChannel("RY") && channels.findChannel("Y")) {
					image_type = FIT_RGBF;
					bUseRgbaInterface = true;
				}
			} else if(components >= 4) {				
				if(channels.findChannel("R") && channels.findChannel("G") && channels.findChannel("B") && channels.findChannel("A")) {
					image_type = FIT_RGBAF;
					// ignore other layers if there is more than one alpha layer
					components = 4;
				}
			}
			if(image_type == FIT_UNKNOWN) {
				THROW (Iex::InputExc, "Unsupported color model: " << exr_color_model);
			}

			// allocate a new dib
			dib = FreeImage_AllocateT(image_type, width, height);
			if(!dib) THROW (Iex::NullExc, FI_MSG_ERROR_MEMORY);

			BYTE *bits = FreeImage_GetBits(dib);			// pointer to our pixel buffer
			size_t bytespp = sizeof(float) * components;	// size of our pixel in bytes
			unsigned pitch = FreeImage_GetPitch(dib);		// size of our yStride in bytes

			Imf::PixelType pixelType = Imf::FLOAT;	// load as float data type;
			
			if(bUseRgbaInterface) {
				// use the RGBA interface

				const int chunk_size = 16;

				BYTE *scanline = (BYTE*)bits;

				// re-open using the RGBA interface
				io->seek_proc(handle, stream_start, SEEK_SET);
				Imf::RgbaInputFile rgbaFile(istream);

				// read the file in chunks
				Imath::Box2i dw = dataWindow;
				Imf::Array2D<Imf::Rgba> chunk(chunk_size, width);
				while (dw.min.y <= dw.max.y) {
					// read a chunk
					rgbaFile.setFrameBuffer (&chunk[0][0] - dw.min.x - dw.min.y * width, 1, width);
					rgbaFile.readPixels (dw.min.y, MIN(dw.min.y + chunk_size - 1, dw.max.y));
					// fill the dib
					const int y_max = ((dw.max.y - dw.min.y) <= chunk_size) ? (dw.max.y - dw.min.y) : chunk_size;
					for(int y = 0; y < y_max; y++) {
						FIRGBF *pixel = (FIRGBF*)scanline;
						const Imf::Rgba *half_rgba = chunk[y];
						for(int x = 0; x < width; x++) {
							// convert from half to float
							pixel[x].red = half_rgba[x].r;
							pixel[x].green = half_rgba[x].g;
							pixel[x].blue = half_rgba[x].b;
						}
						// next line
						scanline += pitch;
					}
					// next chunk
					dw.min.y += chunk_size;
				}

			} else {
				// use the low level interface

				// build a frame buffer (i.e. what we want on output)
				Imf::FrameBuffer frameBuffer;

				if(components == 1) {
					frameBuffer.insert ("Y",	// name
						Imf::Slice (pixelType,	// type
						(char*)(bits),			// base
						bytespp,				// xStride
						pitch,					// yStride
						1, 1,					// x/y sampling
						0.0));					// fillValue
				} else if((components == 3) || (components == 4)) {
					const char *channel_name[4] = { "R", "G", "B", "A" };

					for(int c = 0; c < components; c++) {
						frameBuffer.insert (
							channel_name[c],					// name
							Imf::Slice (pixelType,				// type
							(char*)(bits + c * sizeof(float)),	// base
							bytespp,							// xStride
							pitch,								// yStride
							1, 1,								// x/y sampling
							0.0));								// fillValue
					}
				}

				// read the file
				file.setFrameBuffer(frameBuffer);
				file.readPixels(dataWindow.min.y, dataWindow.max.y);
			}

			// lastly, flip dib lines
			FreeImage_FlipVertical(dib);

		}
		catch(Iex::BaseExc & e) {
			if(dib != NULL) {
				FreeImage_Unload(dib);
			}
			FreeImage_OutputMessageProc(s_format_id, e.what());
			return NULL;
		}
	}	

	return dib;
}


/**
Save using EXR_LC compression (works only with RGB[A]F images)
*/
static BOOL 
SaveAsEXR_LC(C_OStream& ostream, FIBITMAP *dib, Imf::Header& header, int width, int height) {
	int x, y;
	Imf::RgbaChannels rgbaChannels;

	try {

		FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);

		// convert from float to half
		Imf::Array2D<Imf::Rgba> pixels(height, width);
		switch(image_type) {
			case FIT_RGBF:
				rgbaChannels = Imf::WRITE_YC;
				for(y = 0; y < height; y++) {
					FIRGBF *src_bits = (FIRGBF*)FreeImage_GetScanLine(dib, height - 1 - y);
					for(x = 0; x < width; x++) {
						Imf::Rgba &dst_bits = pixels[y][x];
						dst_bits.r = src_bits[x].red;
						dst_bits.g = src_bits[x].green;
						dst_bits.b = src_bits[x].blue;
					}
				}
				break;
			case FIT_RGBAF:
				rgbaChannels = Imf::WRITE_YCA;
				for(y = 0; y < height; y++) {
					FIRGBAF *src_bits = (FIRGBAF*)FreeImage_GetScanLine(dib, height - 1 - y);
					for(x = 0; x < width; x++) {
						Imf::Rgba &dst_bits = pixels[y][x];
						dst_bits.r = src_bits[x].red;
						dst_bits.g = src_bits[x].green;
						dst_bits.b = src_bits[x].blue;
						dst_bits.a = src_bits[x].alpha;
					}
				}
				break;
			default:
				THROW (Iex::IoExc, "Bad image type");
				break;
		}

		// write the data
		Imf::RgbaOutputFile file(ostream, header, rgbaChannels);
		file.setFrameBuffer (&pixels[0][0], 1, width);
		file.writePixels (height);

		return TRUE;

	} catch(Iex::BaseExc & e) {
		FreeImage_OutputMessageProc(s_format_id, e.what());

		return FALSE;
	}

}

static BOOL DLL_CALLCONV
Save(FreeImageIO *io, FIBITMAP *dib, fi_handle handle, int page, int flags, void *data) {
	const char *channel_name[4] = { "R", "G", "B", "A" };
	BOOL bIsFlipped = FALSE;
	half *halfData = NULL;

	if(!dib || !handle) return FALSE;

	try {
		// check for EXR_LC compression and verify that the format is RGB
		if((flags & EXR_LC) == EXR_LC) {
			FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
			if(((image_type != FIT_RGBF) && (image_type != FIT_RGBAF)) || ((flags & EXR_FLOAT) == EXR_FLOAT)) {
				THROW (Iex::IoExc, "EXR_LC compression is only available with RGB[A]F images");
			}
			if((FreeImage_GetWidth(dib) % 2) || (FreeImage_GetHeight(dib) % 2)) {
				THROW (Iex::IoExc, "EXR_LC compression only works when the width and height are a multiple of 2");
			}
		}

		// wrap the FreeImage IO stream
		C_OStream ostream(io, handle);

		// compression
		Imf::Compression compress;
		if((flags & EXR_NONE) == EXR_NONE) {
			// no compression
			compress = Imf::NO_COMPRESSION;
		} else if((flags & EXR_ZIP) == EXR_ZIP) {
			// zlib compression, in blocks of 16 scan lines
			compress = Imf::ZIP_COMPRESSION;
		} else if((flags & EXR_PIZ) == EXR_PIZ) {
			// piz-based wavelet compression
			compress = Imf::PIZ_COMPRESSION;
		} else if((flags & EXR_PXR24) == EXR_PXR24) {
			// lossy 24-bit float compression
			compress = Imf::PXR24_COMPRESSION;
		} else if((flags & EXR_B44) == EXR_B44) {
			// lossy 44% float compression
			compress = Imf::B44_COMPRESSION;
		} else {
			// default value
			compress = Imf::PIZ_COMPRESSION;
		}

		// create the header
		int width  = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		int dx = 0, dy = 0;

		Imath::Box2i dataWindow (Imath::V2i (0, 0), Imath::V2i (width - 1, height - 1));
		Imath::Box2i displayWindow (Imath::V2i (-dx, -dy), Imath::V2i (width - dx - 1, height - dy - 1));

		Imf::Header header = Imf::Header(displayWindow, dataWindow, 1, 
			Imath::V2f(0,0), 1, 
			Imf::INCREASING_Y, compress);        		

		// check for EXR_LC compression
		if((flags & EXR_LC) == EXR_LC) {
			return SaveAsEXR_LC(ostream, dib, header, width, height);
		}

		// output pixel type
		Imf::PixelType pixelType;
		if((flags & EXR_FLOAT) == EXR_FLOAT) {
			pixelType = Imf::FLOAT;	// save as float data type
		} else {
			// default value
			pixelType = Imf::HALF;	// save as half data type
		}

		// check the data type and number of channels
		int components = 0;
		FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
		switch(image_type) {
			case FIT_FLOAT:
				components = 1;
				// insert luminance channel
				header.channels().insert ("Y", Imf::Channel(pixelType));
				break;
			case FIT_RGBF:
				components = 3;
				for(int c = 0; c < components; c++) {
					// insert R, G and B channels
					header.channels().insert (channel_name[c], Imf::Channel(pixelType));
				}
				break;
			case FIT_RGBAF:
				components = 4;
				for(int c = 0; c < components; c++) {
					// insert R, G, B and A channels
					header.channels().insert (channel_name[c], Imf::Channel(pixelType));
				}
				break;
			default:
				THROW (Iex::ArgExc, "Cannot save: invalid data type.\nConvert the image to float before saving as OpenEXR.");
		}

		// build a frame buffer (i.e. what we have on input)
		Imf::FrameBuffer frameBuffer;

		BYTE *bits = NULL;	// pointer to our pixel buffer
		size_t bytespp = 0;	// size of our pixel in bytes
		size_t bytespc = 0;	// size of our pixel component in bytes
		unsigned pitch = 0;	// size of our yStride in bytes


		if(pixelType == Imf::HALF) {
			// convert from float to half
			halfData = new half[width * height * components];
			if(!halfData) THROW (Iex::NullExc, FI_MSG_ERROR_MEMORY);
			for(int y = 0; y < height; y++) {
				float *src_bits = (float*)FreeImage_GetScanLine(dib, height - 1 - y);
				half *dst_bits = halfData + y * width * components;
				for(int x = 0; x < width; x++) {
					for(int c = 0; c < components; c++) {
						dst_bits[c] = src_bits[c];
					}
					src_bits += components;
					dst_bits += components;
				}
			}
			bits = (BYTE*)halfData;
			bytespc = sizeof(half);
			bytespp = sizeof(half) * components;
			pitch = sizeof(half) * width * components;
		} else if(pixelType == Imf::FLOAT) {
			// invert dib scanlines
			bIsFlipped = FreeImage_FlipVertical(dib);
		
			bits = FreeImage_GetBits(dib);
			bytespc = sizeof(float);
			bytespp = sizeof(float) * components;
			pitch = FreeImage_GetPitch(dib);
		}

		if(image_type == FIT_FLOAT) {
			frameBuffer.insert ("Y",	// name
				Imf::Slice (pixelType,	// type
				(char*)(bits),			// base
				bytespp,				// xStride
				pitch));				// yStride
		} else if((image_type == FIT_RGBF) || (image_type == FIT_RGBAF)) {			
			for(int c = 0; c < components; c++) {
				char *channel_base = (char*)(bits) + c*bytespc;
				frameBuffer.insert (channel_name[c],// name
					Imf::Slice (pixelType,			// type
					channel_base,					// base
					bytespp,	// xStride
					pitch));	// yStride
			}
		}

		// write the data
		Imf::OutputFile file (ostream, header);
		file.setFrameBuffer (frameBuffer);
		file.writePixels (height);

		if(halfData != NULL) delete[] halfData;
		if(bIsFlipped) {
			// invert dib scanlines
			FreeImage_FlipVertical(dib);
		}

		return TRUE;

	} catch(Iex::BaseExc & e) {
		if(halfData != NULL) delete[] halfData;
		if(bIsFlipped) {
			// invert dib scanlines
			FreeImage_FlipVertical(dib);
		}

		FreeImage_OutputMessageProc(s_format_id, e.what());

		return FALSE;
	}	
}

// ==========================================================
//   Init
// ==========================================================

void DLL_CALLCONV
InitEXR(Plugin *plugin, int format_id) {
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
	plugin->save_proc = Save;
	plugin->validate_proc = Validate;
	plugin->mime_proc = MimeType;
	plugin->supports_export_bpp_proc = SupportsExportDepth;
	plugin->supports_export_type_proc = SupportsExportType;
	plugin->supports_icc_profiles_proc = NULL;
}
