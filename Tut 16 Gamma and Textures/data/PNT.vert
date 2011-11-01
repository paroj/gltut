#version 330

layout(std140) uniform;

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 5) in vec2 texCoord;

out vec2 colorCoord;
out vec3 cameraSpacePosition;
out vec3 cameraSpaceNormal;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 modelToCameraMatrix;

void main()
{
	cameraSpacePosition = (modelToCameraMatrix * vec4(position, 1.0)).xyz;
	gl_Position = cameraToClipMatrix * vec4(cameraSpacePosition, 1.0);
	//Assume the modelToCameraMatrix contains no scaling.
	cameraSpaceNormal = (modelToCameraMatrix * vec4(normal, 0)).xyz;
	colorCoord = texCoord;
}
