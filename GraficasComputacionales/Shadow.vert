#version 330

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec4 PixelPositionLightSpace;
out vec3 InterpolatedNormal;
out vec3 InterpolatedColor;
out vec3 PixelPosition;
out vec2 InterpolatedTexCoord;

uniform mat4 LightVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
	InterpolatedColor = VertexColor;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
	PixelPosition = vec3(modelMatrix * vec4(VertexPosition, 1.0f));
	InterpolatedNormal = normalMatrix * VertexNormal;
	InterpolatedTexCoord = VertexTexCoord;
	PixelPositionLightSpace = LightVPMatrix * vec4(PixelPosition, 1.0f);
}