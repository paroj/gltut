#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glimg/glimg.h>
#include <glutil/glutil.h>
#include <glimg/TextureGenerator.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MousePole.h"
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

GLuint g_projectionUniformBuffer = 0;
GLuint g_checkerTexture = 0;
GLuint g_mipmapTestTexture = 0;

const int NUM_SAMPLERS = 6;
GLuint g_samplers[NUM_SAMPLERS];

void CreateSamplers()
{
	glGenSamplers(NUM_SAMPLERS, &g_samplers[0]);

	for(int samplerIx = 0; samplerIx < NUM_SAMPLERS; samplerIx++)
	{
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	//Nearest
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Linear
	glSamplerParameteri(g_samplers[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Linear mipmap Nearest
	glSamplerParameteri(g_samplers[2], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[2], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	//Linear mipmap linear
	glSamplerParameteri(g_samplers[3], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[3], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Low anisotropic
	glSamplerParameteri(g_samplers[4], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[4], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(g_samplers[4], GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);

	//Max anisotropic
	GLfloat maxAniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);

	printf("Maximum anisotropy: %f\n", maxAniso);

	glSamplerParameteri(g_samplers[5], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[5], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(g_samplers[5], GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
}

void FillWithColor(std::vector<GLubyte> &buffer,
				   GLubyte red, GLubyte green, GLubyte blue,
				   int width, int height)
{
	int numTexels = width * height;
	buffer.resize(numTexels * 3);

	std::vector<GLubyte>::iterator it = buffer.begin();
	while(it != buffer.end())
	{
		*it++ = red;
		*it++ = green;
		*it++ = blue;
	}
}

const GLubyte mipmapColors[] =
{
	0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF,
};

void LoadMipmapTexture()
{
		glGenTextures(1, &g_mipmapTestTexture);
		glBindTexture(GL_TEXTURE_2D, g_mipmapTestTexture);

		GLint oldAlign = 0;
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &oldAlign);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for(int mipmapLevel = 0; mipmapLevel < 8; mipmapLevel++)
		{
			int width = 128 >> mipmapLevel;
			int height = 128 >> mipmapLevel;
			std::vector<GLubyte> buffer;

			const GLubyte *pCurrColor = &mipmapColors[mipmapLevel * 3];
			FillWithColor(buffer, pCurrColor[0], pCurrColor[1], pCurrColor[2], width, height);

			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGB8, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, &buffer[0]);
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, oldAlign);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 7);
		glBindTexture(GL_TEXTURE_2D, 0);
}

void LoadCheckerTexture()
{
	try
	{
		std::string filename(LOCAL_FILE_DIR);
		filename += "checker.dds";

		std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::dds::LoadFromFile(filename.c_str()));

		glGenTextures(1, &g_checkerTexture);
		glBindTexture(GL_TEXTURE_2D, g_checkerTexture);

		for(int mipmapLevel = 0; mipmapLevel < pImageSet->GetMipmapCount(); mipmapLevel++)
		{
			glimg::SingleImage image = pImageSet->GetImage(mipmapLevel, 0, 0);
			glimg::Dimensions dims = image.GetDimensions();

			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGB8, dims.width, dims.height, 0,
				GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, image.GetImageData());
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, pImageSet->GetMipmapCount() - 1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	catch(std::exception &e)
	{
		printf("%s\n", e.what());
		throw;
	}
}

Framework::Mesh *g_pPlane = NULL;
Framework::Mesh *g_pCorridor = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pCorridor = new Framework::Mesh("Corridor.xml");
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

	LoadCheckerTexture();
	LoadMipmapTexture();
	CreateSamplers();
}

using Framework::Timer;

Timer g_camTimer = Timer(Timer::TT_LOOP, 5.0f);
int g_currSampler = 0;

bool g_useMipmapTexture = false;
bool g_drawCorridor = false;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlane && g_pCorridor)
	{
		g_camTimer.Update();

		float cyclicAngle = g_camTimer.GetAlpha() * 6.28f;
		float hOffset = cosf(cyclicAngle) * 0.25f;
		float vOffset = sinf(cyclicAngle) * 0.25f;

		glutil::MatrixStack modelMatrix;

		const glm::mat4 &worldToCamMat = glm::lookAt(
			glm::vec3(hOffset, 1.0f, -64.0f),
			glm::vec3(hOffset, -5.0f + vOffset, -44.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		modelMatrix *= worldToCamMat;

		glutil::PushStack push(modelMatrix);

		glUseProgram(g_program.theProgram);
		glUniformMatrix4fv(g_program.modelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));

		glActiveTexture(GL_TEXTURE0 + g_colorTexUnit);
		glBindTexture(GL_TEXTURE_2D,
			g_useMipmapTexture ? g_mipmapTestTexture : g_checkerTexture);
		glBindSampler(g_colorTexUnit, g_samplers[g_currSampler]);

		if(g_drawCorridor)
			g_pCorridor->Render("tex");
		else
			g_pPlane->Render("tex");

		glBindSampler(g_colorTexUnit, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(90.0f, (w / (float)h), g_fzNear, g_fzFar);

	ProjectionBlock projData;
	projData.cameraToClipMatrix = persMatrix.Top();

	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ProjectionBlock), &projData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}

const char *g_samplerNames[NUM_SAMPLERS] =
{
	"Nearest",
	"Linear",
	"Linear with nearest mipmaps",
	"Linear with linear mipmaps",
	"Low anisotropic",
	"Max anisotropic",
};

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
		delete g_pCorridor;
		g_pPlane = NULL;
		g_pCorridor = NULL;
		glutLeaveMainLoop();
		return;
	case 32:
		g_useMipmapTexture = !g_useMipmapTexture;
		break;
	case 'y':
		g_drawCorridor = !g_drawCorridor;
		break;
	case 'p':
		g_camTimer.TogglePause();
		break;
	}

	if(('1' <= key) && (key <= '9'))
	{
		int number = key - '1';
		if(number < NUM_SAMPLERS)
		{
			printf("Sampler: %s\n", g_samplerNames[number]);
			g_currSampler = number;
		}
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
