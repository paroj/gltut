// MousePole.cpp: implementation of the MousePole class.
//
//////////////////////////////////////////////////////////////////////

#include <GL/freeglut.h>
#include "framework.h"
#include "MousePole.h"
#include "MatrixStack.h"

#include <math.h>
#include <glm/gtx/quaternion.hpp>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#define PI_2 1.570796325f

glm::vec3 g_UnitZ(0.0f, 0.0f, 1.0f);

namespace Framework
{
	MousePole::MousePole(const glm::vec3 &target, const RadiusDef &radiusDef, ActionButtons eButton)
		: m_lookAt(target)
		, m_radCurrXZAngle(0.0)
		, m_radCurrYAngle(-PI_2 / 2.0f)
		, m_radCurrSpin(0.0f)
		, m_fRadius(20.0f)
		, m_radius(radiusDef)
		, m_glutActionButton(0)
		, m_bIsDragging(false)
	{
		switch(eButton)
		{
		case AB_LEFT_MOUSE: m_glutActionButton = GLUT_LEFT_BUTTON; break;
		case AB_MIDDLE_MOUSE: m_glutActionButton = GLUT_MIDDLE_BUTTON; break;
		case AB_RIGHT_MOUSE: m_glutActionButton = GLUT_RIGHT_BUTTON; break;
		}
	}

	MousePole::~MousePole()
	{
	}

	namespace
	{
		glm::mat4 CalcLookAtMatrix(const glm::vec3 &cameraPt,
			const glm::vec3 &lookPt, const glm::vec3 &upPt)
		{
			glm::vec3 lookDir = glm::normalize(lookPt - cameraPt);
			glm::vec3 upDir = glm::normalize(upPt);

			glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
			glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

			glm::mat4 rotMat(1.0f);
			rotMat[0] = glm::vec4(rightDir, 0.0f);
			rotMat[1] = glm::vec4(perpUpDir, 0.0f);
			rotMat[2] = glm::vec4(-lookDir, 0.0f);

			rotMat = glm::transpose(rotMat);

			glm::mat4 transMat(1.0f);
			transMat[3] = glm::vec4(-cameraPt, 1.0f);

			return rotMat * transMat;
		}
	}

	glm::mat4 MousePole::CalcMatrix() const
	{
		//Compute the position vector along the xz plane.
		float cosa = cosf(m_radCurrXZAngle);
		float sina = sinf(m_radCurrXZAngle);

		glm::vec3 currPos(-sina, 0.0f, cosa);

		//Compute the "up" rotation axis.
		//This axis is a 90 degree rotation around the y axis. Just a component-swap and negate.
		glm::vec3 UpRotAxis;

		UpRotAxis.x = currPos.z;
		UpRotAxis.y = currPos.y;
		UpRotAxis.z = -currPos.x;

		//Now, rotate around this axis by the angle.
		Framework::MatrixStack theStack;

		theStack.SetIdentity();
		theStack.RotateRadians(UpRotAxis, m_radCurrYAngle);
		currPos = glm::vec3(theStack.Top() * glm::vec4(currPos, 0.0));

		//Set the position of the camera.
		glm::vec3 tempVec = currPos * m_radius.fCurrRadius;
		glm::vec3 cameraPosition = tempVec + m_lookAt;

		//Now, compute the up-vector.
		//The direction of the up-vector is the cross-product of currPos and UpRotAxis.
		//Rotate this vector around the currPos axis given m_currSpin.

		glm::vec3 upVec = glm::cross(currPos, UpRotAxis);

		theStack.SetIdentity();
		theStack.RotateRadians(currPos, m_radCurrSpin);
		upVec = glm::vec3(theStack.Top() * glm::vec4(upVec, 0.0));

		return CalcLookAtMatrix(cameraPosition, m_lookAt, upVec);
	}


