#version 400 core

in vec4 Color;
in vec2 Tex;
in vec3 Normal;
in vec3 Position;

out vec4 fColor;

struct LightProperties{
	bool enabled;
	bool local;

	bool spot;
	vec3 ambient;
	vec3 color;
	vec3 position;

	vec3 halfVector;
	vec3 coneDirection;

	float spotCosCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct Material {
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 mMatrix;

uniform sampler2DArray textureData;
uniform int textureID;

uniform vec3 EyeDirection;
const float Strength = 1.0;

const int MaxLights = 1;
const int MaxMats = 1;
const int MaterialIndex = 0;
uniform LightProperties Lights[MaxLights];
uniform Material materials[MaxMats];

void main()
{

	vec3 scatteredLight = vec3(0.0);
	vec3 reflectedLight = vec3(0.0);
	for (int light = 0; light < MaxLights; ++light){
		if(!Lights[light].enabled){
			continue;
		}
		vec3 halfVector;
		vec3 lightDirection = Lights[light].position;
		float attenuation = 1.0;
		if(Lights[light].local){
			mat3 NormMat = mat3(transpose(inverse(mMatrix)));
			lightDirection = lightDirection - vec3(Position);
			float lightDistance = length(lightDirection);
			lightDirection = lightDirection/lightDistance;
			attenuation = 1.0 / (Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * lightDistance * lightDistance);
			
			if(Lights[light].spot){
				float spotCos = dot(lightDirection, -1 * Lights[light].coneDirection);
				if (spotCos < Lights[light].spotCosCutoff){
					attenuation = 0.0;
				}
				else{
					attenuation *= pow(spotCos, Lights[light].spotExponent);
				}
			}
			halfVector = normalize(lightDirection + EyeDirection);
		}
		else{
			halfVector = Lights[light].halfVector;
		}
		float diffuse = max(0.0, dot(Normal, lightDirection));
		float specular = max(0.0, dot(Normal, halfVector));

		if(diffuse == 0.0){
			specular = 0.0;
		}
		else{
			specular = pow(specular, materials[MaterialIndex].shininess) * Strength;
		}
		scatteredLight += Lights[light].ambient * attenuation + Lights[light].color * diffuse * attenuation;
		reflectedLight += Lights[light].color * specular * attenuation;
	}

	vec4 tcolor = vec4(texture(textureData, vec3(Tex.x, Tex.y, textureID)));
	//vec3 rgb = min(tcolor.rgb * scatteredLight, vec3(1.0));
	vec3 rgb = min(tcolor.rgb * scatteredLight + reflectedLight, vec3(1.0));
	//fColor = min(tcolor * vec4(Lights[0].ambient, 1.0), vec4(1.0));
	fColor = vec4(rgb, tcolor.a);
}
