#version 330
in vec3 vertPos;
in vec3 vertNormal;

uniform vec3 eyePos;
uniform vec3 lookAt;
uniform vec3 brainColor;

out vec4 color;

const float ambientIntensity = 0.2;
const float diffuseIntenstiy = 0.6;

void main() {
  vec3 normal = vertNormal;
  vec3 lightDir = normalize(eyePos - vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);

  float intensity = min(ambientIntensity + 
                        lambertian * diffuseIntenstiy, 
                        1.0);               
  
  color = vec4(brainColor * intensity, 1.0);
}