// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

uniform vec2 zoom;
uniform float sampleSpacing;
uniform vec2 bottomLeft;
uniform vec2 size;

in float position;

void main(){
    float x = bottomLeft.x + gl_VertexID * sampleSpacing;
    float y = bottomLeft.y + (size.y / 2.f) + position * zoom.y;
	gl_Position = vec4(x, y, 0.f, 1.f);
}