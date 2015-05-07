#version 330

in vec3 position;
in vec2 bottomLeftUV;
in vec2 topRightUV;

uniform mat4 mvpMatrix;

out vec2 gBottomLeftUV;
out vec2 gTopRightUV;

void main(){
	gl_Position = vec4(position,1);
    gBottomLeftUV = bottomLeftUV;
    gTopRightUV = topRightUV;
}