#version 150

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

void main()
{
	vec4 cameraPos = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraPos;
	theColor = color;
}
