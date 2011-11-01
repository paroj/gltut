#ifndef FRAMEWORK_MOUSE_POLE_H
#define FRAMEWORK_MOUSE_POLE_H

#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <glutil/MousePoles.h>

namespace Framework
{
	struct RadiusDef
	{
		float fCurrRadius;
		float fMinRadius;
		float fMaxRadius;
		float fLargeDelta;
		float fSmallDelta;
	};

	class MousePole  
	{
	public:
		enum ActionButtons
		{
			AB_LEFT_MOUSE,
			AB_MIDDLE_MOUSE,
			AB_RIGHT_MOUSE,
		};

		MousePole(const glm::vec3 &target, const RadiusDef &radiusDef,
			ActionButtons eButton = AB_LEFT_MOUSE);
		virtual ~MousePole();

		void GetCurrVectors(glm::vec3 &pos, glm::vec3 &lookAt, glm::vec3 &upVec);
		glm::mat4 CalcMatrix() const;

		glm::vec3 GetLookAtPos() const {return m_lookAt;}
		float GetLookAtDistance() const {return m_radius.fCurrRadius;}

		void GLUTMouseMove(const glm::ivec2 &position);
		void GLUTMouseButton(int button, int btnState, const glm::ivec2 &position);
		void GLUTMouseWheel(int direction, const glm::ivec2 &position);
		void GLUTKeyOffset(int key, float largeIncrement, float smallIncrement);

		bool IsDragging() const {return m_bIsDragging;}

		enum TargetOffsetDir
		{
			DIR_UP,
			DIR_DOWN,
			DIR_FORWARD,
			DIR_BACKWARD,
			DIR_RIGHT,
			DIR_LEFT,
		};

		void OffsetTargetPos(TargetOffsetDir eDir, float worldDistance);
		void OffsetTargetPos(const glm::vec3 &cameraOffset);

	protected:
		enum RotateMode
		{
			RM_DUAL_AXIS_ROTATE,
			RM_BIAXIAL_ROTATE,
			RM_XZ_AXIS_ROTATE,
			RM_Y_AXIS_ROTATE,
			RM_SPIN_VIEW_AXIS,
		};

		glm::vec3 m_lookAt;

		float m_radCurrXZAngle;	//Angle around the y-axis. In radians
		float m_radCurrYAngle;		//Angle above the xz plane. In radians
		float m_radCurrSpin;		//Angle spin around the look-at direction. Changes up-vector.
		float m_fRadius;		//Camera distance
		RadiusDef m_radius;

		int m_glutActionButton;

		//Used when rotating.
		RotateMode m_RotateMode;
		bool m_bIsDragging;

		glm::ivec2 m_initialPt;

		float m_radInitXZAngle;
		float m_radInitYAngle;
		float m_radInitSpin;

		void ProcessXChange(int iXDiff, bool bClearY = false);
		void ProcessYChange(int iYDiff, bool bClearXZ = false);
		void ProcessSpinAxis(int iXDiff, int iYDiff);

		void BeginDragRotate(const glm::ivec2 &ptStart, RotateMode rotMode = RM_DUAL_AXIS_ROTATE);
		void OnDragRotate(const glm::ivec2 &ptCurr);
		void EndDragRotate(const glm::ivec2 &ptEnd, bool bKeepResults = true);
		bool IsDragging() {return m_bIsDragging;}

		void MoveCloser(bool bLargeStep = true);
		void MoveAway(bool bLargeStep = true);
	};

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
#ifdef LOAD_X11
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
