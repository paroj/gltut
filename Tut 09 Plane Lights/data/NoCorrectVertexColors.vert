#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

noperspective out vec4 theColor;

uniform mat4 cameraToClipMatrix;

void main()
{
	gl_Position = cameraToClipMatrix * vec4(position, 1.0);
	theColor = color;
}
