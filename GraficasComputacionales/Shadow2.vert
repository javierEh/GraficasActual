#version 330

in vec3 vertexPosition;
in vec3 vertexColor;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

out vec4 PixelPositionLightSpace;
out vec3 interpolatedNormal;
out vec3 interpolatedColor;
out vec3 pixelPosition;
out vec2 interpolatedTexCoord;

uniform mat4 LightVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
	interpolatedColor = vertexColor;
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0f);
	pixelPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0f));
	interpolatedNormal = normalMatrix * vertexNormal;
	interpolatedTexCoord = vertexTexCoord;
	PixelPositionLightSpace = LightVPMatrix * vec4(pixelPosition, 1.0f);
}
