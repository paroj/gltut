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

	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;

	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint normalModelToCameraMatrixUnif;
	GLuint cameraSpaceLightPosUnif;
	GLuint clipToCameraMatrixUnif;
	GLuint windowSizeUnif;
	GLuint depthRangeUnif;
	GLuint lightAttenuationUnif;
	GLuint bUseRSquareUnif;
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
	data.lightIntensityUnif = glGetUniformLocation(data.theProgram, "lightIntensity");
	data.ambientIntensityUnif = glGetUniformLocation(data.theProgram, "ambientIntensity");

	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");
	data.cameraSpaceLightPosUnif = glGetUniformLocation(data.theProgram, "cameraSpaceLightPos");
	data.clipToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "clipToCameraMatrix");
	data.windowSizeUnif = glGetUniformLocation(data.theProgram, "windowSize");
	data.depthRangeUnif = glGetUniformLocation(data.theProgram, "depthRange");
	data.lightAttenuationUnif = glGetUniformLocation(data.theProgram, "lightAttenuation");
	data.bUseRSquareUnif = glGetUniformLocation(data.theProgram, "bUseRSquare");

	return data;
}

void InitializePrograms()
{
	g_FragWhiteDiffuseColor = LoadLitProgram("FragLightAtten_PN.vert", "FragLightAtten.frag");
	g_FragVertexDiffuseColor = LoadLitProgram("FragLightAtten_PCN.vert", "FragLightAtten.frag");

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

	const float depthZNear = 0.0f;
	const float depthZFar = 1.0f;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(depthZNear, depthZFar);
	glEnable(GL_DEPTH_CLAMP);

	glUseProgram(g_FragWhiteDiffuseColor.theProgram);
	glUniform2f(g_FragWhiteDiffuseColor.depthRangeUnif,depthZNear, depthZFar);
	glUseProgram(g_FragVertexDiffuseColor.theProgram);
	glUniform2f(g_FragVertexDiffuseColor.depthRangeUnif,depthZNear, depthZFar);
	glUseProgram(0);
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
static bool g_bUseRSquare = false;

static float g_fLightAttenuation = 1.0f;

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
		const glm::vec4 &lightPosCameraSpace = modelMatrix.Top() * worldLightPos;

		glUseProgram(g_FragWhiteDiffuseColor.theProgram);
		glUniform4f(g_FragWhiteDiffuseColor.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(g_FragWhiteDiffuseColor.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(g_FragWhiteDiffuseColor.cameraSpaceLightPosUnif,1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(g_FragWhiteDiffuseColor.lightAttenuationUnif, g_fLightAttenuation);
		glUniform1i(g_FragWhiteDiffuseColor.bUseRSquareUnif, g_bUseRSquare ? 1 : 0);

		glUseProgram(g_FragVertexDiffuseColor.theProgram);
		glUniform4f(g_FragVertexDiffuseColor.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(g_FragVertexDiffuseColor.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(g_FragVertexDiffuseColor.cameraSpaceLightPosUnif, 1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(g_FragVertexDiffuseColor.lightAttenuationUnif, g_fLightAttenuation);
		glUniform1i(g_FragVertexDiffuseColor.bUseRSquareUnif, g_bUseRSquare ? 1 : 0);
		glUseProgram(0);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			//Render the ground plane.
			{
				Framework::MatrixStackPusher push(modelMatrix);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				glUseProgram(g_FragWhiteDiffuseColor.theProgram);
				glUniformMatrix4fv(g_FragWhiteDiffuseColor.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glUniformMatrix3fv(g_FragWhiteDiffuseColor.normalModelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(normMatrix));
				g_pPlaneMesh->Render();
				glUseProgram(0);
			}

			//Render the Cylinder
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.ApplyMatrix(g_objectPole.CalcMatrix());

				if(g_bScaleCyl)
					modelMatrix.Scale(1.0f, 1.0f, 0.2f);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				if(g_bDrawColoredCyl)
				{
					glUseProgram(g_FragVertexDiffuseColor.theProgram);
					glUniformMatrix4fv(g_FragVertexDiffuseColor.modelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(modelMatrix.Top()));

					glUniformMatrix3fv(g_FragVertexDiffuseColor.normalModelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(normMatrix));
					g_pCylinderMesh->Render("tint");
				}
				else
				{
					glUseProgram(g_FragWhiteDiffuseColor.theProgram);
					glUniformMatrix4fv(g_FragWhiteDiffuseColor.modelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(modelMatrix.Top()));

					glUniformMatrix3fv(g_FragWhiteDiffuseColor.normalModelToCameraMatrixUnif, 1, GL_FALSE,
						glm::value_ptr(normMatrix));
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
	const glm::mat4 &invMat = glm::inverse(persMatrix.Top());

	glUseProgram(g_FragWhiteDiffuseColor.theProgram);
	glUniformMatrix4fv(g_FragWhiteDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUniform2i(g_FragWhiteDiffuseColor.windowSizeUnif, w, h);
	glUniformMatrix4fv(g_FragWhiteDiffuseColor.clipToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(invMat));

	glUseProgram(g_FragVertexDiffuseColor.theProgram);
	glUniformMatrix4fv(g_FragVertexDiffuseColor.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUniform2i(g_FragVertexDiffuseColor.windowSizeUnif, w, h);
	glUniformMatrix4fv(g_FragVertexDiffuseColor.clipToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(invMat));

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
	bool bChangedAtten = false;
	bool bChangedType = false;
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

	case 'o': g_fLightAttenuation *= 1.5f; bChangedAtten = true; break;
	case 'u': g_fLightAttenuation /= 1.5f; bChangedAtten = true; break;
	case 'O': g_fLightAttenuation *= 1.1f; bChangedAtten = true; break;
	case 'U': g_fLightAttenuation /= 1.1f; bChangedAtten = true; break;

	case 'y': g_bDrawLight = !g_bDrawLight; break;
	case 't': g_bScaleCyl = !g_bScaleCyl; break;
	case 'b': g_bRotateLight = !g_bRotateLight; break;

	case 'h':
		g_bUseRSquare = !g_bUseRSquare;
		if(g_bUseRSquare)
			printf("Inverse Squared Attenuation\n");
		else
			printf("Plain Inverse Attenuation\n");
		break;
	}

	if(g_fLightRadius < 0.2f)
		g_fLightRadius = 0.2f;

	if(g_fLightAttenuation < 0.1f)
		g_fLightAttenuation = 0.1f;

	if(bChangedAtten)
		printf("Atten: %f\n", g_fLightAttenuation); 

	glutPostRedisplay();
}


