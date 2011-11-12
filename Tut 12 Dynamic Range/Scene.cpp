
#include "Scene.h"
#include <string.h>
#include <glm/gtc/type_ptr.hpp>

//One for the ground, and one for each of the 5 objects.
const int MATERIAL_COUNT = 6;

static void GetMaterials( std::vector<MaterialBlock> &materials )
{
	materials.resize(MATERIAL_COUNT);

	//Ground
	materials[0].diffuseColor = glm::vec4(1.0f);
	materials[0].specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	materials[0].specularShininess = 0.6f;

	//Tetrahedron
	materials[1].diffuseColor = glm::vec4(0.5f);
	materials[1].specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	materials[1].specularShininess = 0.05f;

	//Monolith
	materials[2].diffuseColor = glm::vec4(0.05f);
	materials[2].specularColor = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
	materials[2].specularShininess = 0.4f;

	//Cube
	materials[3].diffuseColor = glm::vec4(0.5f);
	materials[3].specularColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	materials[3].specularShininess = 0.1f;

	//Cylinder
	materials[4].diffuseColor = glm::vec4(0.5f);
	materials[4].specularColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	materials[4].specularShininess = 0.6f;

	//Sphere
	materials[5].diffuseColor = glm::vec4(0.63f, 0.60f, 0.02f, 1.0f);
	materials[5].specularColor = glm::vec4(0.22f, 0.20f, 0.0f, 1.0f);
	materials[5].specularShininess = 0.3f;
}

Scene::Scene()
	: m_pTerrainMesh(new Framework::Mesh("Ground.xml"))
	, m_pCubeMesh(new Framework::Mesh("UnitCube.xml"))
	, m_pTetraMesh(new Framework::Mesh("UnitTetrahedron.xml"))
	, m_pCylMesh(new Framework::Mesh("UnitCylinder.xml"))
	, m_pSphereMesh(new Framework::Mesh("UnitSphere.xml"))
{
	//Align the size of each MaterialBlock to the uniform buffer alignment.
	int uniformBufferAlignSize = 0;
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniformBufferAlignSize);

	m_sizeMaterialBlock = sizeof(MaterialBlock);
	m_sizeMaterialBlock += uniformBufferAlignSize -
		(m_sizeMaterialBlock % uniformBufferAlignSize);

	int sizeMaterialUniformBuffer = m_sizeMaterialBlock * MATERIAL_COUNT;

	std::vector<MaterialBlock> materials;
	GetMaterials(materials);
	assert(materials.size() == MATERIAL_COUNT);

	std::vector<GLubyte> mtlBuffer;
	mtlBuffer.resize(sizeMaterialUniformBuffer, 0);

	GLubyte *bufferPtr = &mtlBuffer[0];

	for(size_t mtl = 0; mtl < materials.size(); ++mtl)
		memcpy(bufferPtr + (mtl * m_sizeMaterialBlock), &materials[mtl], sizeof(MaterialBlock));

	glGenBuffers(1, &m_materialUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_materialUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeMaterialUniformBuffer, bufferPtr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Scene::Draw( glutil::MatrixStack &modelMatrix, int materialBlockIndex, float alphaTetra )
{
	//Render the ground plane.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.RotateX(-90);

		DrawObject(m_pTerrainMesh.get(), GetProgram(LP_VERT_COLOR_DIFFUSE), materialBlockIndex, 0,
			modelMatrix);
	}

	//Render the tetrahedron object.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(75.0f, 5.0f, 75.0f);
		modelMatrix.RotateY(360.0f * alphaTetra);
		modelMatrix.Scale(10.0f, 10.0f, 10.0f);
		modelMatrix.Translate(0.0f, sqrtf(2.0f), 0.0f);
		modelMatrix.Rotate(glm::vec3(-0.707f, 0.0f, -0.707f), 54.735f);

		DrawObject(m_pTetraMesh.get(), "lit-color", GetProgram(LP_VERT_COLOR_DIFFUSE_SPECULAR),
			materialBlockIndex, 1, modelMatrix);
	}

	//Render the monolith object.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(88.0f, 5.0f, -80.0f);
		modelMatrix.Scale(4.0f, 4.0f, 4.0f);
		modelMatrix.Scale(4.0f, 9.0f, 1.0f);
		modelMatrix.Translate(0.0f, 0.5f, 0.0f);

		DrawObject(m_pCubeMesh.get(), "lit", GetProgram(LP_MTL_COLOR_DIFFUSE_SPECULAR),
			materialBlockIndex, 2, modelMatrix);
	}

	//Render the cube object.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(-52.5f, 14.0f, 65.0f);
		modelMatrix.RotateZ(50.0f);
		modelMatrix.RotateY(-10.0f);
		modelMatrix.Scale(20.0f, 20.0f, 20.0f);

		DrawObject(m_pCubeMesh.get(), "lit-color", GetProgram(LP_VERT_COLOR_DIFFUSE_SPECULAR),
			materialBlockIndex, 3, modelMatrix);
	}

	//Render the cylinder.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(-7.0f, 30.0f, -14.0f);
		modelMatrix.Scale(15.0f, 55.0f, 15.0f);
		modelMatrix.Translate(0.0f, 0.5f, 0.0f);

		DrawObject(m_pCylMesh.get(), "lit-color", GetProgram(LP_VERT_COLOR_DIFFUSE_SPECULAR),
			materialBlockIndex, 4, modelMatrix);
	}

	//Render the sphere.
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(-83.0f, 14.0f, -77.0f);
		modelMatrix.Scale(20.0f, 20.0f, 20.0f);

		DrawObject(m_pSphereMesh.get(), "lit", GetProgram(LP_MTL_COLOR_DIFFUSE_SPECULAR),
			materialBlockIndex, 5, modelMatrix);
	}
}

void Scene::DrawObject( const Framework::Mesh *pMesh, const ProgramData &prog,
					   int materialBlockIndex, int mtlIx,
					   const glutil::MatrixStack &modelMatrix )
{
	glBindBufferRange(GL_UNIFORM_BUFFER, materialBlockIndex, m_materialUniformBuffer,
		mtlIx * m_sizeMaterialBlock, sizeof(MaterialBlock));

	glm::mat3 normMatrix(modelMatrix.Top());
	normMatrix = glm::transpose(glm::inverse(normMatrix));

	glUseProgram(prog.theProgram);
	glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(modelMatrix.Top()));

	glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(normMatrix));
	pMesh->Render();
	glUseProgram(0);

	glBindBufferBase(GL_UNIFORM_BUFFER, materialBlockIndex, 0);
}

void Scene::DrawObject(const Framework::Mesh *pMesh, const std::string &meshName, 
					   const ProgramData &prog, int materialBlockIndex, int mtlIx,
					   const glutil::MatrixStack &modelMatrix)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, materialBlockIndex, m_materialUniformBuffer,
		mtlIx * m_sizeMaterialBlock, sizeof(MaterialBlock));

	glm::mat3 normMatrix(modelMatrix.Top());
	normMatrix = glm::transpose(glm::inverse(normMatrix));

	glUseProgram(prog.theProgram);
	glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(modelMatrix.Top()));

	glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(normMatrix));
	pMesh->Render(meshName);
	glUseProgram(0);

	glBindBufferBase(GL_UNIFORM_BUFFER, materialBlockIndex, 0);
}




