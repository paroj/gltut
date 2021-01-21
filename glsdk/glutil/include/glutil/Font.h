/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef FONT_UTIL_H
#define FONT_UTIL_H

/**
\file
\brief Contains the \ref module_glutil_font "basic font rendering system" classes and functions.
**/

#include <exception>
#include <stdexcept>
#include <utility>
#include <vector>
#include <glm/glm.hpp>

namespace glutil
{
	///\addtogroup module_glutil_font
	///@{

	namespace detail
	{
		class FontImpl;
	}

	class Font;

	/**
	\brief The allowed sizes for fonts.

	The sizes are baseline-to-baseline; the actual height of a character will be smaller than this.
	**/
	enum FontSizes
	{
		FONT_SIZE_SMALL,		///<10 pixels in height.
		FONT_SIZE_MEDIUM,		///<14 pixels in height.
		FONT_SIZE_LARGE,		///<30 pixels in height.
		FONT_SIZE_GIANT,		///<63 pixels in height.
	};

	/**
	\brief Creates a font with the given size and characteristics.

	This function requires an active OpenGL context.
	
	This function allocates the Font object with new. You are responsible for deleting the Font object
	yourself with delete. Also, make sure that the OpenGL context is still active; it must be the same context
	(or one shared with it) that was active when this function was called.

	Since the Font creates an OpenGL texture, calling this function will modify the following OpenGL state:

	\li [All `GL_UNPACK_*` state](http://www.opengl.org/wiki/Pixel_Transfer#Pixel_transfer_parameters).
	\li The current texture unit's `GL_TEXTURE_2D` target will have texture object 0 bound to it.

	If ARB_texture_storage, or GL 4.2+, is available, then the [texture's storage will be
	immutable](http://www.opengl.org/wiki/Texture_Storage#Immutable_storage). So don't
	count on being able to modify the storage (the contents can be modified, just not the
	storage structure itself).

	Calling this function multiple times with the same parameters will create multiple copies
	of the same data. That is not necessary; just keep the Font object around and use it from
	different places.

	\param eSize The requested font size.
	\return The created Font.

	\note Despite this function creating a texture, this function has no dependencies on
	[GL Image](@ref module_glimg).
	**/
	Font *GenerateFont(FontSizes eSize);

	/**
	\brief Data type for a single glyph.

	The data for a glyph, as far as the font system is concerned, is a set of positions that define the
	space of the quad, and a set of texture coordinates that reference the Font's texture. Both the
	positions and texture coordinates are 2D vectors.
	**/
	class GlyphQuad
	{
	public:
		/**
		\brief Creates a glyph given two corner positions and two corner texture coordinates.
		**/
		GlyphQuad(glm::vec2 ptBottomLeft, glm::vec2 tcBottomLeft,
			glm::vec2 ptTopRight, glm::vec2 tcTopRight)
			: m_ptBottomLeft(ptBottomLeft)
			, m_tcBottomLeft(tcBottomLeft)
			, m_ptTopRight(ptTopRight)
			, m_tcTopRight(tcTopRight)
		{}

		/**
		\brief Returns the positions of the glyph as an array, for easy usage.

		The vector will have 4 elements, representing the four corners of the quad. In order, the points are:

		1. Top-left
		2. Bottom-left
		3. Top-right
		4. Bottom-right

		This represents a counter-clockwise winding order (the OpenGL default), and is suitable for a triangle strip.

		\todo Make this return a boost::array or something.
		**/
		std::vector<glm::vec2> GetPositions() const;

		/**
		\brief Returns the texture coordinates of the glyph as an array, for easy usage.

		The vector will have 4 elements, representing the four corners of the quad. They are in the same order
		as for GetPositions.

		\todo Make this return a boost::array or something.
		**/
		std::vector<glm::vec2> GetTexCoords() const;

	private:
		glm::vec2 m_ptBottomLeft;
		glm::vec2 m_tcBottomLeft;
		glm::vec2 m_ptTopRight;
		glm::vec2 m_tcTopRight;
	};

