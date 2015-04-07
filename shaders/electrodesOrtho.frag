#version 330

uniform float radius;

const float diffuseContr = 0.3f;
const float ambientContr = 0.7f;

in vec3 middle;
in vec3 direction;
in vec3 fColor;
out vec4 color;

const float PI = 3.14159265358979323846264;

float CalcIntensity(){
	float angle = PI / 2.f * (1.f - length(direction));
	vec3 normal = normalize(vec3(0.f, 0.f, sin(angle)) + direction * cos(angle));
	float diffIntensity = max(0.f, dot(normal, vec3(0.f, 0.f, 1.f)));

	return diffuseContr * diffIntensity + ambientContr;
}

void main(){
	color = vec4(fColor * CalcIntensity(), 1.f);
}