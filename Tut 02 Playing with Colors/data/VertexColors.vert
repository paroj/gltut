#version 150

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

void main()
{
	gl_Position = position;
	theColor = color;
}
