//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include "glutil/MatrixStack.h"
#include <glm/gtc/matrix_transform.hpp>

namespace glutil
{
	void MatrixStack::Rotate( const glm::vec3 axis, float angDegCCW )
	{
		m_currMatrix = glm::rotate(m_currMatrix, angDegCCW, axis);
	}

	void MatrixStack::RotateRadians( const glm::vec3 axisOfRotation, float angRadCCW )
	{
		float fCos = cosf(angRadCCW);
		float fInvCos = 1.0f - fCos;
		float fSin = sinf(angRadCCW);
		//float fInvSin = 1.0f - fSin;

		glm::vec3 axis = glm::normalize(axisOfRotation);

		glm::mat4 theMat(1.0f);
		theMat[0].x = (axis.x * axis.x) + ((1 - axis.x * axis.x) * fCos);
		theMat[1].x = axis.x * axis.y * (fInvCos) - (axis.z * fSin);
		theMat[2].x = axis.x * axis.z * (fInvCos) + (axis.y * fSin);

		theMat[0].y = axis.x * axis.y * (fInvCos) + (axis.z * fSin);
		theMat[1].y = (axis.y * axis.y) + ((1 - axis.y * axis.y) * fCos);
		theMat[2].y = axis.y * axis.z * (fInvCos) - (axis.x * fSin);

		theMat[0].z = axis.x * axis.z * (fInvCos) - (axis.y * fSin);
		theMat[1].z = axis.y * axis.z * (fInvCos) + (axis.x * fSin);
		theMat[2].z = (axis.z * axis.z) + ((1 - axis.z * axis.z) * fCos);
		m_currMatrix *= theMat;
	}

	void MatrixStack::RotateX( float angDegCCW )
	{
		Rotate(glm::vec3(1.0f, 0.0f, 0.0f), angDegCCW);
	}

	void MatrixStack::RotateY( float angDegCCW )
	{
		Rotate(glm::vec3(0.0f, 1.0f, 0.0f), angDegCCW);
	}

	void MatrixStack::RotateZ( float angDegCCW )
	{
		Rotate(glm::vec3(0.0f, 0.0f, 1.0f), angDegCCW);
	}

	void MatrixStack::Scale( const glm::vec3 &scaleVec )
	{
		m_currMatrix = glm::scale(m_currMatrix, scaleVec);
	}

	void MatrixStack::Translate( const glm::vec3 &offsetVec )
	{
		m_currMatrix = glm::translate(m_currMatrix, offsetVec);
	}

	void MatrixStack::Perspective( float degFOV, float aspectRatio, float zNear, float zFar )
	{
		m_currMatrix *= glm::perspective(degFOV, aspectRatio, zNear, zFar);
	}

	void MatrixStack::Orthographic( float left, float right, float bottom, float top,
		float zNear, float zFar )
	{
		m_currMatrix *= glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	void MatrixStack::PixelPerfectOrtho( glm::ivec2 size, glm::vec2 depthRange, bool isTopLeft /*= true*/ )
	{
		if(isTopLeft)
		{
			Translate(-1.0f, 1.0f, (depthRange.x + depthRange.y) / 2.0f);
			Scale(2.0f / size.x, -2.0f / size.y, 1.0f);
		}
		else
		{
			Translate(-1.0f, -1.0f, (depthRange.x + depthRange.y) / 2.0f);
			Scale(2.0f / size.x, 2.0f / size.y, 2.0f / (depthRange.y - depthRange.x));
		}
	}

	void MatrixStack::LookAt( const glm::vec3 &cameraPos, const glm::vec3 &lookatPos, const glm::vec3 &upDir )
	{
		m_currMatrix *= glm::lookAt(cameraPos, lookatPos, upDir);
	}

	void MatrixStack::ApplyMatrix( const glm::mat4 &theMatrix )
	{
		m_currMatrix *= theMatrix;
	}

	void MatrixStack::SetMatrix( const glm::mat4 &theMatrix )
	{
		m_currMatrix = theMatrix;
	}

	void MatrixStack::SetIdentity()
	{
		m_currMatrix = glm::mat4(1.0f);
	}
}


