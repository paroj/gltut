


#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;

GLuint offsetUniform;
GLuint perspectiveMatrixUnif;

float perspectiveMatrix[16];
const float fFrustumScale = 1.0f;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "Standard.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "Standard.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	offsetUniform = glGetUniformLocation(theProgram, "offset");

	perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");

	float fzNear = 1.0f; float fzFar = 100000.0f;

	memset(perspectiveMatrix, 0, sizeof(float) * 16);

	perspectiveMatrix[0] = fFrustumScale;
	perspectiveMatrix[5] = fFrustumScale;
	perspectiveMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
	perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
	perspectiveMatrix[11] = -1.0f;

	glUseProgram(theProgram);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(0);
}

const int numberOfVertices = 8;

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f

const float Z_OFFSET = 0.5f;

const float vertexData[] = {
	//Front face positions
	-400.0f,		 400.0f,			0.0f,
	400.0f,		 400.0f,			0.0f,
	400.0f,		-400.0f,			0.0f,
	-400.0f,		-400.0f,			0.0f,

	//Rear face positions
	-200.0f,		 600.0f,			-Z_OFFSET,
	600.0f,		 600.0f,			0.0f - Z_OFFSET,
	600.0f,		-200.0f,			0.0f - Z_OFFSET,
	-200.0f,		-200.0f,			-Z_OFFSET,

	//Front face colors.
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,

	//Rear face colors.
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,
};

const GLshort indexData[] =
{
	0, 1, 3,
	1, 2, 3,

	4, 5, 7,
	5, 6, 7,
};

GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;


void InitializeVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

float fStart = 2534.0f;
float fDelta = 0.0f;

float CalcZOFfset()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	//float fRet = cosf(fCurrTimeThroughLoop * fScale) * 500.0f - fStart;
	float fRet = fDelta - fStart;

	return fRet;
}

volatile bool bReadBuffer = false;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(theProgram);
	glBindVertexArray(vao);

	float fZOffset = CalcZOFfset();
	glUniform3f(offsetUniform, 0.0f, 0.0f, fZOffset);
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();

	//Read the backbuffer.
	if(bReadBuffer)
	{
		bReadBuffer = false;

		GLuint *pBuffer = new GLuint[500*500];
		glReadPixels(0, 0, 500, 500, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, pBuffer);

		GLuint error = glGetError();

		std::string strOutput;
		strOutput.reserve(500*500*2 + (500));

		std::map<GLuint, char> charMap;

		GLuint *pBufferLoc = pBuffer;
		for(int y = 0; y < 500; y++)
		{
			for(int x = 0; x < 500; x++)
			{
				GLuint iValue = *pBufferLoc >> 8;
				iValue = iValue & 0x00FFFFFF;

				if(charMap.find(iValue) == charMap.end())
				{
					if(charMap.size())
						charMap[iValue] = static_cast<char>(65 + charMap.size() - 1);
					else
						charMap[iValue] = '.';
				}

				strOutput.push_back(charMap[iValue]);
				strOutput.push_back(' ');

				++pBufferLoc;
			}

			strOutput.push_back('\n');
		}

		delete[] pBuffer;

		{
			static int iFile = 0;
			std::ostringstream temp;
			temp << "test" << iFile << ".txt";
			std::string strFilename = temp.str();

			std::ofstream shaderFile(strFilename.c_str());
			shaderFile << "Offset: " << fZOffset << std::endl;
			for(std::map<GLuint, char>::const_iterator startIt = charMap.begin();
				startIt != charMap.end();
				++startIt)
			{
				shaderFile << startIt->first << "->\'" << startIt->second << "\'" << std::endl;
			}

			shaderFile << strOutput;

			printf("finished\n");

			iFile++;
		}


//		printf(strOutput.c_str());
	}
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	perspectiveMatrix[0] = fFrustumScale * (h / (float)w);
	perspectiveMatrix[5] = fFrustumScale;

	glUseProgram(theProgram);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
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
	case 32:
		{
			float fValue = CalcZOFfset();
			printf("%f\n", fValue);
			bReadBuffer = true;
		}
		break;
		//Hundreds
	case 0x51:	//q
	case 0x71:
		fDelta += 100.0f;
		break;
	case 0x41:	//a
	case 0x61:
		fDelta -= 100.0f;
		break;

		//Tens
	case 0x57:	//w
	case 0x77:
		fDelta += 10.0f;
		break;
	case 0x53:	//s
	case 0x73:
		fDelta -= 10.0f;
		break;

		//Ones
	case 0x45:	//e
	case 0x65:
		fDelta += 1.0f;
		break;
	case 0x44:	//d	
	case 0x64:
		fDelta -= 1.0f;
		break;

		//Tenths
	case 0x52:	//r
	case 0x72:
		fDelta += 0.1f;
		break;
	case 0x46:	//f
	case 0x66:
		fDelta -= 0.1f;
		break;

		//Hundreths
	case 0x54:	//t
	case 0x74:
		fDelta += 0.01f;
		break;
	case 0x47:	//g
	case 0x67:
		fDelta -= 0.01f;
		break;
	}

	printf("%f\n", fDelta);
	glutPostRedisplay();
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
