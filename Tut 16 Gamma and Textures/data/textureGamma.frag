#version 330

in vec2 colorCoord;

uniform sampler2D colorTexture;

out vec4 outputColor;

void main()
{
	vec4 gamma = vec4(1.0 / 2.2);
	gamma.w = 1.0;
	outputColor = pow(texture(colorTexture, colorCoord), gamma);
}
