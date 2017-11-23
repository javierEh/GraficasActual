#version 330

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;

out vec3 InterpolatedColor;
out vec3 IterpolatedVertexNormal;
out vec3 PixelPosition;

uniform mat4 mvplMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
	InterpolatedColor = VertexColor;
	PixelPosition = vec3(modelMatrix*vec4(VertexPosition, 1.0f));
	IterpolatedVertexNormal = normalMatrix * VertexNormal;
	gl_Position = mvplMatrix * vec4(VertexPosition, 1.0f);
}