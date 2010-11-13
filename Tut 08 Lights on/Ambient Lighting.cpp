#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glloader/gl_3_2_comp.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MatrixStack.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint dirToLightUnif;
	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;
	GLuint normalModelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_WhiteDiffuseColor;
ProgramData g_VertexDiffuseColor;
ProgramData g_WhiteAmbDiffuseColor;
ProgramData g_VertexAmbDiffuseColor;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");
	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");
	data.dirToLightUnif = glGetUniformLocation(data.theProgram, "dirToLight");
	data.lightIntensityUnif = glGetUniformLocation(data.theProgram, "lightIntensity");
	data.ambientIntensityUnif = glGetUniformLocation(data.theProgram, "ambientIntensity");

	return data;
}

void InitializeProgram()
{
	g_WhiteDiffuseColor = LoadProgram("DirVertexLighting_PN.vert", "ColorPassthrough.frag");
	g_VertexDiffuseColor = LoadProgram("DirVertexLighting_PCN.vert", "ColorPassthrough.frag");
	g_WhiteAmbDiffuseColor = LoadProgram("DirAmbVertexLighting_PN.vert", "ColorPassthrough.frag");
	g_VertexAmbDiffuseColor = LoadProgram("DirAmbVertexLighting_PCN.vert", "ColorPassthrough.frag");
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

Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();

	try
	{
		g_pCylinderMesh = new Framework::Mesh("UnitCylinder.xml");
		g_pPlaneMesh = new Framework::Mesh("LargePlane.xml");
	}
	catch(std::exception &except)
	{
		printf(except.what());
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

static glm::vec3 g_camTarget(0.0f, 0.5f, 0.0f);

//In spherical coordinates.
static glm::vec3 g_sphereCamRelPos(67.5f, -46.0f, 5.0f);

glm::vec3 ResolveCamPosition()
{
	float rho = Framework::DegToRad(g_sphereCamRelPos.x);
	float theta = Framework::DegToRad(g_sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosRho = cosf(rho);
	float fSinRho = sinf(rho);

	glm::vec3 dirToCamera(fSinTheta * fCosRho, fCosTheta, fSinTheta * fSinRho);
	return (dirToCamera * g_sphereCamRelPos.z) + g_camTarget;
}

glm::vec4 g_lightDirection(0.866f, 0.5f, 0.0f, 0.0f);

static float g_CylYaw = 0.0f;
static float g_CylPitch = 0.0f;
static float g_CylRoll = 0.0f;

static bool g_bDrawColoredCyl = true;
static bool g_bShowAmbient = false; 

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlaneMesh && g_pCylinderMesh)
	{
		const glm::vec3 &camPos = ResolveCamPosition();

		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(CalcLookAtMatrix(camPos, g_camTarget, glm::vec3(0.0f, 1.0f, 0.0f)));

		glm::vec4 lightDirCameraSpace = modelMatrix.Top() * g_lightDirection;

		ProgramData &whiteDiffuse = g_bShowAmbient ? g_WhiteAmbDiffuseColor : g_WhiteDiffuseColor;
		ProgramData &vertexDiffuse = g_bShowAmbient ? g_VertexAmbDiffuseColor : g_VertexDiffuseColor;

		if(g_bShowAmbient)
		{
			glUseProgram(whiteDiffuse.theProgram);
			glUniform4f(whiteDiffuse.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
			glUniform4f(whiteDiffuse.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
			glUseProgram(vertexDiffuse.theProgram);
			glUniform4f(vertexDiffuse.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
			glUniform4f(vertexDiffuse.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		}
		else
		{
			glUseProgram(whiteDiffuse.theProgram);
			glUniform4f(whiteDiffuse.lightIntensityUnif, 1.0f, 1.0f, 1.0f, 1.0f);
			glUseProgram(vertexDiffuse.theProgram);
			glUniform4f(vertexDiffuse.lightIntensityUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		}

		glUseProgram(whiteDiffuse.theProgram);
		glUniform3fv(whiteDiffuse.dirToLightUnif, 1, glm::value_ptr(lightDirCameraSpace));
		glUseProgram(vertexDiffuse.theProgram);
		glUniform3fv(vertexDiffuse.dirToLightUnif, 1, glm::value_ptr(lightDirCameraSpace));
		glUseProgram(0);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			//Render the ground plane.
			{
				Framework::MatrixStackPusher push(modelMatrix);

				glUseProgram(whiteDiffuse.theProgram);
				glUniformMatrix4fv(whiteDiffuse.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
				glm::mat3 normMatrix(modelMatrix.Top());
				glUniformMatrix3fv(whiteDiffuse.normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
				g_pPlaneMesh->Render();
				glUseProgram(0);
			}

			//Render the Cylinder
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.Translate(0.0f, 0.5f, 0.0f);

				modelMatrix.RotateX(g_CylPitch);
				modelMatrix.RotateY(g_CylYaw);
				modelMatrix.RotateZ(g_CylRoll);

				if(g_bDrawColoredCyl)
				{
					glUseProgram(vertexDiffuse.theProgram);
					glUniformMatrix4fv(vertexDiffuse.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
					glm::mat3 normMatrix(modelMatrix.Top());
					glUniformMatrix3fv(vertexDiffuse.normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
					g_pCylinderMesh->Render("tint");
				}
				else
				{
					glUseProgram(whiteDiffuse.theProgram);
					glUniformMatrix4fv(whiteDiffuse.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
					glm::mat3 normMatrix(modelMatrix.Top());
					glUniformMatrix3fv(whiteDiffuse.normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
					g_pCylinderMesh->Render("flat");
				}
				glUseProgram(0);
			}
		}
	}

	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	Framework::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (h / (float)w), g_fzNear, g_fzFar);

	glUseProgram(g_WhiteDiffuseColor.theProgram);
	glUniformMatrix4fv(g_WhiteDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_VertexDiffuseColor.theProgram);
	glUniformMatrix4fv(g_VertexDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_WhiteAmbDiffuseColor.theProgram);
	glUniformMatrix4fv(g_WhiteAmbDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_VertexAmbDiffuseColor.theProgram);
	glUniformMatrix4fv(g_VertexAmbDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
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
		delete g_pPlaneMesh;
		delete g_pCylinderMesh;
		glutLeaveMainLoop();
		break;
	case 'w': g_CylPitch -= 11.25f; break;
	case 's': g_CylPitch += 11.25f; break;
	case 'd': g_CylRoll -= 11.25f; break;
	case 'a': g_CylRoll += 11.25f; break;
	case 'e': g_CylYaw -= 11.25f; break;
	case 'q': g_CylYaw += 11.25f; break;
	case 'W': g_CylPitch -= 4.0f; break;
	case 'S': g_CylPitch += 4.0f; break;
	case 'D': g_CylRoll -= 4.0f; break;
	case 'A': g_CylRoll += 4.0f; break;
	case 'E': g_CylYaw -= 4.0f; break;
	case 'Q': g_CylYaw += 4.0f; break;
	case 'i': g_sphereCamRelPos.y -= 11.25f; break;
	case 'k': g_sphereCamRelPos.y += 11.25f; break;
	case 'j': g_sphereCamRelPos.x += 11.25f; break;
	case 'l': g_sphereCamRelPos.x -= 11.25f; break;
	case 'o': g_sphereCamRelPos.z -= 1.5f; break;
	case 'u': g_sphereCamRelPos.z += 1.5f; break;
	case 'I': g_sphereCamRelPos.y -= 1.125f; break;
	case 'K': g_sphereCamRelPos.y += 1.125f; break;
	case 'J': g_sphereCamRelPos.x += 1.125f; break;
	case 'L': g_sphereCamRelPos.x -= 1.125f; break;
	case 'O': g_sphereCamRelPos.z -= 0.25f; break;
	case 'U': g_sphereCamRelPos.z += 0.25f; break;
		
	case 32:
		g_bDrawColoredCyl = !g_bDrawColoredCyl;
		printf("Position: %f, %f, %f\n", g_sphereCamRelPos.x, g_sphereCamRelPos.y, g_sphereCamRelPos.z);
		printf("Yaw: %f, Pitch: %f, Roll: %f\n", g_CylYaw, g_CylPitch, g_CylRoll);
		break;

	case 't':
	case 'T':
		g_bShowAmbient = !g_bShowAmbient;
		if(g_bShowAmbient)
			printf("Ambient Lighting On.\n");
		else
			printf("Ambient Lighting Off.\n");

		break;
	}

	g_sphereCamRelPos.y = glm::clamp(g_sphereCamRelPos.y, -78.75f, 78.75f);
	g_camTarget.y = g_camTarget.y > 0.0f ? g_camTarget.y : 0.0f;
	g_sphereCamRelPos.z = g_sphereCamRelPos.z > 2.0f ? g_sphereCamRelPos.z : 2.0f;

	glutPostRedisplay();
}


