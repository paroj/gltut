#version 150

out vec4 outputColor;

uniform vec2 wndDimensions;

const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);

void main()
{
	float lerpValue = gl_FragCoord.y / wndDimensions.y;
		
	outputColor = mix(firstColor, secondColor, lerpValue);
}
