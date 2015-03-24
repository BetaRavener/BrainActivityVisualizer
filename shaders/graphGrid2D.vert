#version 330

in vec2 position;
uniform mat4 mvpMatrix;

void main(){
	gl_Position = mvpMatrix * vec4(position, 0.f, 1.f);
}