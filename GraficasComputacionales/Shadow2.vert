#version 330

in vec3 vertexPosition;
in vec3 vertexColor;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

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
	InterpolatedColor = vertexColor;
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0f);
	PixelPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0f));
	InterpolatedNormal = normalMatrix * vertexNormal;
	InterpolatedTexCoord = vertexTexCoord;
	PixelPositionLightSpace = LightVPMatrix * vec4(PixelPosition, 1);
}
