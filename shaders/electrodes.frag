#version 330

uniform vec3 eyePos;
uniform float radius;

const vec3 lightPos = vec3(300,120,300);
const float diffuseContr = 0.6f;
const float specularContr = 0.2f;
const float ambientContr = 0.4f;

in vec3 middle;
in vec3 direction;
in vec3 fColor;
out vec4 color;

const float PI = 3.14159265358979323846264;

float CalcIntensity(){
	float angle = PI/2.f*(1.f-length(direction));
	vec3 normal = normalize(normalize(eyePos-middle)*sin(angle)+direction*cos(angle));
	vec3 position = middle+normal*radius;
	vec3 iLightVec = eyePos - position;
	float distance = length(iLightVec);
	iLightVec = normalize(iLightVec);
	vec3 halfVector = normalize(iLightVec + eyePos);
	float diffIntensity = max(0.f, dot(normal, iLightVec));
	float specIntensity = 0.f;
	if(diffIntensity != 0){
		specIntensity = pow(max(0.f, dot(normal, halfVector)), 4.0f);
	}
	return diffuseContr*diffIntensity + specularContr*specIntensity + ambientContr;
}

void main(){
	color = vec4(fColor * CalcIntensity(), 1.f);
}