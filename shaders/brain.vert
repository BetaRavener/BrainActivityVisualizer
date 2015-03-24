#version 330
in vec3 posAttr;
in vec3 normalAttr;
out vec3 vertPos;
out vec3 vertNormal;

uniform mat4 matrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

void main()
{
    vec4 vertPos4 = modelViewMatrix * vec4(posAttr, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
    vertNormal = normalize(vec3(normalMatrix * vec4(normalAttr, 0.0)));
    gl_Position = matrix * vec4(posAttr, 1.0);
}