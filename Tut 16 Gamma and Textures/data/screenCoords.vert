#version 330

layout(std140) uniform;

layout(location = 0) in vec2 position;
layout(location = 5) in vec2 texCoord;

layout(std140) uniform Projection
{
	mat4 cameraToClipMatrix;
};

out vec2 colorCoord;

void main()
{
	gl_Position = cameraToClipMatrix * vec4(position, 0.0, 1.0);
	colorCoord = texCoord;
}
