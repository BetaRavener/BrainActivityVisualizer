#version 330

layout(points) in;
layout(triangle_strip, max_vertices=6) out;

#define size 1.5f

in vec2 gBottomLeftUV[];
in vec2 gTopRightUV[];

uniform vec3 eyePos;
uniform vec3 upDir;
uniform vec3 rightDir;
uniform mat4 mvpMatrix;
uniform float textureAspect;

out vec2 texCoord;

void main(){
	vec3 middle = gl_in[0].gl_Position.xyz;
    vec3 middleEyeVec = normalize(eyePos - middle);
    
    // Offset labels so they are closer to camera, therefore visible in front
    // of electrodes
    middle += middleEyeVec * 2;
    
    vec2 aspectVec = gTopRightUV[0] - gBottomLeftUV[0];
    float aspect = textureAspect * abs(aspectVec.x) / abs(aspectVec.y); 
    
    vec3 topLeft = size * upDir - aspect * size * rightDir + middle;
    vec3 topRight = size * upDir + aspect * size * rightDir + middle;
	vec3 bottomLeft = -size * upDir - aspect * size * rightDir + middle;
    vec3 bottomRight = -size * upDir + aspect * size * rightDir + middle;
    
    gl_Position = mvpMatrix*vec4(topRight, 1.f);
    texCoord = gTopRightUV[0];
    EmitVertex();
    gl_Position = mvpMatrix*vec4(topLeft, 1.f);
    texCoord = vec2(gBottomLeftUV[0].x, gTopRightUV[0].y);
    EmitVertex();
    gl_Position = mvpMatrix*vec4(bottomLeft, 1.f);
    texCoord = gBottomLeftUV[0];
	EmitVertex();
	EndPrimitive();
    gl_Position = mvpMatrix*vec4(bottomLeft, 1.f);
    texCoord = gBottomLeftUV[0];
    EmitVertex();
    gl_Position = mvpMatrix*vec4(bottomRight, 1.f);
    texCoord = vec2(gTopRightUV[0].x, gBottomLeftUV[0].y);
	EmitVertex();
    gl_Position = mvpMatrix*vec4(topRight, 1.f);
    texCoord = gTopRightUV[0];
    EmitVertex();
	EndPrimitive();
}