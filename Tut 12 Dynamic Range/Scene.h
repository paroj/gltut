#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"

struct ProgramData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
	GLuint normalModelToCameraMatrixUnif;
};

struct MaterialBlock
{
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float specularShininess;
	float padding[3];
};

class Scene
{
public:
	Scene();

	void Draw(glutil::MatrixStack &modelMatrix, int materialBlockIndex, float alphaTetra);

	Framework::Mesh *GetCubeMesh() {return m_pCubeMesh.get();}
	Framework::Mesh *GetSphereMesh() {return m_pSphereMesh.get();}

private:
	std::auto_ptr<Framework::Mesh> m_pTerrainMesh;
	std::auto_ptr<Framework::Mesh> m_pCubeMesh;
	std::auto_ptr<Framework::Mesh> m_pTetraMesh;
	std::auto_ptr<Framework::Mesh> m_pCylMesh;
	std::auto_ptr<Framework::Mesh> m_pSphereMesh;

	int m_sizeMaterialBlock;
	GLuint m_materialUniformBuffer;

	void DrawObject( const Framework::Mesh *pMesh, const ProgramData &prog,
		int materialBlockIndex, int mtlIx, const glutil::MatrixStack &modelMatrix );
	void DrawObject(const Framework::Mesh *pMesh, const std::string &meshName, 
		const ProgramData &prog, int materialBlockIndex, int mtlIx,
		const glutil::MatrixStack &modelMatrix);
};

#include "../framework/framework.h"
#include "../framework/Mesh.h"


enum LightingProgramTypes
{
	LP_VERT_COLOR_DIFFUSE_SPECULAR = 0,
	LP_VERT_COLOR_DIFFUSE,

	LP_MTL_COLOR_DIFFUSE_SPECULAR,
	LP_MTL_COLOR_DIFFUSE,

	LP_MAX_LIGHTING_PROGRAM_TYPES,
};

//Defined by the user of the Scene.
const ProgramData &GetProgram(LightingProgramTypes eType);

#endif //SCENE_H