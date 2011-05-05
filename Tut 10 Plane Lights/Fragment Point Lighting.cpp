#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glload/gl_3_2_comp.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MatrixStack.h"
#include "../framework/MousePole.h"
#include "../framework/ObjectPole.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint modelSpaceLightPosUnif;
	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_WhiteDiffuseColor;
ProgramData g_VertexDiffuseColor;
ProgramData g_FragWhiteDiffuseColor;
ProgramData g_FragVertexDiffuseColor;

UnlitProgData g_Unlit;

UnlitProgData LoadUnlitProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	UnlitProgData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");
	data.objectColorUnif = glGetUniformLocation(data.theProgram, "objectColor");

	return data;
}

ProgramData LoadLitProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");
	data.modelSpaceLightPosUnif = glGetUniformLocation(data.theProgram, "modelSpaceLightPos");
	data.lightIntensityUnif = glGetUniformLocation(data.theProgram, "lightIntensity");
	data.ambientIntensityUnif = glGetUniformLocation(data.theProgram, "ambientIntensity");

	return data;
}

void InitializePrograms()
{
	g_WhiteDiffuseColor = LoadLitProgram("ModelPosVertexLighting_PN.vert", "ColorPassthrough.frag");
	g_VertexDiffuseColor = LoadLitProgram("ModelPosVertexLighting_PCN.vert", "ColorPassthrough.frag");
	g_FragWhiteDiffuseColor = LoadLitProgram("FragmentLighting_PN.vert", "FragmentLighting.frag");
	g_FragVertexDiffuseColor = LoadLitProgram("FragmentLighting_PCN.vert", "FragmentLighting.frag");

	g_Unlit = LoadUnlitProgram("PosTransform.vert", "UniformColor.frag");
}

Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;
Framework::Mesh *g_pCubeMesh = NULL;

Framework::RadiusDef radiusDef = {5.0f, 3.0f, 200.0f, 1.5f, 0.5f};
glm::vec3 objectCenter = glm::vec3(0.0f, 0.5f, 0.0f);

Framework::MousePole g_mousePole(objectCenter, radiusDef);
Framework::ObjectPole g_objectPole(objectCenter, &g_mousePole);

namespace
{
	void MouseMotion(int x, int y)
	{
		g_mousePole.GLUTMouseMove(glm::ivec2(x, y));
		g_objectPole.GLUTMouseMove(glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		g_mousePole.GLUTMouseButton(button, state, glm::ivec2(x, y));
		g_objectPole.GLUTMouseButton(button, state, glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		g_mousePole.GLUTMouseWheel(direction, glm::ivec2(x, y));
		g_objectPole.GLUTMouseWheel(direction, glm::ivec2(x, y));
		glutPostRedisplay();
	}
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pCylinderMesh = new Framework::Mesh("UnitCylinder.xml");
		g_pPlaneMesh = new Framework::Mesh("LargePlane.xml");
		g_pCubeMesh = new Framework::Mesh("UnitCube.xml");
	}
	catch(std::exception &except)
	{
		printf(except.what());
	}

 	glutMouseFunc(MouseButton);
 	glutMotionFunc(MouseMotion);
	glutMouseWheelFunc(MouseWheel);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_CLAMP);
}

static float g_fLightHeight = 1.5f;
static float g_fLightRadius = 1.0f;
static bool g_bRotateLight = true;

static float g_fRotateTime = 0.0f;
static float g_fPrevTime = 0.0f;

glm::vec4 CalcLightPosition()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fCurrTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float fDeltaTime = fCurrTime - g_fPrevTime;
	g_fPrevTime = fCurrTime;

	if(g_bRotateLight)
		g_fRotateTime += fDeltaTime;

	float fCurrTimeThroughLoop = fmodf(g_fRotateTime, fLoopDuration);

	glm::vec4 ret(0.0f, g_fLightHeight, 0.0f, 1.0f);

	ret.x = cosf(fCurrTimeThroughLoop * fScale) * g_fLightRadius;
	ret.z = sinf(fCurrTimeThroughLoop * fScale) * g_fLightRadius;

	return ret;
}

