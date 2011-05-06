#version 330

layout(location = 0) in vec3 position;

uniform mat4 modelToCameraMatrix;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

void main()
{
	gl_Position = cameraToClipMatrix * (modelToCameraMatrix * vec4(position, 1.0));
}
