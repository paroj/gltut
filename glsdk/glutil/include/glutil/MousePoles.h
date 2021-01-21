/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef MOUSE_POLES_UTIL_H
#define MOUSE_POLES_UTIL_H

/**
\file
\brief Header for \ref module_glutil_poles "mouse poles".
**/

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace glutil
{
	///\addtogroup module_glutil_poles
	///@{

	///Abstract base class used by ViewPole to identify that it provides a viewing matrix.
	class ViewProvider
	{
	public:
		virtual ~ViewProvider() {}

		///Computes the camera matrix.
		virtual glm::mat4 CalcMatrix() const = 0;
	};

	///The possible buttons that Poles can use.
	enum MouseButtons
	{
		MB_LEFT_BTN = 1,	///<The left mouse button.
		MB_MIDDLE_BTN,		///<The middle mouse button.
		MB_RIGHT_BTN,		///<The right mouse button.
	};

	///Bitfield for modifiers that may be held down while mouse movements go on.
	enum MouseModifiers
	{
		MM_KEY_SHIFT =	0x01,	///<One of the shift keys.
		MM_KEY_CTRL =	0x02,	///<One of the control keys.
		MM_KEY_ALT =	0x04,	///<One of the alt keys.
	};

	///Utility object containing the ObjectPole's position and orientation information.
	struct ObjectData
	{
		glm::vec3 position;			///<The world-space position of the object.
		glm::fquat orientation;		///<The world-space orientation of the object.
	};

	/**
	\brief Mouse-based control over the orientation and position of an object.

	This Pole deals with three spaces: local, world, and view. Local refers to the coordinate system
	of vertices given to the matrix that this Pole generates. World represents the \em output coordinate
	system. So vertices enter in local and are transformed to world. Note that this does not have
	to actually be the real world-space. It could be the space of the parent node in some object
	hierarchy, though there is a caveat below.
	
	View represents the space that vertices are transformed into by the ViewProvider's matrix.
	The ViewProvider is given to this class's constructor. The assumption
	that this Pole makes when using the view space matrix is that the matrix the ObjectPole
	generates will be right-multiplied by the view matrix given by the ViewProvider. So it is assumed
	that there is no intermediate space between world and view.

	By defining these three spaces, it is possible to dictate orientation relative to these spaces.
	The ViewProvider exists to allow transformations relative to the current camera.

	This Pole is given an action button, which it will listen for click events from. When
	the action button is held down and the mouse moved, the object's orientation will change. The
	orientation will be relative to the view's orientation if a ViewProvider was provided. If not, it
	will be relative to the world.
	
	If no modifier keys (shift, ctrl, alt) were held when the click was given, then the object will be
	oriented in both the X and Y axes of the transformation space. If the CTRL key is held
	when the click was given, then the object will only rotate around either the X or Y axis.
	The selection is based on whether
	the X or the Y mouse coordinate is farthest from the initial position when dragging started.
	If the ALT key is held, then the object will rotate about the Z axis, and only the X position
	of the mouse affects the object.

	More information on [mouse poles is available](@ref module_glutil_poles).
	**/
	class ObjectPole
	{
	public:
		/**
		\brief Creates an object pole with a given initial position and orientation.
		
		\param initialData The starting position and orientation of the object in world space.
		\param rotateScale The number of degrees to rotate the object per window space pixel
		\param actionButton The mouse button to listen for. All other mouse buttons are ignored.
		\param pLookatProvider An object that will compute a view matrix. This defines the view space
		that orientations can be relative to. If it is NULL, then orientations will be relative to the world.
		**/
		ObjectPole(const ObjectData &initialData, float rotateScale,
			MouseButtons actionButton, const ViewProvider *pLookatProvider);

		///Generates the local-to-world matrix for this object.
		glm::mat4 CalcMatrix() const;

		/**
		\brief Sets the scaling factor for orientation changes.
		
		The scaling factor is the number of degrees to rotate the object per window space pixel.
		The scale is the same for all mouse movements.
		**/
		void SetRotationScale(float rotateScale);
		///Gets the current scaling factor for orientation changes.
		float GetRotationScale() const {return m_rotateScale;}

		///Retrieves the current position and orientation of the object.
		const ObjectData &GetPosOrient() const {return m_po;}

		///Resets the object to the initial position/orientation. Will fail if currently dragging.
		void Reset();

		/**
		\name Input Providers

		These functions provide input, since Poles cannot get input for themselves. See
		\ref module_glutil_poles "the Pole manual" for details.
		**/
		///@{

		/**
		\brief Notifies the pole of a mouse button being pressed or released.
		
		\param button The button being pressed or released.
		\param isPressed Set to true if \a button is being pressed.
		\param modifiers A bitfield of MouseModifiers that specifies the modifiers being held down currently.
		\param position The mouse position at the moment of the mouse click.
		**/
		void MouseClick(MouseButtons button, bool isPressed, int modifiers,
			const glm::ivec2 &position);

		///Notifies the pole that the mouse has moved to the given absolute position.
		void MouseMove(const glm::ivec2 &position);

		/**
		\brief Notifies the pole that the mouse wheel has been rolled up or down.
		
		\param direction A positive number if the mouse wheel has moved up, otherwise it should be negative.
		\param modifiers The modifiers currently being held down when the wheel was rolled.
		\param position The absolute mouse position at the moment the wheel was rolled.
		**/
		void MouseWheel(int direction, int modifiers, const glm::ivec2 &position);

		/**
		\brief Notifies the pole that a character has been entered.

		\param key ASCII keycode.
		**/
		void CharPress(char key);
		///@}

		///Returns true if the mouse is currently being dragged.
		bool IsDragging() const {return m_bIsDragging;}

	private:
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

		const ViewProvider *m_pView;
		ObjectData m_po;
		ObjectData m_initialPo;

		float m_rotateScale;
		MouseButtons m_actionButton;

		//Used when rotating.
		RotateMode m_RotateMode;
		bool m_bIsDragging;

		glm::ivec2 m_prevMousePos;
		glm::ivec2 m_startDragMousePos;
		glm::fquat m_startDragOrient;
	};

	///Utility object containing the ViewPole's view information.
	struct ViewData
	{
		glm::vec3 targetPos;	///<The starting target position position.
		glm::fquat orient;		///<The initial orientation aroudn the target position.
		float radius;			///<The initial radius of the camera from the target point.
		float degSpinRotation;	///<The initial spin rotation of the "up" axis, relative to \a orient
	};

	///Utility object describing the scale of the ViewPole.
	struct ViewScale
	{
		float minRadius;		///<The closest the radius to the target point can get.
		float maxRadius;		///<The farthest the radius to the target point can get.
		float largeRadiusDelta;	///<The radius change to use when the SHIFT key isn't held while mouse wheel scrolling.
		float smallRadiusDelta;	///<The radius change to use when the SHIFT key \em is held while mouse wheel scrolling.
		float largePosOffset;	///<The position offset to use when the SHIFT key isn't held while pressing a movement key.
		float smallPosOffset;	///<The position offset to use when the SHIFT key \em is held while pressing a movement key.
		float rotationScale;	///<The number of degrees to rotate the view per window space pixel the mouse moves when dragging.
	};

	/**
	\brief Mouse-based control over the orientation and position of the camera. 
	
	This view controller is based on a target point, which is centered in the camera, and an
	orientation around that target point that represents the camera. The Pole allows the user
	to rotate around this point, move closer to/farther from it, and to move the point itself.

	This Pole is given a ViewData object that contains the initial viewing orientation, as well
	as a ViewScale that represents how fast the various movements change the view, as well as its
	limitations.

	This Pole is given an action button, which it will listen for click events from. If the
	mouse button is clicked and no modifiers are pressed, the the view will rotate
	around the object in both the view-local X and Y axes. If the CTRL key is held, then it
	will rotate about the X or Y axes, based on how far the mouse is from the starting point in the
	X or Y directions. If the ALT key is held, then the camera will spin in the view-local Z direction.

	Scrolling the mouse wheel up or down moves the camera closer or farther from the object, respectively.
	The distance is taken from ViewScale::largeRadiusDelta. If the SHIFT key is held while scrolling, then the
	movement will be the ViewScale::smallRadiusDelta value instead.

	The target point can be moved, relative to the current view, with the WASD keys. W/S move forward and
	backwards, while A/D move left and right, respectively. Q and E move down and up, respectively. If
	the \a bRightKeyboardCtrls parameter of the constructor is set, then it uses the IJKLUO keys instead
	of WASDQE. The offset applied to the position is ViewScale::largePosOffset; if SHIFT is held,
	then ViewScale::smallPosOffset is used instead.
	**/
	class ViewPole : public ViewProvider
	{
	public:
		/**
		\brief Creates a view pole with the given initial target position, view definition, and action button.
		
		\param initialView The starting state of the view.
		\param viewScale The viewport definition to use.
		\param actionButton The mouse button to listen for. All other mouse buttons are ignored.
		\param bRightKeyboardCtrls If true, then it uses IJKLUO instead of WASDQE keys.
		**/
		ViewPole(const ViewData &initialView, const ViewScale &viewScale,
			MouseButtons actionButton = MB_LEFT_BTN, bool bRightKeyboardCtrls = false);
		virtual ~ViewPole() {}

		///Generates the world-to-camera matrix for the view.
		glm::mat4 CalcMatrix() const;

		/**
		\brief Sets the scaling factor for orientation changes.
		
		The scaling factor is the number of degrees to rotate the view per window space pixel.
		The scale is the same for all mouse movements.
		**/
		void SetRotationScale(float rotateScale);

		///Gets the current scaling factor for orientation changes.
		float GetRotationScale() const {return m_viewScale.rotationScale;}

		///Retrieves the current viewing information.
		const ViewData &GetView() const {return m_currView;}

		///Resets the view to the initial view. Will fail if currently dragging.
		void Reset();

		/**
		\name Input Providers

		These functions provide input, since Poles cannot get input for themselves. See
		\ref module_glutil_poles "the Pole manual" for details.
		**/
		///@{
		void MouseClick(MouseButtons button, bool isPressed, int modifiers, const glm::ivec2 &position);
		void MouseMove(const glm::ivec2 &position);
		void MouseWheel(int direction, int modifiers, const glm::ivec2 &position);
		void CharPress(char key);
		///@}

		///Returns true if the mouse is being dragged.
		bool IsDragging() const {return m_bIsDragging;}

	private:
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

		enum RotateMode
		{
			RM_DUAL_AXIS_ROTATE,
			RM_BIAXIAL_ROTATE,
			RM_XZ_AXIS_ROTATE,
			RM_Y_AXIS_ROTATE,
			RM_SPIN_VIEW_AXIS,
		};

		ViewData m_currView;
		ViewScale m_viewScale;

		ViewData m_initialView;
		MouseButtons m_actionButton;
		bool m_bRightKeyboardCtrls;

		//Used when rotating.
		bool m_bIsDragging;
		RotateMode m_RotateMode;

		float m_degStarDragSpin;
		glm::ivec2 m_startDragMouseLoc;
		glm::fquat m_startDragOrient;

		void ProcessXChange(int iXDiff, bool bClearY = false);
		void ProcessYChange(int iYDiff, bool bClearXZ = false);
		void ProcessXYChange(int iXDiff, int iYDiff);
		void ProcessSpinAxis(int iXDiff, int iYDiff);

		void BeginDragRotate(const glm::ivec2 &ptStart, RotateMode rotMode = RM_DUAL_AXIS_ROTATE);
		void OnDragRotate(const glm::ivec2 &ptCurr);
		void EndDragRotate(const glm::ivec2 &ptEnd, bool bKeepResults = true);

		void MoveCloser(bool bLargeStep = true);
		void MoveAway(bool bLargeStep = true);
	};
	///@}
}



#endif //MOUSE_POLES_UTIL_H
