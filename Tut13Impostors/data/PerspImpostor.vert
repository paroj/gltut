#version 330

layout(std140) uniform;

out vec2 mapping;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

uniform float sphereRadius;
uniform vec3 cameraSpherePos;

const float g_boxCorrection = 1.5;

void main()
{
	vec2 offset;
	switch(gl_VertexID)
	{
	case 0:
		//Bottom-left
		mapping = vec2(-1.0, -1.0) * g_boxCorrection;
		offset = vec2(-sphereRadius, -sphereRadius);
		break;
	case 1:
		//Top-left
		mapping = vec2(-1.0, 1.0) * g_boxCorrection;
		offset = vec2(-sphereRadius, sphereRadius);
		break;
	case 2:
		//Bottom-right
		mapping = vec2(1.0, -1.0) * g_boxCorrection;
		offset = vec2(sphereRadius, -sphereRadius);
		break;
	case 3:
		//Top-right
		mapping = vec2(1.0, 1.0) * g_boxCorrection;
		offset = vec2(sphereRadius, sphereRadius);
		break;
	}

	vec4 cameraCornerPos = vec4(cameraSpherePos, 1.0);
	cameraCornerPos.xy += offset * g_boxCorrection;

	gl_Position = cameraToClipMatrix * cameraCornerPos;
}
