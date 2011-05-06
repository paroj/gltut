#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

smooth out vec4 interpColor;

uniform vec3 lightPos;
uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

void main()
{
	vec4 cameraPosition = (modelToCameraMatrix * vec4(position, 1.0));
	gl_Position = cameraToClipMatrix * cameraPosition;

	vec3 normCamSpace = normalize(normalModelToCameraMatrix * normal);
	
	vec3 dirToLight = normalize(lightPos - vec3(cameraPosition));
	
	float cosAngIncidence = dot(normCamSpace, dirToLight);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	interpColor = (lightIntensity * cosAngIncidence) + ambientIntensity;
}