	void MousePole::BeginDragRotate(const glm::ivec2 &ptStart, RotateMode rotMode)
	{
		m_RotateMode = rotMode;

		m_initialPt = ptStart;

		m_radInitXZAngle = m_radCurrXZAngle;
		m_radInitYAngle = m_radCurrYAngle;
		m_radInitSpin = m_radCurrSpin;

		m_bIsDragging = true;
	}

	void MousePole::OnDragRotate(const glm::ivec2 &ptCurr)
	{
		glm::ivec2 iDiff = ptCurr - m_initialPt;

		switch(m_RotateMode)
		{
		case RM_DUAL_AXIS_ROTATE:
			ProcessXChange(iDiff.x);
			ProcessYChange(iDiff.y);
			break;
		case RM_BIAXIAL_ROTATE:
			if(abs(iDiff.x) > abs(iDiff.y))
				ProcessXChange(iDiff.x, true);
			else
				ProcessYChange(iDiff.y, true);
			break;
		case RM_XZ_AXIS_ROTATE:
			ProcessXChange(iDiff.x);
			break;
		case RM_Y_AXIS_ROTATE:
			ProcessYChange(iDiff.y);
			break;
		case RM_SPIN_VIEW_AXIS:
			ProcessSpinAxis(iDiff.x, iDiff.y);
		default:
			break;
		}
	}
#define SCALE_FACTOR 250

	const float X_CONVERSION_FACTOR = PI_2 / SCALE_FACTOR;
	const float Y_CONVERSION_FACTOR = PI_2 / SCALE_FACTOR;
	const float SPIN_CONV_FACTOR = PI_2 / SCALE_FACTOR;

	void MousePole::ProcessXChange( int iXDiff, bool bClearY )
	{
		m_radCurrXZAngle = (iXDiff * X_CONVERSION_FACTOR) + m_radInitXZAngle;
		if(bClearY)
			m_radCurrYAngle = m_radInitYAngle;
	}

	void MousePole::ProcessYChange( int iYDiff, bool bClearXZ )
	{
		m_radCurrYAngle = (-iYDiff * Y_CONVERSION_FACTOR) + m_radInitYAngle;
		if(bClearXZ)
			m_radCurrXZAngle = m_radInitXZAngle;
	}

	void MousePole::ProcessSpinAxis(int iXDiff, int iYDiff)
	{
		m_radCurrSpin = (iXDiff * SPIN_CONV_FACTOR) + m_radInitSpin;
	}


	void MousePole::EndDragRotate(const glm::ivec2 &ptEnd, bool bKeepResults)
	{
		if(bKeepResults)
		{
			OnDragRotate(ptEnd);
		}
		else
		{
			m_radCurrXZAngle = m_radInitXZAngle;
			m_radCurrYAngle = m_radInitYAngle;
		}

		m_bIsDragging = false;
	}

	void MousePole::MoveCloser( bool bLargeStep )
	{
		if(bLargeStep)
			m_radius.fCurrRadius -= m_radius.fLargeDelta;
		else
			m_radius.fCurrRadius -= m_radius.fSmallDelta;

		if(m_radius.fCurrRadius < m_radius.fMinRadius)
			m_radius.fCurrRadius = m_radius.fMinRadius;
	}

	void MousePole::MoveAway( bool bLargeStep /*= true*/ )
	{
		if(bLargeStep)
			m_radius.fCurrRadius += m_radius.fLargeDelta;
		else
			m_radius.fCurrRadius += m_radius.fSmallDelta;

		if(m_radius.fCurrRadius > m_radius.fMaxRadius)
			m_radius.fCurrRadius = m_radius.fMaxRadius;
	}

	void MousePole::GLUTMouseMove( const glm::ivec2 &position )
	{
		if(m_bIsDragging)
			OnDragRotate(position);
	}

