//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include <limits>
#include <string>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glutil/Font.h"
#include "ftData.h"


namespace glutil
{
	namespace detail
	{
		const unsigned int BAD_GLYPH_INDEX = std::numeric_limits<unsigned int>::max();
		const unsigned int SPACE_GLYPH_INDEX = std::numeric_limits<unsigned int>::max() - 1;
		const unsigned int IGNORE_GLYPH_INDEX = std::numeric_limits<unsigned int>::max() - 2;

		unsigned int ConvertCodepointToGlyphIndex(unsigned int codepoint)
		{
			//Soft-hyphen. Should be handled at a higher level than this; for our sake, we ignore it.
			if(codepoint == 0xAD)
				return IGNORE_GLYPH_INDEX;

			if(codepoint > 0xAD)
				codepoint--;

			//Latin-1 control characters.
			if(0x7E < codepoint && codepoint < 0xA0)
				return IGNORE_GLYPH_INDEX;

			if(codepoint == 0xA0) //NBSP
				return SPACE_GLYPH_INDEX;

			if(codepoint > 0x7E)
				codepoint -= (0xA1 - 0x7F);

			//ASCII control characters.
			if(codepoint < 0x20) 
				return IGNORE_GLYPH_INDEX;

			if(codepoint == 0x20) //Space
				return SPACE_GLYPH_INDEX;

			codepoint -= 0x21;

			//Too high.
			if(codepoint >= 188)
				return BAD_GLYPH_INDEX;

			return codepoint;
		}

		GLenum CalcInternalFormat()
		{
			return gl::R8;
		}

		GLenum CalcFormat()
		{
			return gl::RED;
		}

		class FontImpl
		{
		public:
			FontImpl(const TypefaceMetrics &metrics, const Glyph *glyphs, const unsigned char* imageData)
				: m_metrics(metrics)
				, m_glyphs(glyphs)
				, m_texture(0)
			{
				gl::GenTextures(1, &m_texture);

				gl::PixelStorei(gl::UNPACK_SWAP_BYTES, gl::FALSE_);
				gl::PixelStorei(gl::UNPACK_LSB_FIRST, gl::FALSE_);
				gl::PixelStorei(gl::UNPACK_ROW_LENGTH, 0);
				gl::PixelStorei(gl::UNPACK_SKIP_ROWS, 0);
				gl::PixelStorei(gl::UNPACK_SKIP_PIXELS, 0);
				gl::PixelStorei(gl::UNPACK_IMAGE_HEIGHT, 0);
				gl::PixelStorei(gl::UNPACK_SKIP_IMAGES, 0);
				gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);

/*
				if(gl::exts::var_EXT_direct_state_access)
				{
					if(gl::exts::var_ARB_texture_storage)
					{
						gl::TextureStorage2DEXT(m_texture, gl::TEXTURE_2D, 1, CalcInternalFormat(),
							m_metrics.imageWidth, m_metrics.imageHeight);
					}
					else
					{
						gl::TextureImage2DEXT(m_texture, gl::TEXTURE_2D, 0, CalcInternalFormat(),
							m_metrics.imageWidth, m_metrics.imageHeight, 0, CalcFormat(),
							gl::UNSIGNED_BYTE, NULL);
						gl::TextureParameteriEXT(m_texture, gl::TEXTURE_2D,
							gl::TEXTURE_BASE_LEVEL, 0);
						gl::TextureParameteriEXT(m_texture, gl::TEXTURE_2D,
							gl::TEXTURE_MAX_LEVEL, 0);
					}

					gl::TextureSubImage2DEXT(m_texture, gl::TEXTURE_2D, 0, 0, 0,
						m_metrics.imageWidth, m_metrics.imageHeight, CalcFormat(),
						gl::UNSIGNED_BYTE, imageData);
				}
				else
*/
				{
					gl::BindTexture(gl::TEXTURE_2D, m_texture);

					if(gl::exts::var_ARB_texture_storage || glload::IsVersionGEQ(4, 2))
					{
						gl::TexStorage2D(gl::TEXTURE_2D, 1, CalcInternalFormat(),
							m_metrics.imageWidth, m_metrics.imageHeight);
					}
					else
					{
						gl::TexImage2D(gl::TEXTURE_2D, 0, CalcInternalFormat(),
							m_metrics.imageWidth, m_metrics.imageHeight, 0, CalcFormat(),
							gl::UNSIGNED_BYTE, NULL);
						gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_BASE_LEVEL, 0);
						gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAX_LEVEL, 0);
					}

					gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
					gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);

					gl::TexSubImage2D(gl::TEXTURE_2D, 0, 0, 0,
						m_metrics.imageWidth, m_metrics.imageHeight, CalcFormat(),
						gl::UNSIGNED_BYTE, imageData);

					gl::BindTexture(gl::TEXTURE_2D, 0);
				}
			}

			~FontImpl()
			{
				gl::DeleteTextures(1, &m_texture);
				m_texture = 0;
			}

			std::pair<GlyphQuad, bool> GetSingleGlyph(unsigned int codepoint, const glm::vec2 &ptReference,
				PointReference eRef = REF_BASELINE) const
			{
				unsigned int glyphIx = ConvertCodepointToGlyphIndex(codepoint);
				if(glyphIx == BAD_GLYPH_INDEX ||
					glyphIx == IGNORE_GLYPH_INDEX ||
					glyphIx == SPACE_GLYPH_INDEX)
				{
					return std::make_pair(GlyphQuad(glm::vec2(0.0f), glm::vec2(0.0f),
						glm::vec2(0.0f), glm::vec2(0.0f)), false);
				}

				glm::vec2 baseline = CalcBaseline(ptReference, eRef);

				return std::make_pair(GetQuad(baseline, m_glyphs[glyphIx]), true);
			}

			std::vector<GlyphQuad> LayoutLine(const std::string& theRef, const glm::vec2 &ptReference,
				PointReference eRef = REF_BASELINE) const
			{
				std::vector<GlyphQuad> ret;

				const char *text = theRef.data();
				const size_t length = theRef.size();

				glm::vec2 baseline = CalcBaseline(ptReference, eRef);

				const unsigned char *currPos = reinterpret_cast<const unsigned char*>(text);
				const unsigned char * const endPos = currPos + length;
				for(; currPos != endPos; ++currPos)
				{
					unsigned int codepoint = *currPos;
					
					//Parse UTF-8
					if(codepoint & 0x80)
					{
						unsigned int build = codepoint;
						int bit = 5;
						for(; (codepoint & (0x1 << (bit + 1))) && (bit != 2); --bit)
						{
							++currPos;
							if(!((*currPos & 0x80) && (~(*currPos) & 0x40)))
								throw InvalidEncodingException();

							//Set the top bits to 1's. Leave the last 6, since that's what we want
							build <<= 6;
							build += *currPos & 0x3F;
						}

						if((codepoint & (0x1 << bit)) != 0)
							throw InvalidEncodingException();

						unsigned int mask = 0x1 << (bit + 1);
						//For each extra byte, we must shift by 6 bits.
						mask <<= 6 * (6 - (bit + 1));

						//Keep every bit below this point.
						--mask;
						codepoint = build & mask;
					}

					unsigned int glyphIx = ConvertCodepointToGlyphIndex(codepoint);

					if(glyphIx == BAD_GLYPH_INDEX || glyphIx == IGNORE_GLYPH_INDEX)
						continue;

					if(glyphIx == SPACE_GLYPH_INDEX)
					{
						baseline.x += m_metrics.advanceWidth;
						continue;
					}

					ret.push_back(GetQuad(baseline, m_glyphs[glyphIx]));
					baseline.x += m_metrics.advanceWidth;
				}

				return ret;
			}

		
			GLuint GetTexture() const {return m_texture;}

			int GetLinePixelHeight() const {return m_metrics.lineHeight;}
			int GetGlyphAdvanceWidth() const {return m_metrics.advanceWidth;}

		private:
			TypefaceMetrics m_metrics;
			const Glyph *m_glyphs;
			GLuint m_texture;

			GlyphQuad GetQuad(const glm::vec2 &baseline, const Glyph &theGlyph) const
			{
				glm::vec2 bottomLeft = baseline;
				bottomLeft.x += theGlyph.baselineOffsetToLeft;
				bottomLeft.y += theGlyph.baselineOffsetToTop - theGlyph.pixelHeight;	//Invert for top-left.

				glm::vec2 topRight = bottomLeft;
				topRight.x += theGlyph.pixelWidth;
				topRight.y += theGlyph.pixelHeight;			//Invert for top-left.

				return GlyphQuad(
					bottomLeft,
					glm::vec2(theGlyph.bottomLeftTexCoordS, theGlyph.bottomLeftTexCoordT),
					topRight,
					glm::vec2(theGlyph.topRightTexCoordS, theGlyph.topRightTexCoordT));

			}

			glm::vec2 CalcBaseline(const glm::vec2 &ptReference, PointReference eRef = REF_BASELINE) const
			{
				glm::vec2 baseline = ptReference;
				switch(eRef)
				{
				case REF_BASELINE:
					break;
				case REF_TOP:
					baseline.y -= m_metrics.maxGlyphBaselineOffsetToTop;	//Invert for top-left
					break;
				case REF_BOTTOM:
					baseline.y += m_metrics.maxGlyphBaselineOffsetToBottom;		//Invert for top-left
					break;
				}

				return baseline;
			}
		};
	}

	Font *GenerateFont( FontSizes eSize )
	{
		detail::FontImpl *pImpl = NULL;
		switch(eSize)
		{
		case FONT_SIZE_SMALL:
			pImpl = new detail::FontImpl(detail::small_Typeface, detail::small_Glyphs, detail::small_Image);
			break;
		case FONT_SIZE_MEDIUM:
			pImpl = new detail::FontImpl(detail::medium_Typeface, detail::medium_Glyphs, detail::medium_Image);
			break;
		case FONT_SIZE_LARGE:
			pImpl = new detail::FontImpl(detail::large_Typeface, detail::large_Glyphs, detail::large_Image);
			break;
		case FONT_SIZE_GIANT:
			pImpl = new detail::FontImpl(detail::giant_Typeface, detail::giant_Glyphs, detail::giant_Image);
			break;
		}

		return new Font(pImpl);
	}

	std::vector<glm::vec2> GlyphQuad::GetPositions() const
	{
		std::vector<glm::vec2> ret;
		ret.reserve(4);

		ret.push_back(glm::vec2(m_ptBottomLeft.x, m_ptTopRight.y));
		ret.push_back(m_ptBottomLeft);
		ret.push_back(m_ptTopRight);
		ret.push_back(glm::vec2(m_ptTopRight.x, m_ptBottomLeft.y));

		return ret;
	}

	std::vector<glm::vec2> GlyphQuad::GetTexCoords() const
	{
		std::vector<glm::vec2> ret;
		ret.reserve(4);

		ret.push_back(glm::vec2(m_tcBottomLeft.x, m_tcTopRight.y));
		ret.push_back(m_tcBottomLeft);
		ret.push_back(m_tcTopRight);
		ret.push_back(glm::vec2(m_tcTopRight.x, m_tcBottomLeft.y));

		return ret;
	}

	Font::Font( detail::FontImpl *pImpl )
		: m_pImpl(pImpl)
	{}

	Font::~Font()
	{
		delete m_pImpl;
	}

	GLuint Font::GetTexture() const
	{
		return m_pImpl->GetTexture();
	}

	std::pair<GlyphQuad, bool> Font::GetSingleGlyph( unsigned int codepoint, const glm::vec2 &ptReference,
		PointReference eRef ) const
	{
		return m_pImpl->GetSingleGlyph(codepoint, ptReference, eRef);
	}

	std::vector<GlyphQuad> Font::LayoutLine( const std::string& text,
		const glm::vec2 &ptReference, PointReference eRef ) const
	{
		return m_pImpl->LayoutLine(text, ptReference, eRef);
	}

	int Font::GetLinePixelHeight() const
	{
		return m_pImpl->GetLinePixelHeight();
	}

	int Font::GetGlyphAdvanceWidth() const
	{
		return m_pImpl->GetGlyphAdvanceWidth();
	}
}

