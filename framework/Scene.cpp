#include <string>
#include <vector>
#include <exception>
#include <memory>

#include <istream>
#include <fstream>
#include <iostream>

#include <glload/gl_all.h>
#include "framework.h"
#include "Scene.h"
#include "Mesh.h"



namespace Framework
{
	class SceneImpl
	{
	public:
		SceneImpl(const std::string &filename)
		{
			std::string pathname = FindFileOrThrow(filename);

			std::ifstream fileStream(pathname.c_str());
			if(!fileStream.is_open())
				throw std::runtime_error("Could not open the scene file.");

			while(!fileStream.fail() && !fileStream.eof())
				LoadElement(fileStream);

			std::cout << "EOF" << std::endl;
		}

	private:
		void LoadElement(std::istream &fileStream)
		{
		}

		void ReadProgram(std::istream &fileStream)
		{
		}

		void ReadMesh(std::istream &fileStream)
		{
		}

		std::string ReadFilename(std::istream &fileStream)
		{
		}
	};

	Scene::Scene( const std::string &filename )
		: m_pImpl(new SceneImpl(filename))
	{}

	Scene::~Scene()
	{
		delete m_pImpl;
	}

	void Scene::Render() const
	{

	}
}
