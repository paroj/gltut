#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
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

	GLuint dirToLightUnif;
	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint modelToCameraMatrixUnif;
	GLuint normalModelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_WhiteDiffuseColor;
ProgramData g_VertexDiffuseColor;
ProgramData g_WhiteAmbDiffuseColor;
ProgramData g_VertexAmbDiffuseColor;

const int g_projectionBlockIndex = 2;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");
	data.dirToLightUnif = glGetUniformLocation(data.theProgram, "dirToLight");
	data.lightIntensityUnif = glGetUniformLocation(data.theProgram, "lightIntensity");
	data.ambientIntensityUnif = glGetUniformLocation(data.theProgram, "ambientIntensity");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

void InitializeProgram()
{
	g_WhiteDiffuseColor = LoadProgram("DirVertexLighting_PN.vert", "ColorPassthrough.frag");
	g_VertexDiffuseColor = LoadProgram("DirVertexLighting_PCN.vert", "ColorPassthrough.frag");
	g_WhiteAmbDiffuseColor = LoadProgram("DirAmbVertexLighting_PN.vert", "ColorPassthrough.frag");
	g_VertexAmbDiffuseColor = LoadProgram("DirAmbVertexLighting_PCN.vert", "ColorPassthrough.frag");
}

Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;

Framework::RadiusDef radiusDef = {5.0f, 3.0f, 20.0f, 1.5f, 0.5f};
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


GLuint g_projectionUniformBuffer = 0;

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

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
		printf("%s\n", except.what());
		throw;
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

	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	//Bind the static buffers.
	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

glm::vec4 g_lightDirection(0.866f, 0.5f, 0.0f, 0.0f);

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
		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_mousePole.CalcMatrix());

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

				modelMatrix.ApplyMatrix(g_objectPole.CalcMatrix());

				if(g_bDrawColoredCyl)
				{
					glUseProgram(vertexDiffuse.theProgram);
					glUniformMatrix4fv(vertexDiffuse.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
					glm::mat3 normMatrix(modelMatrix.Top());
					glUniformMatrix3fv(vertexDiffuse.normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
					g_pCylinderMesh->Render("lit-color");
				}
				else
				{
					glUseProgram(whiteDiffuse.theProgram);
					glUniformMatrix4fv(whiteDiffuse.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
					glm::mat3 normMatrix(modelMatrix.Top());
					glUniformMatrix3fv(whiteDiffuse.normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
					g_pCylinderMesh->Render("lit");
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

	ProjectionBlock projData;
	projData.cameraToClipMatrix = persMatrix.Top();

	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ProjectionBlock), &projData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

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
		return;

	case 32:
		g_bDrawColoredCyl = !g_bDrawColoredCyl;
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

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
