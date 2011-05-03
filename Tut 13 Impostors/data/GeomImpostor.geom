#version 330

layout(std140) uniform;
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform Projection
{
	mat4 cameraToClipMatrix;
};

out FragData
{
	flat vec3 cameraSpherePos;
	flat float sphereRadius;
	smooth vec2 mapping;
};

const float g_boxCorrection = 1.5;

void main()
{
	vec4 cameraCornerPos;
	//Bottom-left
	mapping = vec2(-1.0, -1.0) * g_boxCorrection;
	cameraSpherePos = vec3(gl_in[0].gl_Position);
	sphereRadius = gl_in[0].gl_PointSize;
	cameraCornerPos = gl_in[0].gl_Position;
	cameraCornerPos.xy += vec2(-gl_in[0].gl_PointSize, -gl_in[0].gl_PointSize) * g_boxCorrection;
	gl_Position = cameraToClipMatrix * cameraCornerPos;
	gl_PrimitiveID = gl_PrimitiveIDIn;
	EmitVertex();
	
	//Top-left
	mapping = vec2(-1.0, 1.0) * g_boxCorrection;
	cameraSpherePos = vec3(gl_in[0].gl_Position);
	sphereRadius = gl_in[0].gl_PointSize;
	cameraCornerPos = gl_in[0].gl_Position;
	cameraCornerPos.xy += vec2(-gl_in[0].gl_PointSize, gl_in[0].gl_PointSize) * g_boxCorrection;
	gl_Position = cameraToClipMatrix * cameraCornerPos;
	gl_PrimitiveID = gl_PrimitiveIDIn;
	EmitVertex();
	
	//Bottom-right
	mapping = vec2(1.0, -1.0) * g_boxCorrection;
	cameraSpherePos = vec3(gl_in[0].gl_Position);
	sphereRadius = gl_in[0].gl_PointSize;
	cameraCornerPos = gl_in[0].gl_Position;
	cameraCornerPos.xy += vec2(gl_in[0].gl_PointSize, -gl_in[0].gl_PointSize) * g_boxCorrection;
	gl_Position = cameraToClipMatrix * cameraCornerPos;
	gl_PrimitiveID = gl_PrimitiveIDIn;
	EmitVertex();
	
	//Top-right
	mapping = vec2(1.0, 1.0) * g_boxCorrection;
	cameraSpherePos = vec3(gl_in[0].gl_Position);
	sphereRadius = gl_in[0].gl_PointSize;
	cameraCornerPos = gl_in[0].gl_Position;
	cameraCornerPos.xy += vec2(gl_in[0].gl_PointSize, gl_in[0].gl_PointSize) * g_boxCorrection;
	gl_Position = cameraToClipMatrix * cameraCornerPos;
	gl_PrimitiveID = gl_PrimitiveIDIn;
	EmitVertex();
}
