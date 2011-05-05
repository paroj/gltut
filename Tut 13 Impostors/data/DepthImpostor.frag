#version 330

in vec2 mapping;

out vec4 outputColor;

uniform float sphereRadius;
uniform vec3 cameraSpherePos;

layout(std140) uniform;

uniform Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float specularShininess;
} Mtl;

struct PerLight
{
	vec4 cameraSpaceLightPos;
	vec4 lightIntensity;
};

const int numberOfLights = 2;

uniform Light
{
	vec4 ambientIntensity;
	float lightAttenuation;
	PerLight lights[numberOfLights];
} Lgt;


float CalcAttenuation(in vec3 cameraSpacePosition,
	in vec3 cameraSpaceLightPos,
	out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + Lgt.lightAttenuation * lightDistanceSqr));
}

uniform Projection
{
	mat4 cameraToClipMatrix;
};

vec4 ComputeLighting(in PerLight lightData, in vec3 cameraSpacePosition,
	in vec3 cameraSpaceNormal)
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
	
	vec3 viewDirection = normalize(-cameraSpacePosition);
	
	vec3 halfAngle = normalize(lightDir + viewDirection);
	float angleNormalHalf = acos(dot(halfAngle, surfaceNormal));
	float exponent = angleNormalHalf / Mtl.specularShininess;
	exponent = -(exponent * exponent);
	float gaussianTerm = exp(exponent);

	gaussianTerm = cosAngIncidence != 0.0 ? gaussianTerm : 0.0;
	
	vec4 lighting = Mtl.diffuseColor * lightIntensity * cosAngIncidence;
	lighting += Mtl.specularColor * lightIntensity * gaussianTerm;
	
	return lighting;
}

void Impostor(out vec3 cameraPos, out vec3 cameraNormal)
{
	vec3 cameraPlanePos = vec3(mapping * sphereRadius, 0.0) + cameraSpherePos;
	vec3 rayDirection = normalize(cameraPlanePos);
	
	float B = 2.0 * dot(rayDirection, -cameraSpherePos);
	float C = dot(cameraSpherePos, cameraSpherePos) - (sphereRadius * sphereRadius);
	
	float det = (B * B) - (4 * C);
	if(det < 0.0)
		discard;
		
	float sqrtDet = sqrt(det);
	float posT = (-B + sqrtDet)/2;
	float negT = (-B - sqrtDet)/2;
	
	float intersectT = min(posT, negT);
	cameraPos = rayDirection * intersectT;
	cameraNormal = normalize(cameraPos - cameraSpherePos);
}

void main()
{
	vec3 cameraPos;
	vec3 cameraNormal;
	
	Impostor(cameraPos, cameraNormal);
	
	//Set the depth based on the new cameraPos.
	vec4 clipPos = cameraToClipMatrix * vec4(cameraPos, 1.0);
	float ndcDepth = clipPos.z / clipPos.w;
	gl_FragDepth = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
	
	vec4 accumLighting = Mtl.diffuseColor * Lgt.ambientIntensity;
	for(int light = 0; light < numberOfLights; light++)
	{
		accumLighting += ComputeLighting(Lgt.lights[light],
			cameraPos, cameraNormal);
	}
	
	outputColor = sqrt(accumLighting); //2.0 gamma correction
}
