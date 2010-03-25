
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <glloader/gl_3_2_comp.h>
#include <glloader/wgl_exts.h>
#include <glloader/gle.h>
#include <GL/freeglut.h>

/* report GL errors, if any, to stderr */
void checkError(const char *functionName)
{
	GLenum error;
	while (( error = glGetError() ) != GL_NO_ERROR) {
		fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
	}
}

/* vertex array data for a colored 2D triangle, consisting of RGB color values
and XY coordinates */
const GLfloat varray[] = {
	1.0f, 0.0f, 0.0f, /* red */
	5.0f, 5.0f,       /* lower left */

	0.0f, 1.0f, 0.0f, /* green */
	25.0f, 5.0f,      /* lower right */

	0.0f, 0.0f, 1.0f, /* blue */
	5.0f, 25.0f       /* upper left */
};

/* ISO C somehow enforces this silly use of 'enum' for compile-time constants */
enum {
	numColorComponents = 3,
	numVertexComponents = 2,
	stride = sizeof(GLfloat) * (numColorComponents + numVertexComponents),
	numElements = sizeof(varray) / stride
};

/* the name of the vertex buffer object */
GLuint vertexBufferName;

void initBuffer(void)
{
	glGenBuffers (1, &vertexBufferName);
	glBindBuffer (GL_ARRAY_BUFFER, vertexBufferName);
	glBufferData (GL_ARRAY_BUFFER, sizeof(varray), varray, GL_STATIC_DRAW);
	checkError ("initBuffer");
}

const GLchar *vertexShaderSource[] = {
	"#version 140\n",
	"uniform mat4 fg_ProjectionMatrix;\n",
	"in vec4 fg_Color;\n",
	"in vec4 fg_Vertex;\n",
	"smooth out vec4 fg_SmoothColor;\n",
	"void main()\n",
	"{\n",
	"   fg_SmoothColor = fg_Color;\n",
	"   gl_Position = fg_ProjectionMatrix * fg_Vertex;\n",
	"}\n"
};

const GLchar *fragmentShaderSource[] = {
	"#version 140\n",
	"smooth in vec4 fg_SmoothColor;\n",
	"out vec4 fg_FragColor;\n",
	"void main(void)\n",
	"{\n",
	"   fg_FragColor = fg_SmoothColor;\n",
	"}\n"
};

void compileAndCheck(GLuint shader)
{
	GLint status;
	glCompileShader (shader);
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		GLchar *infoLog;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = (GLchar*) malloc (infoLogLength);
		glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
		fprintf (stderr, "compile log: %s\n", infoLog);
		free (infoLog);
	}
}

GLuint compileShaderSource(GLenum type, GLsizei count, const GLchar **string)
{
	GLuint shader = glCreateShader (type);
	glShaderSource (shader, count, string, NULL);
	compileAndCheck (shader);
	return shader;
}

void linkAndCheck(GLuint program)
{
	GLint status;
	glLinkProgram (program);
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		GLchar *infoLog;
		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = (GLchar*) malloc (infoLogLength);
		glGetProgramInfoLog (program, infoLogLength, NULL, infoLog);
		fprintf (stderr, "link log: %s\n", infoLog);
		free (infoLog);
	}
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram ();
	if (vertexShader != 0) {
		glAttachShader (program, vertexShader);
	}
	if (fragmentShader != 0) {
		glAttachShader (program, fragmentShader);
	}
	linkAndCheck (program);
	return program;
}

GLuint fgProjectionMatrixIndex;
GLuint fgColorIndex;
GLuint fgVertexIndex;

void initShader(void)
{
	const GLsizei vertexShaderLines = sizeof(vertexShaderSource) / sizeof(GLchar*);
	GLuint vertexShader =
		compileShaderSource (GL_VERTEX_SHADER, vertexShaderLines, vertexShaderSource);

	const GLsizei fragmentShaderLines = sizeof(fragmentShaderSource) / sizeof(GLchar*);
	GLuint fragmentShader =
		compileShaderSource (GL_FRAGMENT_SHADER, fragmentShaderLines, fragmentShaderSource);

	GLuint program = createProgram (vertexShader, fragmentShader);

	glUseProgram (program);

	fgProjectionMatrixIndex = glGetUniformLocation(program, "fg_ProjectionMatrix");

	fgColorIndex = glGetAttribLocation(program, "fg_Color");
	glEnableVertexAttribArray (fgColorIndex);

	fgVertexIndex = glGetAttribLocation(program, "fg_Vertex");
	glEnableVertexAttribArray (fgVertexIndex);

	checkError ("initShader");
}

void initRendering(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	checkError ("initRendering");
}

void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
	checkError ("dumpInfo");
}

void init(void) 
{
	dumpInfo ();

	initBuffer ();
	initShader ();
	initRendering ();
}

const GLvoid *bufferObjectPtr (GLsizei index)
{
	return (const GLvoid *) (((char *) NULL) + index);
}

GLfloat projectionMatrix[16];

void triangle(void)
{
	glUniformMatrix4fv (fgProjectionMatrixIndex, 1, GL_FALSE, projectionMatrix);

	glBindBuffer (GL_ARRAY_BUFFER, vertexBufferName);
	glVertexAttribPointer (fgColorIndex, numColorComponents, GL_FLOAT, GL_FALSE,
		stride, bufferObjectPtr (0));
	glVertexAttribPointer (fgVertexIndex, numVertexComponents, GL_FLOAT, GL_FALSE,
		stride, bufferObjectPtr (sizeof(GLfloat) * numColorComponents));
	glDrawArrays(GL_TRIANGLES, 0, numElements);
	checkError ("triangle");
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	triangle ();
	checkError ("display");
	glutSwapBuffers();
}

void loadOrthof(GLfloat *m, GLfloat l, GLfloat r, GLfloat b, GLfloat t,
				GLfloat n, GLfloat f)
{
	m[ 0] = 2.0f / (r - l);
	m[ 1] = 0.0f;
	m[ 2] = 0.0f;
	m[ 3] = 0.0f;

	m[ 4] = 0.0f;
	m[ 5] = 2.0f / (t - b);
	m[ 6] = 0.0f;
	m[ 7] = 0.0f;

	m[ 8] = 0.0f;
	m[ 9] = 0.0f;
	m[10] = -2.0f / (f - n);
	m[11] = 0.0f;

	m[12] = -(r + l) / (r - l);
	m[13] = -(t + b) / (t - b);
	m[14] = -(f + n) / (f - n);
	m[15] = 1.0f;
}

void loadOrtho2Df(GLfloat *m, GLfloat l, GLfloat r, GLfloat b, GLfloat t)
{
	loadOrthof (m, l, r, b, t, -1.0f, 1.0f);
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	if (w <= h) {
		loadOrtho2Df (projectionMatrix, 0.0f, 30.0f, 0.0f, 30.0f * (GLfloat) h/(GLfloat) w);
	} else {
		loadOrtho2Df (projectionMatrix, 0.0f, 30.0f * (GLfloat) w/(GLfloat) h, 0.0f, 30.0f);
	}
	checkError ("reshape");
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	  case 27:
		  glutLeaveMainLoop();
		  break;
	}
}