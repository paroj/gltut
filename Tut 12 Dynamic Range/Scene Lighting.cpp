#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glloader/gl_3_2_comp.h>
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
	GLuint lightAttenuationUnif;
	GLuint shininessFactorUnif;
	GLuint baseDiffuseColorUnif;

	void SetWindowData(const glm::mat4 cameraToClip)
	{
		glUseProgram(theProgram);
		glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(cameraToClip));
		glUseProgram(0);
	}
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;

	void SetWindowData(const glm::mat4 cameraToClip)
	{
		glUseProgram(theProgram);
		glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(cameraToClip));
		glUseProgram(0);
	}

};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

enum LightingModel
{
	LM_GAUSSIAN_SPECULAR = 0,
	LM_GAUSSIAN_ONLY,

	LM_MAX_LIGHTING_MODEL,
};

struct ProgramPairs
{
	ProgramData whiteProg;
	ProgramData colorProg;
};

struct ShaderPairs
{
	const char *strWhiteVertShader;
	const char *strColorVertShader;
	const char *strFragmentShader;
};

ProgramPairs g_Programs[LM_MAX_LIGHTING_MODEL];
ShaderPairs g_ShaderFiles[LM_MAX_LIGHTING_MODEL] =
{
	{"PN.vert", "PCN.vert", "GaussianLighting.frag"},
	{"PN.vert", "PCN.vert", "GaussianOnly.frag"},
};

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
	data.lightAttenuationUnif = glGetUniformLocation(data.theProgram, "lightAttenuation");
	data.shininessFactorUnif = glGetUniformLocation(data.theProgram, "shininessFactor");
	data.baseDiffuseColorUnif = glGetUniformLocation(data.theProgram, "baseDiffuseColor");

	return data;
}

void InitializePrograms()
{
	for(int iProg = 0; iProg < LM_MAX_LIGHTING_MODEL; iProg++)
	{
		g_Programs[iProg].whiteProg = LoadLitProgram(
			g_ShaderFiles[iProg].strWhiteVertShader, g_ShaderFiles[iProg].strFragmentShader);
		g_Programs[iProg].colorProg = LoadLitProgram(
			g_ShaderFiles[iProg].strColorVertShader, g_ShaderFiles[iProg].strFragmentShader);
	}

	g_Unlit = LoadUnlitProgram("PosTransform.vert", "UniformColor.frag");
}

Framework::RadiusDef radiusDef = {150.0f, 3.0f, 500.0f, 6.0f, 2.0f};
glm::vec3 objectCenter = glm::vec3(0.0f, 0.0f, 0.0f);

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

Framework::Mesh *g_pTerrainMesh = NULL;
Framework::Mesh *g_pLightMesh = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pTerrainMesh = new Framework::Mesh("UnitSphere.xml");
		g_pLightMesh = new Framework::Mesh("UnitCube.xml");
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
}

static float g_fLightHeight = 1.5f;
static float g_fLightRadius = 40.0f;
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

static int g_eLightModel = LM_GAUSSIAN_SPECULAR;

bool IsGuassianLightModel()
{
	return (g_eLightModel == LM_GAUSSIAN_ONLY || g_eLightModel == LM_GAUSSIAN_SPECULAR);
}

static bool g_bUseFragmentLighting = true;
static bool g_bDrawColoredCyl = false;
static bool g_bDrawLightSource = false;
static bool g_bScaleCyl = false;
static bool g_bDrawDark = false;

const float g_fLightAttenuation = 1.0f / (50.0f * 50.0f);

const glm::vec4 g_darkColor(0.2f, 0.2f, 0.2f, 1.0f);
const glm::vec4 g_lightColor(1.0f);

class MaterialParams
{
public:
	MaterialParams()
		: m_fPhongExponent(4.0f)
		, m_fBlinnExponent(4.0f)
		, m_fGaussianRoughness(0.5f)
	{}

	operator float() const
	{
		return GetSpecularValue();
	}

	void Increment(bool bIsLarge)
	{
		float &theParam = GetSpecularValue();
		if(IsGuassianLightModel())
		{
			if(bIsLarge)
				theParam += 0.1f;
			else
				theParam += 0.01f;
		}
		else
		{
			if(bIsLarge)
				theParam += 0.5f;
			else
				theParam += 0.1f;
		}

		ClampParam();
	}

	void Decrement(bool bIsLarge)
	{
		float &theParam = GetSpecularValue();
		if(IsGuassianLightModel())
		{
			if(bIsLarge)
				theParam -= 0.1f;
			else
				theParam -= 0.01f;
		}
		else
		{
			if(bIsLarge)
				theParam -= 0.5f;
			else
				theParam -= 0.1f;
		}

		ClampParam();
	}

private:
	float m_fPhongExponent;
	float m_fBlinnExponent;
	float m_fGaussianRoughness;

	float &GetSpecularValue()
	{
		switch(g_eLightModel)
		{
		case LM_GAUSSIAN_SPECULAR:
		case LM_GAUSSIAN_ONLY:
			return m_fGaussianRoughness;
		}

		static float fStopComplaint = 0.0f;
		return fStopComplaint;
	}

