#ifndef FRAMEWORK_MOUSE_POLE_H
#define FRAMEWORK_MOUSE_POLE_H

#include <glm/glm.hpp>

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
		MousePole(glm::vec3 target, const RadiusDef &radiusDef);
		virtual ~MousePole();

		void GetCurrVectors(glm::vec3 &pos, glm::vec3 &lookAt, glm::vec3 &upVec);
		glm::mat4 CalcMatrix() const;

		enum RotateMode
		{
			RM_DUAL_AXIS_ROTATE,
			RM_XZ_AXIS_ROTATE,
			RM_Y_AXIS_ROTATE,
			RM_SPIN_VIEW_AXIS,
		};

		void GLUTMouseMove(const glm::ivec2 &position);
		void GLUTMouseButton(int button, int btnState, const glm::ivec2 &position);
		void GLUTMouseWheel(int direction, const glm::ivec2 &position);

	protected:
		glm::vec3 m_lookAt;

		float m_radCurrXZAngle;	//Angle around the y-axis. In radians
		float m_radCurrYAngle;		//Angle above the xz plane. In radians
		float m_radCurrSpin;		//Angle spin around the look-at direction. Changes up-vector.
		float m_fRadius;		//Camera distance
		RadiusDef m_radius;


		//Used when rotating.
		RotateMode m_RotateMode;
		bool m_bIsDragging;

		glm::ivec2 m_initialPt;

		float m_radInitXZAngle;
		float m_radInitYAngle;
		float m_radInitSpin;

		void ProcessXChange(int iXDiff);
		void ProcessYChange(int iYDiff);
		void ProcessSpinAxis(int iXDiff, int iYDiff);

		void BeginDragRotate(const glm::ivec2 &ptStart, RotateMode rotMode = RM_DUAL_AXIS_ROTATE);
		void OnDragRotate(const glm::ivec2 &ptCurr);
		void EndDragRotate(const glm::ivec2 &ptEnd, bool bKeepResults = true);
		bool IsDragging() {return m_bIsDragging;}

		void MoveCloser(bool bLargeStep = true);
		void MoveAway(bool bLargeStep = true);
	};
}

#endif //FRAMEWORK_MOUSE_POLE_H
