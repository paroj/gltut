#version 330

in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 modelSpacePosition;

out vec4 outputColor;

uniform vec3 modelSpaceLightPos;

uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;

void main()
{
	vec3 lightDir = normalize(modelSpaceLightPos - modelSpacePosition);

	float cosAngIncidence = dot(normalize(vertexNormal), lightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	outputColor = (diffuseColor * lightIntensity * cosAngIncidence) +
		(diffuseColor * ambientIntensity);
}
