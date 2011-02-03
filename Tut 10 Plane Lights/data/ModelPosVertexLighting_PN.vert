#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

out vec4 interpColor;

uniform vec3 modelSpaceLightPos;
uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));

	vec3 dirToLight = normalize(modelSpaceLightPos - position);
	
	float cosAngIncidence = dot(normal, dirToLight);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	interpColor = (lightIntensity * cosAngIncidence) + ambientIntensity;
}
