#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inDiffuseColor;
layout(location = 2) in vec3 normal;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 modelSpaceNormal;
out vec3 cameraSpacePosition;

smooth out vec4 passthrough;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

uniform mat3 normalModelToCameraMatrix;

uniform vec3 cameraSpaceLightPos;

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vec3 cameraNormal = normalize(normalModelToCameraMatrix * normal);
	vertexNormal = cameraNormal;
	modelSpaceNormal = normalize(normal);
	diffuseColor = inDiffuseColor;
	cameraSpacePosition = tempCamPosition.xyz;
	
	vec3 lightDir = normalize(cameraSpaceLightPos - tempCamPosition.xyz);
	vec3 surfaceNormal = normalize(cameraNormal);
	passthrough = vec4(dot(surfaceNormal, lightDir));

}
