#version 330

noperspective in vec4 theColor;

out vec4 outputColor;

void main()
{
	outputColor = theColor;
}
