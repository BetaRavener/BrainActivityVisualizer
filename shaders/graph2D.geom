// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#version 330

layout(lines_adjacency) in;
layout(triangle_strip, max_vertices=7) out;

uniform float width;
uniform mat4 mvpMatrix;

void main(){
    vec2 prev = gl_in[0].gl_Position.xy;
    vec2 begin = gl_in[1].gl_Position.xy;
    vec2 end = gl_in[2].gl_Position.xy;
    
    vec2 prevDir = begin - prev;
    vec2 dir = end - begin;
    
    float prevDirLength = length(prevDir);
    float dirLength = length(dir);
    
    prevDir /= prevDirLength;
    dir /= dirLength;
    
    vec2 prevNorm = vec2(prevDir.y, -prevDir.x); 
    vec2 norm = vec2(dir.y, -dir.x); 
    
    if (dot(dir, prevNorm) > 0.f)
        prevNorm *= -1.f;
        
    if (dot(prevDir, norm) < 0.f)
        norm *= -1.f;

    norm *= (width / 2.f);
    prevNorm *= (width / 2.f);
    
    // Render line
	gl_Position = mvpMatrix * vec4(begin + norm, 0.f, 1.f);
	EmitVertex();
	
	gl_Position = mvpMatrix * vec4(begin - norm, 0.f, 1.f);
	EmitVertex();
	
	gl_Position = mvpMatrix * vec4(end + norm, 0.f, 1.f);
	EmitVertex();
    
    gl_Position = mvpMatrix * vec4(end - norm, 0.f, 1.f);
    EmitVertex();
	EndPrimitive();
    
    // Render line join
    gl_Position = mvpMatrix * vec4(begin, 0.f, 1.f);
	//EmitVertex();
    
	gl_Position = mvpMatrix * vec4(begin + prevNorm, 0.f, 1.f);
	//EmitVertex();
	
	gl_Position = mvpMatrix * vec4(begin + norm, 0.f, 1.f);
	//EmitVertex();
    
	//EndPrimitive();
}