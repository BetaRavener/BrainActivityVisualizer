#version 330

uniform vec3 shapeColor;

out vec4 color;

void main(){
    color = vec4(shapeColor, 1.f);
}