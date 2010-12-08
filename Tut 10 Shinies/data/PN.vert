#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

out vec4 diffuseColor;
out vec3 vertexNormal;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;
uniform vec4 baseDiffuseColor;

uniform mat3 normalModelToCameraMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));

	vertexNormal = normalModelToCameraMatrix * normal;
	diffuseColor = baseDiffuseColor;
}
