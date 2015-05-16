// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

in vec3 position;
in vec3 vColor;

out vec3 gColor;

void main(){
	gl_Position = vec4(position,1);
    gColor = vColor;
}