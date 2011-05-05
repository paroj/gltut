
#include <glloader/gl_3_2_comp.h>
#include "framework.h"
#include "MatrixStack.h"
#include <glm/gtc/matrix_projection.hpp>

namespace Framework
{
	void MatrixStack::Rotate( const glm::vec3 &axisOfRotation, float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);

		RotateRadians(axisOfRotation, fAngRad);
	}

	void MatrixStack::RotateRadians( const glm::vec3 &axisOfRotation, float fAngRad )
	{
		float fCos = cosf(fAngRad);
		float fInvCos = 1.0f - fCos;
		float fSin = sinf(fAngRad);
		float fInvSin = 1.0f - fSin;

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
		m_currMat *= theMat;
	}

	void MatrixStack::RotateX( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[1].y = fCos; theMat[2].y = -fSin;
		theMat[1].z = fSin; theMat[2].z = fCos;

		m_currMat *= theMat;
	}

	void MatrixStack::RotateY( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[2].x = fSin;
		theMat[0].z = -fSin; theMat[2].z = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::RotateZ( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[1].x = -fSin;
		theMat[0].y = fSin; theMat[1].y = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::Scale( const glm::vec3 &scaleVec )
	{
		glm::mat4 scaleMat(1.0f);
		scaleMat[0].x = scaleVec.x;
		scaleMat[1].y = scaleVec.y;
		scaleMat[2].z = scaleVec.z;

		m_currMat *= scaleMat;
	}

	void MatrixStack::Translate( const glm::vec3 &offsetVec )
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(offsetVec, 1.0f);

		m_currMat *= translateMat;
	}

	void MatrixStack::ApplyMatrix( const glm::mat4 &theMatrix )
	{
		m_currMat *= theMatrix;
	}

	void MatrixStack::SetIdentity()
	{
		m_currMat = glm::mat4(1.0f);
	}

	void MatrixStack::Perspective( float fDegFOV, float fAspectRatio, float fZNear, float fZFar )
	{
		m_currMat *= glm::perspective(fDegFOV, 1.0f / fAspectRatio, fZNear, fZFar);
	}

	void MatrixStack::SetMatrix( const glm::mat4 &theMatrix )
	{
		m_currMat = theMatrix;
	}
}
