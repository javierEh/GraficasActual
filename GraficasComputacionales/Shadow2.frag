#version 330

in vec4 pixelPositionLightSpace;
in vec3 interpolatedColor;
in vec3 interpolatedNormal;
in vec3 pixelPosition;
in vec2 interpolatedTexCoord;

uniform vec3 cameraPosition;
uniform sampler2D diffuseTexture;
uniform sampler2D diffuseTexture2;
uniform sampler2D shadowMap;
uniform vec3 lightColor;
uniform vec3 lightPosition;

out vec4 FragColor;

float IsPixelOccluded(vec4 fragPosLightSpace){
	// Realizar la corrección de perspectiva. Coordenadas en rango [-1, 1] -> Normalized Device Space 
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// Transformar projCoords al rango [0, 1]. 
	(projCoords * 0.5 + 0.5)
	// Muestrear el mapa de profundidad usando projCoords.xy como coordenadas de textura.
	// Con esto obtenemos la profundidad del pixel en el primer render (desde la luz). 
	float closestDepth = texture2D(ShadowMap, projCoords.xy).r;
	// La profundidad del pixel desde la actual cámara (ya transformado) está en projCoords.z 
	float currentDepth =  projCoords.z;
	// Si la profundidad del render actual es mayor a closestDepth, regresar 1.0f 
	// De lo contrario, regresar 0.0f 
	float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;

}

void main()
{
    vec3 ambient = 0.1f * lightColor;
	vec3 L = normalize(lightPosition - pixelPosition);
	vec3 diffuse = max(dot(normslize(interpolatedNormal, L), 0.0f) * lightColor;
	vec3 R = normalize(reflect(-L, normalize(interpolatedNormal)));
	vec3 V = normalize(cameraPosition - pixelPosition);
	vec3 specular = 0.5f * pow(max(dot(V, R), 0.0f), 256) * lightColor;

	vec4 texA = texture2D(diffuseTexture, interpolatedTexCoord);
	vec4 texB = texture2D(diffuseTexture2, interpolatedTexCoord);
	vec4 combine = mix(texA, texB, 0.5f);
	
	float shadow = IsPixelOccluded(pixelPositionLightSpace);
	vec3 phong = (ambient + (1.0 - shadow) * (diffuse + specular)) * combine;
	FragColor = vec4(phong, 1.0f);
}
