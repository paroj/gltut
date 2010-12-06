#version 330

in vec4 diffuseColor;
in vec3 vertexNormal;

out vec4 outputColor;

uniform vec3 modelSpaceLightPos;

uniform vec4 lightIntensity;
const vec4 phongIntensity = vec4(0.25, 0.25, 0.25, 1.0);
uniform vec4 ambientIntensity;

uniform vec3 cameraSpaceLightPos;

uniform mat4 clipToCameraMatrix;
uniform ivec2 windowSize;
uniform vec2 depthRange;

uniform float lightAttenuation;

const vec4 specularColor = vec4(1.0);
uniform float shininessFactor;


vec3 CalcCameraSpacePosition()
{
	vec3 ndcPos;
	ndcPos.xy = ((gl_FragCoord.xy / windowSize.xy) * 2.0) - 1.0;
	ndcPos.z = 2.0 * (gl_FragCoord.z - depthRange.x - depthRange.y) / (depthRange.y - depthRange.x);
	
	vec4 clipPos;
	clipPos.w = 1.0f / gl_FragCoord.w;
	clipPos.xyz = ndcPos.xyz * clipPos.w;
	
	return vec3(clipToCameraMatrix * clipPos);
}

float CalcAttenuation(in vec3 cameraSpacePosition, out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + lightAttenuation * sqrt(lightDistanceSqr)));
}

void main()
{
	vec3 cameraSpacePosition = CalcCameraSpacePosition();

	vec3 lightDir = vec3(0.0);
	float atten = CalcAttenuation(cameraSpacePosition, lightDir);
	vec4 attenIntensity = atten * lightIntensity;
	
	vec3 surfaceNormal = normalize(vertexNormal);
	float cosAngIncidence = dot(surfaceNormal, lightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	vec4 phongAttenIntensity = atten * phongIntensity;
	vec3 viewDirection = normalize(-cameraSpacePosition);
	vec3 reflectDir = reflect(-lightDir, surfaceNormal);
	float phongTerm = dot(viewDirection, reflectDir);
	phongTerm = clamp(phongTerm, 0, 1);
	phongTerm = dot(reflectDir, surfaceNormal) > 0.0 ? phongTerm : 0.0;
	phongTerm = pow(phongTerm, shininessFactor);
	

	outputColor = (diffuseColor * attenIntensity * cosAngIncidence) +
		(specularColor * phongAttenIntensity * phongTerm) +
		(diffuseColor * ambientIntensity);
}
