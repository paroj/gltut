#version 330

layout(std140) uniform;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inDiffuseColor;
layout(location = 2) in vec3 normal;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 cameraSpacePosition;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vertexNormal = normalize(normalModelToCameraMatrix * normal);
	diffuseColor = inDiffuseColor;
	cameraSpacePosition = vec3(tempCamPosition);
}
