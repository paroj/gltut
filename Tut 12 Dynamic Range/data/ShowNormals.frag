#version 330

in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 modelSpaceNormal;
in vec3 cameraSpacePosition;

out vec4 outputColor;

uniform vec3 modelSpaceLightPos;

uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;

uniform vec3 cameraSpaceLightPos;

uniform float lightAttenuation;

const vec4 specularColor = vec4(0.25, 0.25, 0.25, 1.0);
uniform float shininessFactor;


void main()
{
	outputColor = vec4(normalize(modelSpaceNormal), 1.0);
}
