#include <GL/freeglut.h>
#include "framework.h"
#include "ObjectPole.h"
#include "MousePole.h"

#include <math.h>

#include <glm/gtx/quaternion.hpp>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#define PI_2 1.570796325f

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))



namespace Framework
{
	ObjectPole::ObjectPole( const glm::vec3 &initialPos,
		const MousePole *pView, ActionButtons eButton)
		: m_pView(pView)
		, m_orientation()
		, m_objectPos(initialPos)
		, m_bIsDragging(false)
	{
		switch(eButton)
		{
		case AB_LEFT_MOUSE: m_glutActionButton = GLUT_LEFT_BUTTON; break;
		case AB_MIDDLE_MOUSE: m_glutActionButton = GLUT_MIDDLE_BUTTON; break;
		case AB_RIGHT_MOUSE: m_glutActionButton = GLUT_RIGHT_BUTTON; break;
		}
	}

	glm::mat4 ObjectPole::CalcMatrix() const
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(m_objectPos, 1.0f);

		return translateMat * glm::mat4_cast(m_orientation);
	}

	namespace
	{
		glm::vec3 g_axisVectors[ObjectPole::NUM_AXES] =
		{
			glm::vec3(1.0, 0.0, 0.0),
			glm::vec3(0.0, 1.0, 0.0),
			glm::vec3(0.0, 0.0, 1.0),
		};

		glm::fquat CalcRotationQuat(ObjectPole::Axis eAxis, float degAngle)
		{
			return glm::angleAxis(degAngle, g_axisVectors[eAxis]);
		}
	}

	void ObjectPole::RotateWorldDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		m_orientation = glm::normalize(rot * (bFromInitial ? m_initialOrient : m_orientation));
	}

	void ObjectPole::RotateLocalDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		m_orientation = glm::normalize((bFromInitial ? m_initialOrient : m_orientation) * rot);
	}

	void ObjectPole::RotateViewDegrees( const glm::fquat &rot, bool bFromInitial )
	{
		if(!m_bIsDragging)
			bFromInitial = false;

		if(m_pView)
		{
			glm::fquat viewQuat = glm::quat_cast(m_pView->CalcMatrix());
			glm::fquat invViewQuat = glm::conjugate(viewQuat);
			m_orientation = glm::normalize((invViewQuat * rot * viewQuat) *
				(bFromInitial ? m_initialOrient : m_orientation));
		}
		else
			RotateWorldDegrees(rot);
	}

#define SCALE_FACTOR 4

	const float X_CONVERSION_FACTOR = PI_2 / SCALE_FACTOR;
	const float Y_CONVERSION_FACTOR = PI_2 / SCALE_FACTOR;
	const float SPIN_CONV_FACTOR = PI_2 / SCALE_FACTOR;

	void ObjectPole::GLUTMouseMove( const glm::ivec2 &position )
	{
		if(m_bIsDragging)
		{
			glm::ivec2 iDiff = position - m_prevPos;

			switch(m_RotateMode)
			{
			case RM_DUAL_AXIS:
				{
					glm::fquat rot = CalcRotationQuat(AXIS_Y, iDiff.x * X_CONVERSION_FACTOR);
					rot = glm::normalize(
						CalcRotationQuat(AXIS_X, iDiff.y * Y_CONVERSION_FACTOR) * rot);
					RotateViewDegrees(rot);
				}
				break;
			case RM_BIAXIAL:
				{
					glm::ivec2 iInitDiff = position - m_initialPos;

					Axis eAxis;
					float degAngle;
					if(abs(iInitDiff.x) > abs(iInitDiff.y))
					{
						eAxis = AXIS_Y;
						degAngle = iInitDiff.x * X_CONVERSION_FACTOR;
					}
					else
					{
						eAxis = AXIS_X;
						degAngle = iInitDiff.y * Y_CONVERSION_FACTOR;
					}

					glm::fquat rot = CalcRotationQuat(eAxis, degAngle);
					RotateViewDegrees(rot, true);
				}
				break;
			case RM_SPIN:
				RotateViewDegrees(CalcRotationQuat(AXIS_Z, -iDiff.x * SPIN_CONV_FACTOR));
				break;
			}

			m_prevPos = position;
		}
	}

	void ObjectPole::GLUTMouseButton( int button, int btnState, const glm::ivec2 &position )
	{
		if(btnState == GLUT_DOWN)
		{
			//Ignore button presses when dragging.
			if(!m_bIsDragging)
			{
				if(button == m_glutActionButton)
				{
					if(glutGetModifiers() & GLUT_ACTIVE_ALT)
						m_RotateMode = RM_SPIN;
					else if(glutGetModifiers() & GLUT_ACTIVE_CTRL)
						m_RotateMode = RM_BIAXIAL;
					else
						m_RotateMode = RM_DUAL_AXIS;

					m_prevPos = position;
					m_initialPos = position;
					m_initialOrient = m_orientation;

					m_bIsDragging = true;
				}
			}
		}
		else
		{
			//Ignore up buttons if not dragging.
			if(m_bIsDragging)
			{
				if(button == m_glutActionButton)
				{
					GLUTMouseMove(position);

					m_bIsDragging = false;
				}
			}
		}
	}

	void ObjectPole::GLUTMouseWheel( int direction, const glm::ivec2 &position )
	{

	}
}
