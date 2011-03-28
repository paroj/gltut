#version 330

in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 cameraSpacePosition;

out vec4 outputColor;

layout(std140) uniform;

uniform Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float specularShininess;
} Mtl;

struct PerLight
{
	vec3 cameraSpaceLightPos;
	vec4 lightIntensity;
};

uniform Light
{
	vec4 ambientIntensity;
	float lightAttenuation;
	PerLight lights;
} Lgt;


float CalcAttenuation(in vec3 cameraSpacePosition,
	in vec3 cameraSpaceLightPos,
	out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + Lgt.lightAttenuation * sqrt(lightDistanceSqr)));
}

void main()
{
	vec3 lightDir = vec3(0.0);
	float atten = CalcAttenuation(cameraSpacePosition,
		Lgt.lights.cameraSpaceLightPos, lightDir);
	vec4 attenIntensity = atten * Lgt.lights.lightIntensity;
	
	vec3 surfaceNormal = normalize(vertexNormal);
	float cosAngIncidence = dot(surfaceNormal, lightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	outputColor = (diffuseColor * attenIntensity * cosAngIncidence) +
		(diffuseColor * Lgt.ambientIntensity);
}