	void MousePole::GLUTMouseButton( int button, int btnState, const glm::ivec2 &position )
	{
		if(btnState == GLUT_DOWN)
		{
			//Ignore all other button presses when dragging.
			if(!m_bIsDragging)
			{
				if(button == m_glutActionButton)
				{
					if(glutGetModifiers() & GLUT_ACTIVE_CTRL)
						this->BeginDragRotate(position, MousePole::RM_BIAXIAL_ROTATE);
					else if(glutGetModifiers() & GLUT_ACTIVE_ALT)
						this->BeginDragRotate(position, MousePole::RM_SPIN_VIEW_AXIS);
					else
						this->BeginDragRotate(position, MousePole::RM_DUAL_AXIS_ROTATE);
				}
			}
		}
		else
		{
			//Ignore all other button releases when not dragging
			if(m_bIsDragging)
			{
				if(button == m_glutActionButton)
				{
					if(m_RotateMode == MousePole::RM_DUAL_AXIS_ROTATE ||
						m_RotateMode == MousePole::RM_SPIN_VIEW_AXIS ||
						m_RotateMode == MousePole::RM_BIAXIAL_ROTATE)
						this->EndDragRotate(position);
				}
			}
		}
	}

	void MousePole::GLUTMouseWheel( int direction, const glm::ivec2 &position )
	{
		if(direction > 0)
			this->MoveCloser(!(glutGetModifiers() & GLUT_ACTIVE_SHIFT));
		else
			this->MoveAway(!(glutGetModifiers() & GLUT_ACTIVE_SHIFT));
	}

	void MousePole::GLUTKeyOffset( int key, float largeIncrement, float smallIncrement )
	{
		switch(key)
		{
		case 'w': OffsetTargetPos(Framework::MousePole::DIR_FORWARD, largeIncrement); break;
		case 's': OffsetTargetPos(Framework::MousePole::DIR_BACKWARD, largeIncrement); break;
		case 'd': OffsetTargetPos(Framework::MousePole::DIR_RIGHT, largeIncrement); break;
		case 'a': OffsetTargetPos(Framework::MousePole::DIR_LEFT, largeIncrement); break;
		case 'e': OffsetTargetPos(Framework::MousePole::DIR_UP, largeIncrement); break;
		case 'q': OffsetTargetPos(Framework::MousePole::DIR_DOWN, largeIncrement); break;

		case 'W': OffsetTargetPos(Framework::MousePole::DIR_FORWARD, smallIncrement); break;
		case 'S': OffsetTargetPos(Framework::MousePole::DIR_BACKWARD, smallIncrement); break;
		case 'D': OffsetTargetPos(Framework::MousePole::DIR_RIGHT, smallIncrement); break;
		case 'A': OffsetTargetPos(Framework::MousePole::DIR_LEFT, smallIncrement); break;
		case 'E': OffsetTargetPos(Framework::MousePole::DIR_UP, smallIncrement); break;
		case 'Q': OffsetTargetPos(Framework::MousePole::DIR_DOWN, smallIncrement); break;
		}
	}

	namespace
	{
		glm::vec3 g_offsets[] =
		{
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f, -1.0f,  0.0f),
			glm::vec3( 0.0f,  0.0f, -1.0f),
			glm::vec3( 0.0f,  0.0f,  1.0f),
			glm::vec3( 1.0f,  0.0f,  0.0f),
			glm::vec3(-1.0f,  0.0f,  0.0f),
		};
	}

	void MousePole::OffsetTargetPos( TargetOffsetDir eDir, float worldDistance )
	{
		glm::vec3 offsetDir = g_offsets[eDir];
		OffsetTargetPos(offsetDir * worldDistance);
	}

	void MousePole::OffsetTargetPos( const glm::vec3 &cameraOffset )
	{
		glm::mat4 currMat = CalcMatrix();
		glm::fquat orientation = glm::quat_cast(currMat);

		glm::fquat invOrient = glm::conjugate(orientation);
		glm::vec3 worldOffset = invOrient * cameraOffset;

		m_lookAt += worldOffset;
	}
}

