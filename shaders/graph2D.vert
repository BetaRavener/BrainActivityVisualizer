#version 330

uniform vec2 zoom;
uniform vec2 bottomLeft;
uniform vec2 size;

in float position;

void main(){
    float x = bottomLeft.x + gl_VertexID * (zoom.x > 0.5f ? zoom.x : 0.5f);
    float y = bottomLeft.y + (size.y / 2.f) + position * zoom.y;
	gl_Position = vec4(x, y, 0.f, 1.f);
}