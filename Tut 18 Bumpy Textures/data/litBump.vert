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
uniform mat3 normalModelToCameraMatrix;

void main()
{
	cameraSpacePosition = (modelToCameraMatrix * vec4(position, 1.0)).xyz;
	gl_Position = cameraToClipMatrix * vec4(cameraSpacePosition, 1.0);
	cameraSpaceNormal = normalize(normalModelToCameraMatrix * normal);

	colorCoord = texCoord;
}
