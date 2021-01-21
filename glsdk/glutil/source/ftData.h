/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/




#ifndef FONT_DATA_DEFINITION_UTIL_H
#define FONT_DATA_DEFINITION_UTIL_H

namespace glutil
{
	namespace detail
	{
		struct TypefaceMetrics
		{
			int imageWidth;
			int imageHeight;
			
			int advanceWidth;
			int lineHeight;
			
			int maxGlyphBaselineOffsetToTop;
			int maxGlyphBaselineOffsetToBottom;
			
			int numGlyphs;
		};

		struct Glyph
		{
			unsigned int codepoint;
			
			int baselineOffsetToLeft; //The offset from the baseline to the left edge of the glyph. Can be negative.
			int baselineOffsetToTop;  //The offset from the baseline to the top edge of the glyph. Can be negative.
			
			int pixelWidth;
			int pixelHeight;
			
			float bottomLeftTexCoordS;
			float bottomLeftTexCoordT;
			
			float topRightTexCoordS;
			float topRightTexCoordT;
		};

		extern const TypefaceMetrics small_Typeface;
		extern const Glyph small_Glyphs[];
		extern const unsigned char small_Image[];

		extern const TypefaceMetrics medium_Typeface;
		extern const Glyph medium_Glyphs[];
		extern const unsigned char medium_Image[];

		extern const TypefaceMetrics large_Typeface;
		extern const Glyph large_Glyphs[];
		extern const unsigned char large_Image[];

		extern const TypefaceMetrics giant_Typeface;
		extern const Glyph giant_Glyphs[];
		extern const unsigned char giant_Image[];


	}
}
#endif //FONT_DATA_DEFINITION_UTIL_H
