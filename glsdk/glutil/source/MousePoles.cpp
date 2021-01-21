//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <stdio.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glutil/MousePoles.h"

#ifndef M_PI
#define M_PI 3.14159265f
#endif

const float PI_2 = 1.570796325f;

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


namespace glutil
{
	ObjectPole::ObjectPole( const ObjectData &initialData, float rotateScale,
		MouseButtons actionButton, const ViewProvider *pLookatProvider )
		: m_pView(pLookatProvider)
		, m_po(initialData)
		, m_initialPo(initialData)
		, m_rotateScale(rotateScale)
		, m_actionButton(actionButton)
		, m_bIsDragging(false)
	{}

	glm::mat4 ObjectPole::CalcMatrix() const
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(m_po.position, 1.0f);

		return translateMat * glm::mat4_cast(m_po.orientation);
	}

	void ObjectPole::SetRotationScale( float rotateScale )
	{
		m_rotateScale = rotateScale;
	}

	void ObjectPole::Reset()
	{
		if(!m_bIsDragging)
			m_po = m_initialPo;
	}

	namespace
	{
		///ObjectPole::NUM_AXES
		glm::vec3 g_axisVectors[] =
		{
			glm::vec3(1.0, 0.0, 0.0),
			glm::vec3(0.0, 1.0, 0.0),
			glm::vec3(0.0, 0.0, 1.0),
		};

		glm::fquat CalcRotationQuat(int eAxis, float degAngle)
		{
			return glm::angleAxis(degAngle, g_axisVectors[eAxis]);
		}
	}


	void ObjectPole::RotateWorldDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		m_po.orientation = glm::normalize(rot * (bFromInitial ? m_startDragOrient : m_po.orientation));
	}

	void ObjectPole::RotateLocalDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		m_po.orientation = glm::normalize((bFromInitial ? m_startDragOrient : m_po.orientation) * rot);
	}

	void ObjectPole::RotateViewDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		if(m_pView)
		{
			glm::fquat viewQuat = glm::quat_cast(m_pView->CalcMatrix());
			glm::fquat invViewQuat = glm::conjugate(viewQuat);
			m_po.orientation = glm::normalize((invViewQuat * rot * viewQuat) *
				(bFromInitial ? m_startDragOrient : m_po.orientation));
		}
		else
			RotateWorldDegrees(rot, bFromInitial);
	}

	void ObjectPole::MouseMove( const glm::ivec2 &position )
	{
		if(m_bIsDragging)
		{
			glm::ivec2 iDiff = position - m_prevMousePos;

			switch(m_RotateMode)
			{
			case RM_DUAL_AXIS:
				{
					glm::fquat rot = CalcRotationQuat(AXIS_Y, iDiff.x * m_rotateScale);
					rot = glm::normalize(
						CalcRotationQuat(AXIS_X, iDiff.y * m_rotateScale) * rot);
					RotateViewDegrees(rot);
				}
				break;
			case RM_BIAXIAL:
				{
					glm::ivec2 iInitDiff = position - m_startDragMousePos;

					Axis eAxis;
					float degAngle;
					if(abs(iInitDiff.x) > abs(iInitDiff.y))
					{
						eAxis = AXIS_Y;
						degAngle = iInitDiff.x * m_rotateScale;
					}
					else
					{
						eAxis = AXIS_X;
						degAngle = iInitDiff.y * m_rotateScale;
					}

					glm::fquat rot = CalcRotationQuat(eAxis, degAngle);
					RotateViewDegrees(rot, true);
				}
				break;
			case RM_SPIN:
				RotateViewDegrees(CalcRotationQuat(AXIS_Z, -iDiff.x * m_rotateScale));
				break;
			}

			m_prevMousePos = position;
		}
	}

	void ObjectPole::MouseClick( MouseButtons button, bool isPressed,
		int modifiers, const glm::ivec2 &position )
	{
		if(isPressed)
		{
			//Ignore button presses when dragging.
			if(!m_bIsDragging)
			{
				if(button == m_actionButton)
				{
					if(modifiers & MM_KEY_ALT)
						m_RotateMode = RM_SPIN;
					else if(modifiers & MM_KEY_CTRL)
						m_RotateMode = RM_BIAXIAL;
					else
						m_RotateMode = RM_DUAL_AXIS;

					m_prevMousePos = position;
					m_startDragMousePos = position;
					m_startDragOrient = m_po.orientation;

					m_bIsDragging = true;
				}
			}
		}
		else
		{
			//Ignore up buttons if not dragging.
			if(m_bIsDragging)
			{
				if(button == m_actionButton)
				{
					MouseMove(position);

					m_bIsDragging = false;
				}
			}
		}
	}

	void ObjectPole::MouseWheel( int direction, int modifiers, const glm::ivec2 &position )
	{

	}

	void ObjectPole::CharPress( char key )
	{

	}

	ViewPole::ViewPole( const ViewData &initialView, const ViewScale &viewScale,
		MouseButtons actionButton, bool bRightKeyboardCtrls )
		: m_currView(initialView)
		, m_viewScale(viewScale)
		, m_initialView(initialView)
		, m_actionButton(actionButton)
		, m_bRightKeyboardCtrls(bRightKeyboardCtrls)
		, m_bIsDragging(false)
	{}

	glm::mat4 ViewPole::CalcMatrix() const
	{
		glm::mat4 theMat(1.0f);

		//Remember: these transforms are in reverse order.

		//In this space, we are facing in the correct direction. Which means that the camera point
		//is directly behind us by the radius number of units.
		theMat = glm::translate(theMat, glm::vec3(0.0f, 0.0f, -m_currView.radius));

		//Rotate the world to look in the right direction..
		glm::fquat fullRotation = glm::angleAxis(m_currView.degSpinRotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
			m_currView.orient;
		theMat = theMat * glm::mat4_cast(fullRotation);

		//Translate the world by the negation of the lookat point, placing the origin at the
		//lookat point.
		theMat = glm::translate(theMat, -m_currView.targetPos);

		return theMat;
	}

	void ViewPole::Reset()
	{
		if(!m_bIsDragging)
			m_currView = m_initialView;
	}


	void ViewPole::SetRotationScale( float rotateScale )
	{
		m_viewScale.rotationScale = rotateScale;
	}

	void ViewPole::ProcessXChange( int iXDiff, bool bClearY )
	{
		float degAngleDiff = (iXDiff * m_viewScale.rotationScale);

		//Rotate about the world-space Y axis.
		m_currView.orient = m_startDragOrient * glm::angleAxis(degAngleDiff, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void ViewPole::ProcessYChange( int iYDiff, bool bClearXZ )
	{
		float degAngleDiff = (iYDiff * m_viewScale.rotationScale);

		//Rotate about the local-space X axis.
		m_currView.orient = glm::angleAxis(degAngleDiff, glm::vec3(1.0f, 0.0f, 0.0f)) * m_startDragOrient;
	}

	void ViewPole::ProcessXYChange( int iXDiff, int iYDiff )
	{
		float degXAngleDiff = (iXDiff * m_viewScale.rotationScale);
		float degYAngleDiff = (iYDiff * m_viewScale.rotationScale);

		//Rotate about the world-space Y axis.
		m_currView.orient = m_startDragOrient * glm::angleAxis(degXAngleDiff, glm::vec3(0.0f, 1.0f, 0.0f));
		//Rotate about the local-space X axis.
		m_currView.orient = glm::angleAxis(degYAngleDiff, glm::vec3(1.0f, 0.0f, 0.0f)) * m_currView.orient;
	}

	void ViewPole::ProcessSpinAxis( int iXDiff, int iYDiff )
	{
		float degSpinDiff = (iXDiff * m_viewScale.rotationScale);
		m_currView.degSpinRotation = degSpinDiff + m_degStarDragSpin;
	}

	void ViewPole::BeginDragRotate( const glm::ivec2 &ptStart, RotateMode rotMode )
	{
		m_RotateMode = rotMode;

		m_startDragMouseLoc = ptStart;

		m_degStarDragSpin = m_currView.degSpinRotation;

		m_startDragOrient = m_currView.orient;

		m_bIsDragging = true;
	}

	void ViewPole::OnDragRotate( const glm::ivec2 &ptCurr )
	{
		glm::ivec2 iDiff = ptCurr - m_startDragMouseLoc;

		switch(m_RotateMode)
		{
		case RM_DUAL_AXIS_ROTATE:
			ProcessXYChange(iDiff.x, iDiff.y);
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

	void ViewPole::EndDragRotate( const glm::ivec2 &ptEnd, bool bKeepResults )
	{
		if(bKeepResults)
		{
			OnDragRotate(ptEnd);
		}
		else
		{
			m_currView.orient = m_startDragOrient;
		}

		m_bIsDragging = false;
	}

	void ViewPole::MoveCloser( bool bLargeStep )
	{
		if(bLargeStep)
			m_currView.radius -= m_viewScale.largeRadiusDelta;
		else
			m_currView.radius -= m_viewScale.smallRadiusDelta;

		if(m_currView.radius < m_viewScale.minRadius)
			m_currView.radius = m_viewScale.minRadius;
	}

	void ViewPole::MoveAway( bool bLargeStep )
	{
		if(bLargeStep)
			m_currView.radius += m_viewScale.largeRadiusDelta;
		else
			m_currView.radius += m_viewScale.smallRadiusDelta;

		if(m_currView.radius > m_viewScale.maxRadius)
			m_currView.radius = m_viewScale.maxRadius;
	}

	void ViewPole::MouseMove( const glm::ivec2 &position )
	{
		if(m_bIsDragging)
			OnDragRotate(position);
	}

	void ViewPole::MouseClick( MouseButtons button, bool isPressed, int modifiers,
		const glm::ivec2 &position )
	{
		if(isPressed)
		{
			//Ignore all other button presses when dragging.
			if(!m_bIsDragging)
			{
				if(button == m_actionButton)
				{
					if(modifiers & MM_KEY_CTRL)
						this->BeginDragRotate(position, ViewPole::RM_BIAXIAL_ROTATE);
					else if(modifiers & MM_KEY_ALT)
						this->BeginDragRotate(position, ViewPole::RM_SPIN_VIEW_AXIS);
					else
						this->BeginDragRotate(position, ViewPole::RM_DUAL_AXIS_ROTATE);
				}
			}
		}
		else
		{
			//Ignore all other button releases when not dragging
			if(m_bIsDragging)
			{
				if(button == m_actionButton)
				{
					if(m_RotateMode == ViewPole::RM_DUAL_AXIS_ROTATE ||
						m_RotateMode == ViewPole::RM_SPIN_VIEW_AXIS ||
						m_RotateMode == ViewPole::RM_BIAXIAL_ROTATE)
						this->EndDragRotate(position);
				}
			}
		}
	}

	void ViewPole::MouseWheel( int direction, int modifiers,
		const glm::ivec2 &position )
	{
		if(direction > 0)
			this->MoveCloser(!(modifiers & MM_KEY_SHIFT));
		else
			this->MoveAway(!(modifiers & MM_KEY_SHIFT));

	}

	void ViewPole::CharPress( char key )
	{
		if(m_bRightKeyboardCtrls)
		{
			switch(key)
			{
			case 'i': OffsetTargetPos(ViewPole::DIR_FORWARD, m_viewScale.largePosOffset); break;
			case 'k': OffsetTargetPos(ViewPole::DIR_BACKWARD, m_viewScale.largePosOffset); break;
			case 'l': OffsetTargetPos(ViewPole::DIR_RIGHT, m_viewScale.largePosOffset); break;
			case 'j': OffsetTargetPos(ViewPole::DIR_LEFT, m_viewScale.largePosOffset); break;
			case 'o': OffsetTargetPos(ViewPole::DIR_UP, m_viewScale.largePosOffset); break;
			case 'u': OffsetTargetPos(ViewPole::DIR_DOWN, m_viewScale.largePosOffset); break;

			case 'I': OffsetTargetPos(ViewPole::DIR_FORWARD, m_viewScale.smallPosOffset); break;
			case 'K': OffsetTargetPos(ViewPole::DIR_BACKWARD, m_viewScale.smallPosOffset); break;
			case 'L': OffsetTargetPos(ViewPole::DIR_RIGHT, m_viewScale.smallPosOffset); break;
			case 'J': OffsetTargetPos(ViewPole::DIR_LEFT, m_viewScale.smallPosOffset); break;
			case 'O': OffsetTargetPos(ViewPole::DIR_UP, m_viewScale.smallPosOffset); break;
			case 'U': OffsetTargetPos(ViewPole::DIR_DOWN, m_viewScale.smallPosOffset); break;
			}
		}
		else
		{
			switch(key)
			{
			case 'w': OffsetTargetPos(ViewPole::DIR_FORWARD, m_viewScale.largePosOffset); break;
			case 's': OffsetTargetPos(ViewPole::DIR_BACKWARD, m_viewScale.largePosOffset); break;
			case 'd': OffsetTargetPos(ViewPole::DIR_RIGHT, m_viewScale.largePosOffset); break;
			case 'a': OffsetTargetPos(ViewPole::DIR_LEFT, m_viewScale.largePosOffset); break;
			case 'e': OffsetTargetPos(ViewPole::DIR_UP, m_viewScale.largePosOffset); break;
			case 'q': OffsetTargetPos(ViewPole::DIR_DOWN, m_viewScale.largePosOffset); break;

			case 'W': OffsetTargetPos(ViewPole::DIR_FORWARD, m_viewScale.smallPosOffset); break;
			case 'S': OffsetTargetPos(ViewPole::DIR_BACKWARD, m_viewScale.smallPosOffset); break;
			case 'D': OffsetTargetPos(ViewPole::DIR_RIGHT, m_viewScale.smallPosOffset); break;
			case 'A': OffsetTargetPos(ViewPole::DIR_LEFT, m_viewScale.smallPosOffset); break;
			case 'E': OffsetTargetPos(ViewPole::DIR_UP, m_viewScale.smallPosOffset); break;
			case 'Q': OffsetTargetPos(ViewPole::DIR_DOWN, m_viewScale.smallPosOffset); break;
			}
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

	void ViewPole::OffsetTargetPos( TargetOffsetDir eDir, float worldDistance )
	{
		glm::vec3 offsetDir = g_offsets[eDir];
		OffsetTargetPos(offsetDir * worldDistance);
	}

	void ViewPole::OffsetTargetPos( const glm::vec3 &cameraOffset )
	{
		glm::mat4 currMat = CalcMatrix();
		glm::fquat orientation = glm::quat_cast(currMat);

		glm::fquat invOrient = glm::conjugate(orientation);
		glm::vec3 worldOffset = invOrient * cameraOffset;

		m_currView.targetPos += worldOffset;
	}
}