	/**
	\brief Defines what the vertical value of the point represents.
	
	When doing text layout, a starting point is provided. The vertical axis of this point could mean one
	of three possible places. It could represent the baseline point in the font, such that glyphs that
	hang under the baseline (commas, certain lower-case letters, etc) would modify pixels below this point.
	It could represent the absolute lowest point that any text could be rendered to, such that no pixels will
	be modified below this point. And it could represent the absolute highest point that any text could be
	rendered to, such that no pixels will be modified above this point.
	**/
	enum PointReference
	{
		REF_BASELINE,		///<The point is the baseline.
		REF_BOTTOM,			///<The point is the bottom of the text; nothing below here will be touched.
		REF_TOP,			///<The point is the top of the text; nothing above here will be touched.
	};

	/**
	\brief Thrown if a supposedly UTF-8 encoded string is not valid UTF-8.
	**/
	class InvalidEncodingException : public std::runtime_error
	{
	public:
		InvalidEncodingException() : std::runtime_error("UTF-8 text is not valid.") {}
	};

	//Deletion of this object must happen while OpenGL is still active.
	/**
	\brief The class that represents a series of glyphs as well as the information to layout a string of text.

	This class contains functions to get the rendering information for a single glyph and a line of glyphs. It
	also has functions for inspecting properties of the font (the height of lines, width of the characters, etc).

	This font will always be fixed-width. It contains characters only from the first 256 Unicode codepoints.
	Characters outside of this range are not available.

	This font is a "bitmap" font; the glyphs are stores as images in a texture.

	This class's constructors are private; you must use glutil::GenerateFont to create an instance of this class. The
	destructor is not private; you can (and \em should) call delete on this pointer.

	This class contains and manages an OpenGL texture. This means that deleting this class will destroy that texture.
	Most important of all, you must ensure that this object does not outlive the OpenGL context that was active when
	glutil::GenerateFont was called.

	All layout functions of this class assume the standard OpenGL coordinate system: +Y goes up and +X right.
	If you want to have a top-down coordinate system, you will need to adjust the glyphs manually.
	**/
	class Font
	{
	public:
		~Font();

		/**
		\brief Retrieves the texture that contains the glyph images.

		In order to render glyphs, you must bind this texture to the context and have your shader access
		the texture.
		
		The texture will, after creation, use nearest filtering. If you wish to override this,
		you should use an OpenGL sampler object. Be advised that the texture does not have mipmaps, so
		performing mipmap filtering will not be useful.
		**/
		GLuint GetTexture() const;

		/**
		\brief Retrieves a single glyph, given a Unicode codepoint.

		You can use the GlyphQuad result (if present) to render the glyph at the position requested.
		
		\param codepoint The Unicode codepoint of the glyph to fetch. This must not be a control character,
		space character (including 0xA0, the non-breaking space), or 0xAD (the soft-hyphen). And it must
		be less than 256; all higher codepoints will not produce valid glyphs.
		\param ptReference The start point of the glyph.
		\param eRef Defines what the Y-component of \a ptReference means.

		\return A std::pair of GlyphQuad and a bool. If the bool is false, the glyph for the codepoint could
		not be found, and therefore you should not use the GlyphQuad part of the return value.
		**/
		std::pair<GlyphQuad, bool> GetSingleGlyph(unsigned int codepoint, const glm::vec2 &ptReference,
			PointReference eRef = REF_BASELINE) const;

		/**
		\brief Generates a series of GlyphQuad's from a string of text.

		Any codepoints in \a text that are not in the font (control characters, codepoings outside of Latin-1,
		etc) will be ignored. Spaces will use work (though obviously they won't draw anything).
		
		\param text The string of text to get the glyphs for, encoded as UTF-8.
		\param ptReference The starting point for the string. Each glyph will be offset to the right.
		\param eRef Defines what the Y-component of \a ptReference means.

		\return An ordered set of glyphs that represent the string of text.

		\throw InvalidEncodingException Thrown if \a text is not valid UTF-8.
		**/
		std::vector<GlyphQuad> LayoutLine(const std::string& text, const glm::vec2 &ptReference,
			PointReference eRef = REF_BASELINE) const;

		///Returns the baseline-to-baseline height of the font, in pixels.
		int GetLinePixelHeight() const;

		///Returns the width of each character, in pixels. Remember: this is a fixed-width font.
		int GetGlyphAdvanceWidth() const;

	private:
		detail::FontImpl *m_pImpl;

		explicit Font(detail::FontImpl *pImpl);

		friend Font *GenerateFont(FontSizes eSize);

		//Prevent copying
		Font(const Font &);
		Font &operator=(const Font &);
	};

	///@}
}

#endif //FONT_UTIL_H
