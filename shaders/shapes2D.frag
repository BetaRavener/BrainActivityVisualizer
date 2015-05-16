// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

in vec3 fColor;

out vec4 color;

void main(){
    color = vec4(fColor, 1.f);
}