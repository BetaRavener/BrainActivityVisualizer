#version 330

in vec2 texCoord;

uniform sampler2D namesTextureSampler;

out vec4 color;

void main(){
    color = texture(namesTextureSampler, texCoord);
    //color = vec4(texCoord, 0, 1);
}