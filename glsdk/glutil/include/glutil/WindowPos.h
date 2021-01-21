/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef WINDOW_POSITION_UTIL_H
#define WINDOW_POSITION_UTIL_H

/**
\file
\brief Contains functions to \ref module_glutil_wndpos "position the window relative to the desktop".
**/

#include <glm/glm.hpp>

namespace glutil
{
	///\addtogroup module_glutil_wndpos
	///@{

	///Horizontal window positions.
	enum HorizWindowPos
	{
		WH_CENTER,		///<Horizontally position the window in the center of the screen.
		WH_LEFT,		///<Horizontally position the window on the left edge of the screen.
		WH_RIGHT,		///<Horizontally position the window on the right edge of the screen.
	};

	///Vertical window positions.
	enum VertWindowPos
	{
		WV_CENTER,		///<Vertically position the window in the center of the screen.
		WV_TOP,			///<Vertically position the window on the top edge of the screen.
		WV_BOTTOM,		///<Vertically position the window on the bottom edge of the screen.
	};

	/**
	\brief Compute the position of the window relative to the desktop area.

	This function can be used to center a window or place it along the edges of the desktop.

	\param wndSize The size of the window.
	\param desktopSize The size of the desktop area the window will be placed in.
	\param hpos The desired horizontal position of the window, relative to the desktop.
	\param vpos The desired vertical position of the window, relative to the desktop.

	\return The position of the top-left coordinate of the window.
	**/
	glm::ivec2 CalcWindowPosition(const glm::ivec2 &wndSize, const glm::ivec2 &desktopSize,
		HorizWindowPos hpos = WH_CENTER, VertWindowPos vpos = WV_CENTER);
	///@}
}

#endif //WINDOW_POSITION_UTIL_H