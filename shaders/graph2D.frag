// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

uniform vec3 lineColor;
uniform vec2 bottomLeft;
uniform vec2 size;

out vec4 color;

void main(){
    vec2 topRight = bottomLeft + size;

    if (gl_FragCoord.x > bottomLeft.x &&
        gl_FragCoord.y > bottomLeft.y &&
        gl_FragCoord.x < topRight.x &&
        gl_FragCoord.y < topRight.y)
    {
        color = vec4(lineColor, 1.f);
    }
    else
    {
        // Discard this pixel
       discard;
    }
}