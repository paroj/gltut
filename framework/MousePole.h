#ifndef FRAMEWORK_MOUSE_POLE_H
#define FRAMEWORK_MOUSE_POLE_H

#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <glutil/MousePoles.h>

namespace Framework
{
	inline int calc_glut_modifiers()
	{
		int ret = 0;

		int modifiers = glutGetModifiers();
		if(modifiers & GLUT_ACTIVE_SHIFT)
			ret |= glutil::MM_KEY_SHIFT;
		if(modifiers & GLUT_ACTIVE_CTRL)
			ret |= glutil::MM_KEY_CTRL;
		if(modifiers & GLUT_ACTIVE_ALT)
			ret |= glutil::MM_KEY_ALT;

		return ret;
	}

	template<typename Pole>
	inline void ForwardMouseMotion(Pole &forward, int x, int y)
	{
		forward.MouseMove(glm::ivec2(x, y));
	}

	template<typename Pole>
	inline void ForwardMouseButton(Pole &forward, int button, int state, int x, int y)
	{
		int modifiers = calc_glut_modifiers();

		glm::ivec2 mouseLoc = glm::ivec2(x, y);

		glutil::MouseButtons eButton;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			eButton = glutil::MB_LEFT_BTN;
			break;
		case GLUT_MIDDLE_BUTTON:
			eButton = glutil::MB_MIDDLE_BTN;
			break;
		case GLUT_RIGHT_BUTTON:
			eButton = glutil::MB_RIGHT_BTN;
			break;
#ifndef _WIN32
			//Linux Mouse wheel support
		case 3:
			{
				forward.MouseWheel(1, modifiers, mouseLoc);
				return;
			}
		case 4:
			{
				forward.MouseWheel(-1, modifiers, mouseLoc);
				return;
			}
#endif
		default:
			return;
		}

		forward.MouseClick(eButton, state == GLUT_DOWN, modifiers, glm::ivec2(x, y));
	}

	template<typename Pole>
	inline void ForwardMouseWheel(Pole &forward, int wheel, int direction, int x, int y)
	{
		forward.MouseWheel(direction, calc_glut_modifiers(), glm::ivec2(x, y));
	}

}

#endif //FRAMEWORK_MOUSE_POLE_H
