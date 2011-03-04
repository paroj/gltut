#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 modelSpaceNormal;
out vec3 cameraSpacePosition;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;
uniform vec4 baseDiffuseColor;

uniform mat3 normalModelToCameraMatrix;

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vertexNormal = normalModelToCameraMatrix * normal;
	modelSpaceNormal = normalize(normal);
	diffuseColor = baseDiffuseColor;
	cameraSpacePosition = vec3(tempCamPosition);
}
