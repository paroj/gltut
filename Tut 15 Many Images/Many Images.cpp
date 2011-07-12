#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glimg/glimg.h>
#include <glimg/TextureGenerator.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MatrixStack.h"
#include "../framework/MousePole.h"
#include "../framework/ObjectPole.h"
#include "../framework/Timer.h"
#include "../framework/UniformBlockArray.h"
#include "../framework/directories.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_program;

const int g_projectionBlockIndex = 0;
const int g_colorTexUnit = 0;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	GLuint colorTextureUnif = glGetUniformLocation(data.theProgram, "colorTexture");
	glUseProgram(data.theProgram);
	glUniform1i(colorTextureUnif, g_colorTexUnit);
	glUseProgram(0);

	return data;
}

void InitializePrograms()
{
	g_program = LoadProgram("PT.vert", "Tex.frag");
}

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

Framework::Mesh *g_pPlane = NULL;

GLuint g_projectionUniformBuffer = 0;
GLuint g_testTexture = 0;
GLuint g_testSampler = 0;

void LoadTextures()
{
	std::auto_ptr<glimg::ImageSet> pImageSet;

	try
	{
		std::string filename(LOCAL_FILE_DIR);
		filename.append("checker.dds");

		pImageSet.reset(glimg::loaders::dds::LoadFromFile(filename.c_str()));
		std::auto_ptr<glimg::SingleImage> pImage(pImageSet->GetImage(0, 0, 0));

		glimg::Dimensions dims = pImage->GetDimensions();

		g_testTexture = glimg::CreateTexture(pImageSet.get(), 0);
	}
	catch(std::exception &e)
	{
		printf("%s\n", e.what());
		throw;
	}

	glGenSamplers(1, &g_testSampler);
	glSamplerParameteri(g_testSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_testSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(g_testSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(g_testSampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pPlane = new Framework::Mesh("BigPlane.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

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

	//Setup our Uniform Buffers
	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	LoadTextures();
}

using Framework::Timer;

Timer g_camTimer = Timer(Timer::TT_LOOP, 5.0f);

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlane)
	{
		g_camTimer.Update();



		Framework::MatrixStack modelMatrix;
		const glm::mat4 &worldToCamMat = glm::lookAt(
			glm::vec3(0.0f, 1.0f, -64.0f),
			glm::vec3(0.0f, -5.0f, -44.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		modelMatrix.ApplyMatrix(worldToCamMat);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			glUseProgram(g_program.theProgram);
			glUniformMatrix4fv(g_program.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));

 			glActiveTexture(GL_TEXTURE0 + g_colorTexUnit);
 			glBindTexture(GL_TEXTURE_2D, g_testTexture);
 			glBindSampler(g_colorTexUnit, g_testSampler);

			g_pPlane->Render("tex");

 			glBindSampler(g_colorTexUnit, 0);
 			glBindTexture(GL_TEXTURE_2D, 0);

			glUseProgram(0);
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
		delete g_pPlane;
		g_pPlane = NULL;
		glutLeaveMainLoop();
		break;
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
