#version 330

in vec2 colorCoord;

uniform sampler2D colorTexture;

out vec4 outputColor;

void main()
{
	outputColor = texture(colorTexture, colorCoord);
}
