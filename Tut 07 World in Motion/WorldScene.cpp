#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;
	GLuint modelToWorldMatrixUnif;
	GLuint worldToCameraMatrixUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint baseColorUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData UniformColor;
ProgramData ObjectColor;
ProgramData UniformColorTint;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToWorldMatrixUnif = glGetUniformLocation(data.theProgram, "modelToWorldMatrix");
	data.worldToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "worldToCameraMatrix");
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");
	data.baseColorUnif = glGetUniformLocation(data.theProgram, "baseColor");

	return data;
}

void InitializeProgram()
{
	UniformColor = LoadProgram("PosOnlyWorldTransform.vert", "ColorUniform.frag");
	ObjectColor = LoadProgram("PosColorWorldTransform.vert", "ColorPassthrough.frag");
	UniformColorTint = LoadProgram("PosColorWorldTransform.vert", "ColorMultUniform.frag");
}

glm::mat4 CalcLookAtMatrix(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt)
{
	glm::vec3 lookDir = glm::normalize(lookPt - cameraPt);
	glm::vec3 upDir = glm::normalize(upPt);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	rotMat = glm::transpose(rotMat);

	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-cameraPt, 1.0f);

	return rotMat * transMat;
}

Framework::Mesh *g_pConeMesh = NULL;
Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pCubeTintMesh = NULL;
Framework::Mesh *g_pCubeColorMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();

	try
	{
		g_pConeMesh = new Framework::Mesh("UnitConeTint.xml");
		g_pCylinderMesh = new Framework::Mesh("UnitCylinderTint.xml");
		g_pCubeTintMesh = new Framework::Mesh("UnitCubeTint.xml");
		g_pCubeColorMesh = new Framework::Mesh("UnitCubeColor.xml");
		g_pPlaneMesh = new Framework::Mesh("UnitPlane.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_CLAMP);
}

static float g_fYAngle = 0.0f;
static float g_fXAngle = 0.0f;

//Trees are 3x3 in X/Z, and fTrunkHeight+fConeHeight in the Y.
void DrawTree(glutil::MatrixStack &modelMatrix, float fTrunkHeight = 2.0f, float fConeHeight = 3.0f)
{
	//Draw trunk.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, fTrunkHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.694f, 0.4f, 0.106f, 1.0f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}

	//Draw the treetop
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fTrunkHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(3.0f, fConeHeight, 3.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.0f, 1.0f, 0.0f, 1.0f);
		g_pConeMesh->Render();
		glUseProgram(0);
	}
}

const float g_fColumnBaseHeight = 0.25f;

//Columns are 1x1 in the X/Z, and fHieght units in the Y.
void DrawColumn(glutil::MatrixStack &modelMatrix, float fHeight = 5.0f)
{
	//Draw the bottom of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the top of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fHeight - g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the main column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(0.8f, fHeight - (g_fColumnBaseHeight * 2.0f), 0.8f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}
}

const float g_fParthenonWidth = 14.0f;
const float g_fParthenonLength = 20.0f;
const float g_fParthenonColumnHeight = 5.0f;
const float g_fParthenonBaseHeight = 1.0f;
const float g_fParthenonTopHeight = 2.0f;

