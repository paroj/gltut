#ifndef FRAMEWORK_MESH_H
#define FRAMEWORK_MESH_H


namespace Framework
{
	struct MeshData;

	class Mesh
	{
	public:
		Mesh(const std::string &strFilename);
		~Mesh();

		void Render();
		void Render(const std::string &strMeshName);
		void DeleteObjects();

	private:
		MeshData *m_pData;
	};
}


#endif //FRAMEWORK_MESH_H
