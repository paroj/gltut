#version 330

in vec4 diffuseColor;
in vec3 vertexNormal;

out vec4 outputColor;

uniform vec3 modelSpaceLightPos;

uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;

uniform vec3 cameraSpaceLightPos;

uniform mat4 clipToCameraMatrix;
uniform ivec2 windowSize;
uniform vec2 depthRange;

uniform float lightAttenuation;
uniform bool bUseRSquare;

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

vec4 CalcLightIntensity(in vec3 cameraSpacePosition)
{
	float lightDistance = length(cameraSpaceLightPos - cameraSpacePosition);
	
	float distFactor = bUseRSquare ? lightDistance * lightDistance : lightDistance;

	return lightIntensity * (1 / ( 1.0 + lightAttenuation * distFactor));
}

void main()
{
	vec3 cameraSpacePosition = CalcCameraSpacePosition();
	vec3 lightDir = normalize(cameraSpaceLightPos - cameraSpacePosition);

	float cosAngIncidence = dot(normalize(vertexNormal),
		normalize(lightDir));
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	outputColor = (diffuseColor * CalcLightIntensity(cameraSpacePosition) * cosAngIncidence) +
		(diffuseColor * ambientIntensity);
}
