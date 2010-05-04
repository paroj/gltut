#version 150

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

uniform vec2 offset;

void main()
{
	gl_Position = position + vec4(offset.x, offset.y, 0.0, 0.0);
	theColor = color;
}