	const float &GetSpecularValue() const
	{
		switch(g_eLightModel)
		{
		case LM_GAUSSIAN_SPECULAR:
		case LM_GAUSSIAN_ONLY:
			return m_fGaussianRoughness;
		}

		static float fStopComplaint = 0.0f;
		return fStopComplaint;
	}

	void ClampParam()
	{
		float &theParam = GetSpecularValue();

		if(IsGuassianLightModel())
		{
			//Clamp to (0, 1].
			theParam = std::max(0.00001f, theParam);
			theParam = std::min(1.0f, theParam);
		}
		else
		{
			if(theParam <= 0.0f)
				theParam = 0.0001f;
		}
	}
};

static MaterialParams g_matParams;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pLightMesh && g_pLightMesh)
	{
		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_mousePole.CalcMatrix());

		const glm::vec4 &worldLightPos = CalcLightPosition();
		const glm::vec4 &lightPosCameraSpace = modelMatrix.Top() * worldLightPos;

		ProgramData &whiteProg = g_Programs[g_eLightModel].whiteProg;
		ProgramData &colorProg = g_Programs[g_eLightModel].colorProg;

		glUseProgram(whiteProg.theProgram);
		glUniform4f(whiteProg.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(whiteProg.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(whiteProg.cameraSpaceLightPosUnif,1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(whiteProg.lightAttenuationUnif, g_fLightAttenuation);
		glUniform1f(whiteProg.shininessFactorUnif, g_matParams);
		glUniform4fv(whiteProg.baseDiffuseColorUnif, 1,
			g_bDrawDark ? glm::value_ptr(g_darkColor) : glm::value_ptr(g_lightColor));

		glUseProgram(colorProg.theProgram);
		glUniform4f(colorProg.lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(colorProg.ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(colorProg.cameraSpaceLightPosUnif, 1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(colorProg.lightAttenuationUnif, g_fLightAttenuation);
		glUniform1f(colorProg.shininessFactorUnif, g_matParams);
		glUseProgram(0);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			//Render the ground plane.
			{
				Framework::MatrixStackPusher push(modelMatrix);
				modelMatrix.RotateX(-90);
				modelMatrix.Scale(20.0f, 20.0f, 20.0f);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				glUseProgram(colorProg.theProgram);
				glUniformMatrix4fv(colorProg.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glUniformMatrix3fv(colorProg.normalModelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(normMatrix));
				g_pTerrainMesh->Render("tint");
				glUseProgram(0);
			}

			//Render the light
			if(g_bDrawLightSource)
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.Translate(glm::vec3(worldLightPos));
				modelMatrix.Scale(1.f, 1.f, 1.f);

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));
				glUniform4f(g_Unlit.objectColorUnif, 0.8078f, 0.8706f, 0.9922f, 1.0f);
				g_pLightMesh->Render("flat");
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

	for(int iProg = 0; iProg < LM_MAX_LIGHTING_MODEL; iProg++)
	{
		g_Programs[iProg].whiteProg.SetWindowData(persMatrix.Top());
		g_Programs[iProg].colorProg.SetWindowData(persMatrix.Top());
	}

	g_Unlit.SetWindowData(persMatrix.Top());

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}

static const char *strLightModelNames[] =
{
	"Gaussian Specular.",
	"Gaussian Only",
};


//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	bool bChangedShininess = false;
	bool bChangedLightModel = false;
	switch (key)
	{
	case 27:
		delete g_pTerrainMesh;
		delete g_pLightMesh;
		glutLeaveMainLoop();
		break;
		
	case 32:
		g_bDrawColoredCyl = !g_bDrawColoredCyl;
		break;

	case 'i': g_fLightHeight += 2.f; break;
	case 'k': g_fLightHeight -= 2.f; break;
	case 'l': g_fLightRadius += 2.f; break;
	case 'j': g_fLightRadius -= 2.f; break;
	case 'I': g_fLightHeight += 0.5f; break;
	case 'K': g_fLightHeight -= 0.5f; break;
	case 'L': g_fLightRadius += 0.5f; break;
	case 'J': g_fLightRadius -= 0.5f; break;

	case 'o': g_matParams.Increment(true); bChangedShininess = true; break;
	case 'u': g_matParams.Decrement(true); bChangedShininess = true; break;
	case 'O': g_matParams.Increment(false); bChangedShininess = true; break;
	case 'U': g_matParams.Decrement(false); bChangedShininess = true; break;

	case 'y': g_bDrawLightSource = !g_bDrawLightSource; break;
	case 't': g_bScaleCyl = !g_bScaleCyl; break;
	case 'b': g_bRotateLight = !g_bRotateLight; break;
	case 'g': g_bDrawDark = !g_bDrawDark; break;
	case 'h':
		if(g_eLightModel % 2)
			g_eLightModel -= 1;
		else
			g_eLightModel += 1;
		g_eLightModel %= LM_MAX_LIGHTING_MODEL;
		bChangedLightModel = true;
		break;
	}

	if(g_fLightRadius < 0.2f)
		g_fLightRadius = 0.2f;

	if(bChangedShininess)
		printf("Shiny: %f\n", (float)g_matParams);

	if(bChangedLightModel)
		printf("%s\n", strLightModelNames[g_eLightModel]);

	glutPostRedisplay();
}


