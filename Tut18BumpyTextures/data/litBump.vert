#version 330

layout(std140) uniform;

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;
layout(location = 5) in vec2 texCoord;

out vec2 normalCoord;
out vec3 cameraSpacePosition;
out vec3 cameraToTangentX;
out vec3 cameraToTangentY;
out vec3 cameraToTangentZ;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform mat4 modelToCameraMatrix;
uniform mat3 normalCameraToModelMatrix;

void main()
{
	cameraSpacePosition = (modelToCameraMatrix * vec4(position, 1.0)).xyz;
	gl_Position = cameraToClipMatrix * vec4(cameraSpacePosition, 1.0);
	
	mat3 modelToTangent = mat3(tangent, bitangent, normal);
	mat3 cameraToTangent = modelToTangent * normalCameraToModelMatrix;
	
	cameraToTangentX = cameraToTangent[0];
	cameraToTangentY = cameraToTangent[1];
	cameraToTangentZ = cameraToTangent[2];

	normalCoord = texCoord;
}
