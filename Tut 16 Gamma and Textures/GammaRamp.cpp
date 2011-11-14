
#include <string>
#include <memory>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <glload/gl_3_3.h>
#include <glm/glm.hpp>
#include <glimg/glimg.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/directories.h"

const int g_projectionBlockIndex = 0;
const int g_gammaRampTextureUnit = 0;

GLuint g_noGammaProgram = 0;
GLuint g_gammaProgram = 0;

void InitializeProgram()
{
	GLuint vertexShader = Framework::LoadShader(GL_VERTEX_SHADER, "screenCoords.vert");
	std::vector<GLuint> shaderList;

	shaderList.push_back(vertexShader);
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "textureNoGamma.frag"));

	g_noGammaProgram = Framework::CreateProgram(shaderList);
	glDeleteShader(shaderList.back());

	shaderList.pop_back();
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "textureGamma.frag"));

	g_gammaProgram = Framework::CreateProgram(shaderList);
	glDeleteShader(shaderList.back());
	glDeleteShader(vertexShader);

	GLuint projectionBlock = glGetUniformBlockIndex(g_noGammaProgram, "Projection");
	glUniformBlockBinding(g_noGammaProgram, projectionBlock, g_projectionBlockIndex);

	GLuint colorTextureUnif = glGetUniformLocation(g_noGammaProgram, "colorTexture");
	glUseProgram(g_noGammaProgram);
	glUniform1i(colorTextureUnif, g_gammaRampTextureUnit);
	glUseProgram(0);

	projectionBlock = glGetUniformBlockIndex(g_gammaProgram, "Projection");
	glUniformBlockBinding(g_gammaProgram, projectionBlock, g_projectionBlockIndex);

	colorTextureUnif = glGetUniformLocation(g_gammaProgram, "colorTexture");
	glUseProgram(g_gammaProgram);
	glUniform1i(colorTextureUnif, g_gammaRampTextureUnit);
	glUseProgram(0);
}

const GLushort vertexData[] = {
	 90, 80,	0,		0,
	 90, 16,	0,		65535,
	410, 80,	65535,	0,
	410, 16,	65535,	65535,

	 90, 176,	0,		0,
	 90, 112,	0,		65535,
	410, 176,	65535,	0,
	410, 112,	65535,	65535,
};

GLuint g_dataBufferObject;
GLuint g_vao;


void InitializeVertexData()
{
	glGenBuffers(1, &g_dataBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, g_dataBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &g_vao);

	glBindVertexArray(g_vao);
	glBindBuffer(GL_ARRAY_BUFFER, g_dataBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_UNSIGNED_SHORT, GL_FALSE, 8, (void*)0);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_UNSIGNED_SHORT, GL_TRUE, 8, (void*)4);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_projectionUniformBuffer;
GLuint g_textures[2];
GLuint g_samplerObj;

void LoadTextures()
{
	glGenTextures(2, g_textures);

	std::string filename(LOCAL_FILE_DIR);
	filename += "gamma_ramp.png";

	try
	{
		std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::stb::LoadFromFile(filename.c_str()));

		glimg::SingleImage image = pImageSet->GetImage(0, 0, 0);
		glimg::Dimensions dims = image.GetDimensions();

		glimg::OpenGLPixelTransferParams pxTrans = glimg::GetUploadFormatType(pImageSet->GetFormat(), 0);

		glBindTexture(GL_TEXTURE_2D, g_textures[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, dims.width, dims.height, 0,
			pxTrans.format, pxTrans.type, image.GetImageData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, pImageSet->GetMipmapCount() - 1);

		glBindTexture(GL_TEXTURE_2D, g_textures[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, dims.width, dims.height, 0,
			pxTrans.format, pxTrans.type, image.GetImageData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, pImageSet->GetMipmapCount() - 1);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	catch(std::exception &e)
	{
		printf("%s\n", e.what());
		throw;
	}

	glGenSamplers(1, &g_samplerObj);
	glSamplerParameteri(g_samplerObj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(g_samplerObj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(g_samplerObj, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(g_samplerObj, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexData();
	LoadTextures();

	//Setup our Uniform Buffers
	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool g_useGammaCorrect[2] = {false, false};

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.5f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0 + g_gammaRampTextureUnit);
	glBindTexture(GL_TEXTURE_2D, g_textures[g_useGammaCorrect[0] ? 1 : 0]);
	glBindSampler(g_gammaRampTextureUnit, g_samplerObj);

	glBindVertexArray(g_vao);

	glUseProgram(g_noGammaProgram);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindTexture(GL_TEXTURE_2D, g_textures[g_useGammaCorrect[1] ? 1 : 0]);

	glUseProgram(g_gammaProgram);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

	glBindVertexArray(0);
	glUseProgram(0);

	glActiveTexture(GL_TEXTURE0 + g_gammaRampTextureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindSampler(g_gammaRampTextureUnit, 0);

	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Translate(-1.0f, 1.0f, 0.0f);
	persMatrix.Scale(2.0f / w, -2.0f / h, 1.0f);

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
		glutLeaveMainLoop();
		return;
	case '1':
		g_useGammaCorrect[0] = !g_useGammaCorrect[0];
		if(g_useGammaCorrect[0])
			printf("Top:\tsRGB texture.\n");
		else
			printf("Top:\tlinear texture.\n");
		break;
	case '2':
		g_useGammaCorrect[1] = !g_useGammaCorrect[1];
		if(g_useGammaCorrect[1])
			printf("Bottom:\tsRGB texture.\n");
		else
			printf("Bottom:\tlinear texture.\n");
		break;

	case 32:
		break;
	}

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {height = 192; return displayMode;}
