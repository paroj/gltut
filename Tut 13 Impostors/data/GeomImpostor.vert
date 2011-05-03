#version 330

layout(std140) uniform;

layout(location = 0) in vec3 cameraSpherePos;
layout(location = 1) in float sphereRadius;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

void main()
{
	gl_Position = vec4(cameraSpherePos, 1.0);
	gl_PointSize = sphereRadius;
}