static bool g_bUseFragmentLighting = true;
static bool g_bDrawColoredCyl = false;
static bool g_bDrawLight = false;
static bool g_bScaleCyl = false;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlaneMesh && g_pCylinderMesh && g_pCubeMesh)
	{
		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_mousePole.CalcMatrix());

		const glm::vec4 &worldLightPos = CalcLightPosition();

		glm::vec4 lightPosCameraSpace = modelMatrix.Top() * worldLightPos;

		ProgramData *pWhiteProgram = NULL;
		ProgramData *pVertColorProgram = NULL;

		if(g_bUseFragmentLighting)
		{
			pWhiteProgram = &g_FragWhiteDiffuseColor;
			pVertColorProgram = &g_FragVertexDiffuseColor;
		}
		else
		{
			pWhiteProgram = &g_WhiteDiffuseColor;
			pVertColorProgram = &g_VertexDiffuseColor;
		}

		glUseProgram(pWhiteProgram->theProgram);
		glUniform4f(pWhiteProgram->lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(pWhiteProgram->ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUseProgram(pVertColorProgram->theProgram);
		glUniform4f(pVertColorProgram->lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(pVertColorProgram->ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUseProgram(0);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			//Render the ground plane.
			{
				Framework::MatrixStackPusher push(modelMatrix);

				glUseProgram(pWhiteProgram->theProgram);
				glUniformMatrix4fv(pWhiteProgram->modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glm::mat4 invTransform = glm::inverse(modelMatrix.Top());
				glm::vec4 lightPosModelSpace = invTransform * lightPosCameraSpace;
				glUniform3fv(pWhiteProgram->modelSpaceLightPosUnif, 1, glm::value_ptr(lightPosModelSpace));

				g_pPlaneMesh->Render();
				glUseProgram(0);
			}

			//Render the Cylinder
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.ApplyMatrix(g_objectPole.CalcMatrix());

				if(g_bScaleCyl)
					modelMatrix.Scale(1.0f, 1.0f, 0.2f);

				glm::mat4 invTransform = glm::inverse(modelMatrix.Top());
				glm::vec4 lightPosModelSpace = invTransform * lightPosCameraSpace;

				if(g_bDrawColoredCyl)
				{
					glUseProgram(pVertColorProgram->theProgram);
					glUniformMatrix4fv(pVertColorProgram->modelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(modelMatrix.Top()));

					glUniform3fv(pVertColorProgram->modelSpaceLightPosUnif, 1, glm::value_ptr(lightPosModelSpace));

					g_pCylinderMesh->Render("tint");
				}
				else
				{
					glUseProgram(pWhiteProgram->theProgram);
					glUniformMatrix4fv(pWhiteProgram->modelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(modelMatrix.Top()));

					glUniform3fv(pWhiteProgram->modelSpaceLightPosUnif, 1, glm::value_ptr(lightPosModelSpace));

					g_pCylinderMesh->Render("flat");
				}
				glUseProgram(0);
			}

			//Render the light
			if(g_bDrawLight)
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.Translate(glm::vec3(worldLightPos));
				modelMatrix.Scale(0.1f, 0.1f, 0.1f);

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));
				glUniform4f(g_Unlit.objectColorUnif, 0.8078f, 0.8706f, 0.9922f, 1.0f);
				g_pCubeMesh->Render("flat");
			}
		}
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	Framework::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (h / (float)w), g_fzNear, g_fzFar);

	glUseProgram(g_WhiteDiffuseColor.theProgram);
	glUniformMatrix4fv(g_WhiteDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_VertexDiffuseColor.theProgram);
	glUniformMatrix4fv(g_VertexDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_FragWhiteDiffuseColor.theProgram);
	glUniformMatrix4fv(g_FragWhiteDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_FragVertexDiffuseColor.theProgram);
	glUniformMatrix4fv(g_FragVertexDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_Unlit.theProgram);
	glUniformMatrix4fv(g_Unlit.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
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
		delete g_pCubeMesh;
		glutLeaveMainLoop();
		break;
		
	case 32:
		g_bDrawColoredCyl = !g_bDrawColoredCyl;
		break;

	case 'i': g_fLightHeight += 0.2f; break;
	case 'k': g_fLightHeight -= 0.2f; break;
	case 'l': g_fLightRadius += 0.2f; break;
	case 'j': g_fLightRadius -= 0.2f; break;

	case 'I': g_fLightHeight += 0.05f; break;
	case 'K': g_fLightHeight -= 0.05f; break;
	case 'L': g_fLightRadius += 0.05f; break;
	case 'J': g_fLightRadius -= 0.05f; break;

	case 'y': g_bDrawLight = !g_bDrawLight; break;
	case 't': g_bScaleCyl = !g_bScaleCyl; break;
	case 'h': g_bUseFragmentLighting = !g_bUseFragmentLighting; break;
	case 'b': g_bRotateLight = !g_bRotateLight; break;
	}

	if(g_fLightRadius < 0.2f)
		g_fLightRadius = 0.2f;

	glutPostRedisplay();
}


