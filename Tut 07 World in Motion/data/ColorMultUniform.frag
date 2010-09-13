#version 330

smooth in vec4 interpColor;
uniform vec4 baseColor;

out vec4 outputColor;

void main()
{
	outputColor = interpColor * baseColor;
}
