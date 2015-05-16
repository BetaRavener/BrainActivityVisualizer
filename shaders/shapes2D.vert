// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

in vec2 position;
in vec3 vColor;

uniform mat4 mvpMatrix;

out vec3 fColor;

void main(){
	gl_Position = mvpMatrix * vec4(position, 0.f, 1.f);
    fColor = vColor;
}