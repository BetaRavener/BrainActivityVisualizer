#version 330

#define maxOut 93
#define minOut 6

layout(points) in;
layout(triangle_strip, max_vertices=93) out;

uniform vec3 eyePos;
uniform float radius;
uniform mat4 mvpMatrix;

out vec3 middle;
out vec3 direction;

const float PI = 3.14159265358979323846264;
const float sqrDeg = 0.2; //def: 0.1
const float linDeg = 0.1; //def: 0.5
const float divFac = 0.03; // def: 0.02

mat2 createRotMatrix(float angle){
	float cosA = cos(angle);
	float sinA = sin(angle);
	return mat2(
		cosA, -sinA,
        sinA,  cosA
	);
}

void main(){
	int vertexCount = maxOut/3;
	middle = gl_in[0].gl_Position.xyz;
	
	//degradate ball quality as it is further from viewer
	vertexCount = 93;

	vec2 firstDir, tempDir;
	vec4 midPoint, tempPos;
	if(vertexCount > maxOut/3)
		vertexCount = maxOut/3;
	else if(vertexCount < minOut)
		vertexCount = minOut;
	mat2 anglIncrMatrix = createRotMatrix(2.f*PI/vertexCount);
	
	//form circle facing the camera
	midPoint = mvpMatrix*gl_in[0].gl_Position;
	tempDir = firstDir = vec2(1.f, 0.f);
    
	tempPos = mvpMatrix*(gl_in[0].gl_Position+vec4(tempDir, 0.f, 0.f)*radius);
	
	for(int i = 0; i < vertexCount-1; i++){
		gl_Position = midPoint;
		direction = vec3(0.f,0.f,0.f);
		EmitVertex();
		
		gl_Position = tempPos;
		direction = vec3(tempDir, 0.f);
		EmitVertex();
		
		tempDir = anglIncrMatrix*tempDir;
		gl_Position = tempPos = mvpMatrix*(gl_in[0].gl_Position+vec4(tempDir, 0.f, 0.f)*radius);
		direction = vec3(tempDir, 0.f);
		EmitVertex();
		EndPrimitive();
	}
	//render last triangle (endVertex = startVertex)
	gl_Position = midPoint;
	direction = vec3(0.f,0.f,0.f);
	EmitVertex();
	
	gl_Position = tempPos;
	direction = vec3(tempDir, 0.f);
	EmitVertex();
	
	gl_Position = mvpMatrix*(gl_in[0].gl_Position+vec4(firstDir, 0.f, 0.f)*radius);
	direction = vec3(firstDir, 0.f);
	EmitVertex();
	EndPrimitive();
}