void DrawParthenon(glutil::MatrixStack &modelMatrix)
{
	//Draw base.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonBaseHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw top.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fParthenonColumnHeight + g_fParthenonBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonTopHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(UniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw columns.
	const float fFrontZVal = (g_fParthenonLength / 2.0f) - 1.0f;
	const float fRightXVal = (g_fParthenonWidth / 2.0f) - 1.0f;

	for(int iColumnNum = 0; iColumnNum < int(g_fParthenonWidth / 2.0f); iColumnNum++)
	{
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3((2.0f * iColumnNum) - (g_fParthenonWidth / 2.0f) + 1.0f,
				g_fParthenonBaseHeight, fFrontZVal));

			DrawColumn(modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3((2.0f * iColumnNum) - (g_fParthenonWidth / 2.0f) + 1.0f,
				g_fParthenonBaseHeight, -fFrontZVal));

			DrawColumn(modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Don't draw the first or last columns, since they've been drawn already.
	for(int iColumnNum = 1; iColumnNum < int((g_fParthenonLength - 2.0f) / 2.0f); iColumnNum++)
	{
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(-fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Draw interior.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth - 6.0f, g_fParthenonColumnHeight,
			g_fParthenonLength - 6.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(ObjectColor.theProgram);
		glUniformMatrix4fv(ObjectColor.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		g_pCubeColorMesh->Render();
		glUseProgram(0);
	}

	//Draw headpiece.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(
			0.0f,
			g_fParthenonColumnHeight + g_fParthenonBaseHeight + (g_fParthenonTopHeight / 2.0f),
			g_fParthenonLength / 2.0f));
		modelMatrix.RotateX(-135.0f);
		modelMatrix.RotateY(45.0f);

		glUseProgram(ObjectColor.theProgram);
		glUniformMatrix4fv(ObjectColor.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		g_pCubeColorMesh->Render();
		glUseProgram(0);
	}
}

struct TreeData
{
	float fXPos;
	float fZPos;
	float fTrunkHeight;
	float fConeHeight;
};

static const TreeData g_forest[] =
{
	{-45.0f, -40.0f, 2.0f, 3.0f},
	{-42.0f, -35.0f, 2.0f, 3.0f},
	{-39.0f, -29.0f, 2.0f, 4.0f},
	{-44.0f, -26.0f, 3.0f, 3.0f},
	{-40.0f, -22.0f, 2.0f, 4.0f},
	{-36.0f, -15.0f, 3.0f, 3.0f},
	{-41.0f, -11.0f, 2.0f, 3.0f},
	{-37.0f, -6.0f, 3.0f, 3.0f},
	{-45.0f, 0.0f, 2.0f, 3.0f},
	{-39.0f, 4.0f, 3.0f, 4.0f},
	{-36.0f, 8.0f, 2.0f, 3.0f},
	{-44.0f, 13.0f, 3.0f, 3.0f},
	{-42.0f, 17.0f, 2.0f, 3.0f},
	{-38.0f, 23.0f, 3.0f, 4.0f},
	{-41.0f, 27.0f, 2.0f, 3.0f},
	{-39.0f, 32.0f, 3.0f, 3.0f},
	{-44.0f, 37.0f, 3.0f, 4.0f},
	{-36.0f, 42.0f, 2.0f, 3.0f},

	{-32.0f, -45.0f, 2.0f, 3.0f},
	{-30.0f, -42.0f, 2.0f, 4.0f},
	{-34.0f, -38.0f, 3.0f, 5.0f},
	{-33.0f, -35.0f, 3.0f, 4.0f},
	{-29.0f, -28.0f, 2.0f, 3.0f},
	{-26.0f, -25.0f, 3.0f, 5.0f},
	{-35.0f, -21.0f, 3.0f, 4.0f},
	{-31.0f, -17.0f, 3.0f, 3.0f},
	{-28.0f, -12.0f, 2.0f, 4.0f},
	{-29.0f, -7.0f, 3.0f, 3.0f},
	{-26.0f, -1.0f, 2.0f, 4.0f},
	{-32.0f, 6.0f, 2.0f, 3.0f},
	{-30.0f, 10.0f, 3.0f, 5.0f},
	{-33.0f, 14.0f, 2.0f, 4.0f},
	{-35.0f, 19.0f, 3.0f, 4.0f},
	{-28.0f, 22.0f, 2.0f, 3.0f},
	{-33.0f, 26.0f, 3.0f, 3.0f},
	{-29.0f, 31.0f, 3.0f, 4.0f},
	{-32.0f, 38.0f, 2.0f, 3.0f},
	{-27.0f, 41.0f, 3.0f, 4.0f},
	{-31.0f, 45.0f, 2.0f, 4.0f},
	{-28.0f, 48.0f, 3.0f, 5.0f},

	{-25.0f, -48.0f, 2.0f, 3.0f},
	{-20.0f, -42.0f, 3.0f, 4.0f},
	{-22.0f, -39.0f, 2.0f, 3.0f},
	{-19.0f, -34.0f, 2.0f, 3.0f},
	{-23.0f, -30.0f, 3.0f, 4.0f},
	{-24.0f, -24.0f, 2.0f, 3.0f},
	{-16.0f, -21.0f, 2.0f, 3.0f},
	{-17.0f, -17.0f, 3.0f, 3.0f},
	{-25.0f, -13.0f, 2.0f, 4.0f},
	{-23.0f, -8.0f, 2.0f, 3.0f},
	{-17.0f, -2.0f, 3.0f, 3.0f},
	{-16.0f, 1.0f, 2.0f, 3.0f},
	{-19.0f, 4.0f, 3.0f, 3.0f},
	{-22.0f, 8.0f, 2.0f, 4.0f},
	{-21.0f, 14.0f, 2.0f, 3.0f},
	{-16.0f, 19.0f, 2.0f, 3.0f},
	{-23.0f, 24.0f, 3.0f, 3.0f},
	{-18.0f, 28.0f, 2.0f, 4.0f},
	{-24.0f, 31.0f, 2.0f, 3.0f},
	{-20.0f, 36.0f, 2.0f, 3.0f},
	{-22.0f, 41.0f, 3.0f, 3.0f},
	{-21.0f, 45.0f, 2.0f, 3.0f},

	{-12.0f, -40.0f, 2.0f, 4.0f},
	{-11.0f, -35.0f, 3.0f, 3.0f},
	{-10.0f, -29.0f, 1.0f, 3.0f},
	{-9.0f, -26.0f, 2.0f, 2.0f},
	{-6.0f, -22.0f, 2.0f, 3.0f},
	{-15.0f, -15.0f, 1.0f, 3.0f},
	{-8.0f, -11.0f, 2.0f, 3.0f},
	{-14.0f, -6.0f, 2.0f, 4.0f},
	{-12.0f, 0.0f, 2.0f, 3.0f},
	{-7.0f, 4.0f, 2.0f, 2.0f},
	{-13.0f, 8.0f, 2.0f, 2.0f},
	{-9.0f, 13.0f, 1.0f, 3.0f},
	{-13.0f, 17.0f, 3.0f, 4.0f},
	{-6.0f, 23.0f, 2.0f, 3.0f},
	{-12.0f, 27.0f, 1.0f, 2.0f},
	{-8.0f, 32.0f, 2.0f, 3.0f},
	{-10.0f, 37.0f, 3.0f, 3.0f},
	{-11.0f, 42.0f, 2.0f, 2.0f},


	{15.0f, 5.0f, 2.0f, 3.0f},
	{15.0f, 10.0f, 2.0f, 3.0f},
	{15.0f, 15.0f, 2.0f, 3.0f},
	{15.0f, 20.0f, 2.0f, 3.0f},
	{15.0f, 25.0f, 2.0f, 3.0f},
	{15.0f, 30.0f, 2.0f, 3.0f},
	{15.0f, 35.0f, 2.0f, 3.0f},
	{15.0f, 40.0f, 2.0f, 3.0f},
	{15.0f, 45.0f, 2.0f, 3.0f},

	{25.0f, 5.0f, 2.0f, 3.0f},
	{25.0f, 10.0f, 2.0f, 3.0f},
	{25.0f, 15.0f, 2.0f, 3.0f},
	{25.0f, 20.0f, 2.0f, 3.0f},
	{25.0f, 25.0f, 2.0f, 3.0f},
	{25.0f, 30.0f, 2.0f, 3.0f},
	{25.0f, 35.0f, 2.0f, 3.0f},
	{25.0f, 40.0f, 2.0f, 3.0f},
	{25.0f, 45.0f, 2.0f, 3.0f},
};

void DrawForest(glutil::MatrixStack &modelMatrix)
{
	for(int iTree = 0; iTree < ARRAY_COUNT(g_forest); iTree++)
	{
		const TreeData &currTree = g_forest[iTree];

		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(glm::vec3(currTree.fXPos, 0.0f, currTree.fZPos));
		DrawTree(modelMatrix, currTree.fTrunkHeight, currTree.fConeHeight);
	}
}

static bool g_bDrawLookatPoint = false;
static glm::vec3 g_camTarget(0.0f, 0.4f, 0.0f);

//In spherical coordinates.
static glm::vec3 g_sphereCamRelPos(67.5f, -46.0f, 150.0f);

glm::vec3 ResolveCamPosition()
{
	glutil::MatrixStack tempMat;

	float phi = Framework::DegToRad(g_sphereCamRelPos.x);
	float theta = Framework::DegToRad(g_sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	return (dirToCamera * g_sphereCamRelPos.z) + g_camTarget;
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pConeMesh && g_pCylinderMesh && g_pCubeTintMesh && g_pCubeColorMesh && g_pPlaneMesh)
	{
		const glm::vec3 &camPos = ResolveCamPosition();

		glutil::MatrixStack camMatrix;
		camMatrix.SetMatrix(CalcLookAtMatrix(camPos, g_camTarget, glm::vec3(0.0f, 1.0f, 0.0f)));

		glUseProgram(UniformColor.theProgram);
		glUniformMatrix4fv(UniformColor.worldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(camMatrix.Top()));
		glUseProgram(ObjectColor.theProgram);
		glUniformMatrix4fv(ObjectColor.worldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(camMatrix.Top()));
		glUseProgram(UniformColorTint.theProgram);
		glUniformMatrix4fv(UniformColorTint.worldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(camMatrix.Top()));
		glUseProgram(0);

		glutil::MatrixStack modelMatrix;

		//Render the ground plane.
		{
			glutil::PushStack push(modelMatrix);

			modelMatrix.Scale(glm::vec3(100.0f, 1.0f, 100.0f));

			glUseProgram(UniformColor.theProgram);
			glUniformMatrix4fv(UniformColor.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
			glUniform4f(UniformColor.baseColorUnif, 0.302f, 0.416f, 0.0589f, 1.0f);
			g_pPlaneMesh->Render();
			glUseProgram(0);
		}

		//Draw the trees
		DrawForest(modelMatrix);

		//Draw the building.
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(20.0f, 0.0f, -10.0f));

			DrawParthenon(modelMatrix);
		}

		if(g_bDrawLookatPoint)
		{
			glDisable(GL_DEPTH_TEST);
			glm::mat4 idenity(1.0f);

			glutil::PushStack push(modelMatrix);

			glm::vec3 cameraAimVec = g_camTarget - camPos;
			modelMatrix.Translate(0.0f, 0.0, -glm::length(cameraAimVec));
			modelMatrix.Scale(1.0f, 1.0f, 1.0f);
		
			glUseProgram(ObjectColor.theProgram);
			glUniformMatrix4fv(ObjectColor.modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
			glUniformMatrix4fv(ObjectColor.worldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(idenity));
			g_pCubeColorMesh->Render();
			glUseProgram(0);
			glEnable(GL_DEPTH_TEST);
		}
	}

	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (w / (float)h), g_fzNear, g_fzFar);

	glUseProgram(UniformColor.theProgram);
	glUniformMatrix4fv(UniformColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(ObjectColor.theProgram);
	glUniformMatrix4fv(ObjectColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(UniformColorTint.theProgram);
	glUniformMatrix4fv(UniformColorTint.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		delete g_pConeMesh;
		g_pConeMesh = NULL;
		delete g_pCylinderMesh;
		g_pCylinderMesh = NULL;
		delete g_pCubeTintMesh;
		g_pCubeTintMesh = NULL;
		delete g_pCubeColorMesh;
		g_pCubeColorMesh = NULL;
		delete g_pPlaneMesh;
		g_pPlaneMesh = NULL;
		glutLeaveMainLoop();
		return;
	case 'w': g_camTarget.z -= 4.0f; break;
	case 's': g_camTarget.z += 4.0f; break;
	case 'd': g_camTarget.x += 4.0f; break;
	case 'a': g_camTarget.x -= 4.0f; break;
	case 'e': g_camTarget.y -= 4.0f; break;
	case 'q': g_camTarget.y += 4.0f; break;
	case 'W': g_camTarget.z -= 0.4f; break;
	case 'S': g_camTarget.z += 0.4f; break;
	case 'D': g_camTarget.x += 0.4f; break;
	case 'A': g_camTarget.x -= 0.4f; break;
	case 'E': g_camTarget.y -= 0.4f; break;
	case 'Q': g_camTarget.y += 0.4f; break;
	case 'i': g_sphereCamRelPos.y -= 11.25f; break;
	case 'k': g_sphereCamRelPos.y += 11.25f; break;
	case 'j': g_sphereCamRelPos.x -= 11.25f; break;
	case 'l': g_sphereCamRelPos.x += 11.25f; break;
	case 'o': g_sphereCamRelPos.z -= 5.0f; break;
	case 'u': g_sphereCamRelPos.z += 5.0f; break;
	case 'I': g_sphereCamRelPos.y -= 1.125f; break;
	case 'K': g_sphereCamRelPos.y += 1.125f; break;
	case 'J': g_sphereCamRelPos.x -= 1.125f; break;
	case 'L': g_sphereCamRelPos.x += 1.125f; break;
	case 'O': g_sphereCamRelPos.z -= 0.5f; break;
	case 'U': g_sphereCamRelPos.z += 0.5f; break;
		
	case 32:
		g_bDrawLookatPoint = !g_bDrawLookatPoint;
		printf("Target: %f, %f, %f\n", g_camTarget.x, g_camTarget.y, g_camTarget.z);
		printf("Position: %f, %f, %f\n", g_sphereCamRelPos.x, g_sphereCamRelPos.y, g_sphereCamRelPos.z);
		break;
	}

	g_sphereCamRelPos.y = glm::clamp(g_sphereCamRelPos.y, -78.75f, -1.0f);
	g_camTarget.y = g_camTarget.y > 0.0f ? g_camTarget.y : 0.0f;
	g_sphereCamRelPos.z = g_sphereCamRelPos.z > 5.0f ? g_sphereCamRelPos.z : 5.0f;

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
