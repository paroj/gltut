#version 330

layout(location = 0) in vec3 cameraSpherePos;
layout(location = 1) in float sphereRadius;

out VertexData
{
	vec3 cameraSpherePos;
	float sphereRadius;
} outData;

void main()
{
	outData.cameraSpherePos = cameraSpherePos;
	outData.sphereRadius = sphereRadius;
}
