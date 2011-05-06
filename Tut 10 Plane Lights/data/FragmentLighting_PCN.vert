#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inDiffuseColor;
layout(location = 2) in vec3 normal;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 modelSpacePosition;

uniform mat4 modelToCameraMatrix;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));

	modelSpacePosition = position;
	vertexNormal = normal;
	diffuseColor = inDiffuseColor;
}
