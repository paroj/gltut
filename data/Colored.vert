#version 330

layout(std140) uniform;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

smooth out vec4 objectColor;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 modelToCameraMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));
	objectColor = color;
}
