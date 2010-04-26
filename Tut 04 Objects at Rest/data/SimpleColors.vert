#version 150

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

uniform vec2 offset;

void main()
{
	vec4 tempOffset = vec4(offset.x, offset.y, 0.0, 0.0);

	gl_Position = position + tempOffset;
	theColor = color;
}
