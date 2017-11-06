#version 330

in vec3 InterpolatedColor;
in vec3 InterpolatedNormal;
in vec3 pixelPosition;
in vec2 InterpolatedTexCoord;

uniform vec3 CameraPosition;
uniform sampler2D DiffuseTexture;
uniform sampler2D DiffuseTexture2;
uniform vec3 LightColor;
uniform vec3 LightPosition;


out vec4 FragColor;

void main()
{
    vec3 ambient = 0.1f * LightColor;
	vec3 V = normalize(CameraPosition-pixelPosition);
	vec3 Luz = normalize(LightPosition - pixelPosition);
	vec3 Re = normalize(reflect(-Luz,normalize(InterpolatedNormal)));
	

	vec3 diffuse = max(dot(normalize(InterpolatedNormal), Luz),0.0f) * LightColor;
	vec3 specular = 0.5f * pow(max(dot(V, Re),0.0f),256) * LightColor;
	
	vec4 texA = texture2D(DiffuseTexture, InterpolatedTexCoord);
	vec4 texB = texture2D(DiffuseTexture2, InterpolatedTexCoord);
	vec4 mixOne = mix(texA, texB, 0.5f);
	
	vec3 phong = (ambient+diffuse+specular) *  mixOne;
	FragColor = vec4(phong, 1.0f);
}