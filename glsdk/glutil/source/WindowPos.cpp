//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include "glutil/WindowPos.h"


namespace glutil
{
	glm::ivec2 CalcWindowPosition( const glm::ivec2 &wndSize, const glm::ivec2 &desktopSize,
		HorizWindowPos hpos, VertWindowPos vpos )
	{
		glm::ivec2 wndPosition(0, 0);

		switch(vpos)
		{
		case WV_CENTER:
			wndPosition.y = (desktopSize.y - wndSize.y) / 2;
			break;
		case WV_TOP:
			wndPosition.y = 0;
			break;
		case WV_BOTTOM:
			wndPosition.y = desktopSize.y - wndSize.y;
			break;
		}

		switch(hpos)
		{
		case WH_CENTER:
			wndPosition.x = (desktopSize.x - wndSize.x) / 2;
			break;
		case WH_LEFT:
			wndPosition.x = 0;
			break;
		case WH_RIGHT:
			wndPosition.x = desktopSize.x - wndSize.x;
			break;
		}

		return wndPosition;
	}
}

