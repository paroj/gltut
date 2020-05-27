#version 330

smooth in vec4 theColor;
uniform vec4 baseColor;

out vec4 outputColor;

void main()
{
	outputColor = theColor * baseColor;
}
