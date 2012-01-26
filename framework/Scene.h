
#ifndef FRAMEWORK_SCENE_H
#define FRAMEWORK_SCENE_H

#include <string>

namespace Framework
{
	class SceneImpl;

	class Scene
	{
	public:
		Scene(const std::string &filename);
		~Scene();

		void Render() const;

	private:
		SceneImpl *m_pImpl;
	};
}

#endif //FRAMEWORK_SCENE_H
