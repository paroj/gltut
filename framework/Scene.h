
#ifndef FRAMEWORK_SCENE_H
#define FRAMEWORK_SCENE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glutil/MousePoles.h>

namespace Framework
{
	class SceneImpl;
	class SceneNode;

	class Mesh;

	class StateBinder;
	class UniformBinderBase;

	class NodeRef
	{
	public:
		NodeRef();

		void NodeSetScale(const glm::vec3 &scale);
		void NodeSetScale(float scale);

		//Right-multiplies the given orientation to the current one.
		void NodeRotate(const glm::fquat &orient);
		//Sets the current orientation to the given one.
		void NodeSetOrient(const glm::fquat &orient);

		glm::fquat NodeGetOrient() const;

		//Adds the offset to the current translation.
		void NodeOffset(const glm::vec3 &offset);
		//Sets the current translation to the given one.
		void NodeSetTrans(const glm::vec3 &offset);

		//Sets the pre-transform matrix.
		void SetNodePreTransform(const glm::mat4 &preTransform);
		//Sets the post-transform matrix.
		void SetNodePostTransform(const glm::mat4 &postTransform);

		//This object does *NOT* claim ownership of the pointer.
		//You must ensure that it stays around so long as this Scene exists.
		void SetStateBinder(StateBinder *pBinder);

		GLuint GetProgram() const;
		GLuint GetProgram(const std::string &variation) const;

		void AssociateWithBinder(UniformBinderBase &binder, const std::string &unifName) const;

	private:
		explicit NodeRef(SceneNode *pNode) : m_pNode(pNode) {}
		SceneNode *m_pNode;

		friend class SceneImpl;
	};

	class Scene
	{
	public:
		Scene(const std::string &filename);
		~Scene();

		void Render(const glm::mat4 &cameraMatrix) const;
		void Render(const std::string &variation, const glm::mat4 &cameraMatrix) const;

		NodeRef FindNode(const std::string &nodeName);

		std::vector<NodeRef> GetAllNodes();

		GLuint FindProgram(const std::string &progName);

		Mesh *FindMesh(const std::string &meshName);

		//Returns the old texture name, or 0 if not found.
		GLuint ReplaceTexture(const std::string &textureName, GLuint newTexObj, GLenum newTexType);

		//Constructs a camera. Note that this is *constructs*, not retrieves a stored one.
		//Every call creates a new, *independent* camera.
		glutil::ViewPole *CreateCamera(const std::string &cameraName,
			glutil::MouseButtons actionButton = glutil::MB_LEFT_BTN, bool bRightKeyboardCtrls = false) const;

	private:
		SceneImpl *m_pImpl;
	};
}

#endif //FRAMEWORK_SCENE_H
