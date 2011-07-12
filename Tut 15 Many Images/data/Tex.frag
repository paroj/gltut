#version 330

in vec2 colorCoord;

uniform sampler2D colorTexture;

out vec4 outputColor;

void main()
{
//	outputColor = vec4(colorCoord, 0.0, 1.0);
	outputColor = texture(colorTexture, colorCoord);
}
