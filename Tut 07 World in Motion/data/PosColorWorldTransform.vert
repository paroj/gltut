#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 interpColor;

uniform mat4 cameraToClipMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 modelToWorldMatrix;

void main()
{
	vec4 temp = modelToWorldMatrix * position;
	temp = worldToCameraMatrix * temp;
	gl_Position = cameraToClipMatrix * temp;
	interpColor = color;
}
