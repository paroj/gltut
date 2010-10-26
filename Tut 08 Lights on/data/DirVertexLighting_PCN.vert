#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 diffuseColor;
layout(location = 2) in vec3 normal;

smooth out vec4 interpColor;

uniform vec3 dirToLight;
uniform vec4 lightIntensity;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

uniform mat4 normalModelToCameraMatrix;

void main()
{
	vec4 temp = modelToWorldMatrix * position;
	temp = worldToCameraMatrix * temp;
	gl_Position = cameraToClipMatrix * temp;

	vec4 normCamSpace = normalModelToCameraMatrix * vec4(normal, 0.0);
	
	float cosAngIncidence = dot(normCamSpace, dirToLight);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	interpColor = lightIntensity * diffuseColor * cosAngIncidence;;
}
