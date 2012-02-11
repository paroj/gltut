
#ifndef FRAMEWORK_SCENE_H
#define FRAMEWORK_SCENE_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Framework
{
	class SceneImpl;
	class SceneNode;

	class Mesh;

	class StateBinder;

	class NodeRef
	{
	public:
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

		//This object does *NOT* claim ownership of the pointer.
		//You must ensure that it stays around so long as this Scene exists.
		void SetStateBinder(StateBinder *pBinder);

		GLuint GetProgram() const;

	private:
		NodeRef();	//No default-construction.
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

		NodeRef FindNode(const std::string &nodeName);

		GLuint FindProgram(const std::string &progName);

		Mesh *FindMesh(const std::string &meshName);

	private:
		SceneImpl *m_pImpl;
	};
}

#endif //FRAMEWORK_SCENE_H
