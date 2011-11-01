#version 330

in vec2 colorCoord;
in vec3 cameraSpacePosition;
in vec3 cameraSpaceNormal;

out vec4 outputColor;

layout(std140) uniform;

struct PerLight
{
	vec4 cameraSpaceLightPos;
	vec4 lightIntensity;
};

uniform Light
{
	vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	PerLight lights[4];
} Lgt;

uniform int numberOfLights;

float CalcAttenuation(in vec3 cameraSpacePosition,
	in vec3 cameraSpaceLightPos,
	out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + Lgt.lightAttenuation * lightDistanceSqr));
}

vec4 ComputeLighting(in vec4 diffuseColor, in PerLight lightData)
{
	vec3 lightDir;
	vec4 lightIntensity;
	if(lightData.cameraSpaceLightPos.w == 0.0)
	{
		lightDir = vec3(lightData.cameraSpaceLightPos);
		lightIntensity = lightData.lightIntensity;
	}
	else
	{
		float atten = CalcAttenuation(cameraSpacePosition,
			lightData.cameraSpaceLightPos.xyz, lightDir);
		lightIntensity = atten * lightData.lightIntensity;
	}
	
	vec3 surfaceNormal = normalize(cameraSpaceNormal);
	float cosAngIncidence = dot(surfaceNormal, lightDir);
	cosAngIncidence = cosAngIncidence < 0.0001 ? 0.0 : cosAngIncidence;
	
	vec4 lighting = diffuseColor * lightIntensity * cosAngIncidence;
	
	return lighting;
}

uniform sampler2D diffuseColorTex;

void main()
{
	vec4 diffuseColor = texture(diffuseColorTex, colorCoord);
	
	vec4 accumLighting = diffuseColor * Lgt.ambientIntensity;
	for(int light = 0; light < numberOfLights; light++)
	{
		accumLighting += ComputeLighting(diffuseColor, Lgt.lights[light]);
	}
	
	outputColor = accumLighting / Lgt.maxIntensity;

//	outputColor = diffuseColor;
}
