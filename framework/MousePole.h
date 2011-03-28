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
}

#endif //FRAMEWORK_MOUSE_POLE_H
