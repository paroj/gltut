#ifndef FRAMEWORK_OBJECT_POLE_H
#define FRAMEWORK_OBJECT_POLE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace Framework
{
	class MousePole;

	class ObjectPole
	{
	public:
		enum ActionButtons
		{
			AB_LEFT_MOUSE,
			AB_MIDDLE_MOUSE,
			AB_RIGHT_MOUSE,
		};

		ObjectPole(const glm::vec3 &initialPos,
			const MousePole *pView = NULL, ActionButtons eButton = AB_RIGHT_MOUSE);

		glm::mat4 CalcMatrix() const;

		enum Axis
		{
			AXIS_X,
			AXIS_Y,
			AXIS_Z,

			NUM_AXES,
		};

		enum RotateMode
		{
			RM_DUAL_AXIS,
			RM_BIAXIAL,
			RM_SPIN,
		};

		void RotateWorldDegrees(const glm::fquat &rot, bool bFromInitial = false);
		void RotateLocalDegrees(const glm::fquat &rot, bool bFromInitial = false);
		void RotateViewDegrees(const glm::fquat &rot, bool bFromInitial = false);

		void GLUTMouseMove(const glm::ivec2 &position);
		void GLUTMouseButton(int button, int btnState, const glm::ivec2 &position);
		void GLUTMouseWheel(int direction, const glm::ivec2 &position);

		bool IsDragging() const {return m_bIsDragging;}

	private:
		const MousePole *m_pView;
		glm::fquat m_orientation;
		glm::vec3 m_objectPos;

		int m_glutActionButton;

		RotateMode m_RotateMode;
		bool m_bIsDragging;

		glm::ivec2 m_prevPos;
		glm::ivec2 m_initialPos;
		glm::fquat m_initialOrient;
	};
}


#endif //FRAMEWORK_OBJECT_POLE_H
