#version 330

in vec4 Position;
in vec4 Normal;
in vec4 Tangent;
in vec4 Indices;
in vec4 Weights;
in vec2 Tex1;

out vec4 vNormal;
out vec4 vTangent;
out vec2 vUV;

out vec4 vLightDir;
out vec4 vHalfVec;

uniform vec4 cameraPosition;
uniform vec4 lightDirection;
uniform mat4 ProjectionView; 
uniform mat4 Model;

// we need to give our bone array a limit
const int MAX_BONES = 128;

uniform mat4 Bones[MAX_BONES];

void main() 
{ 
	// cast the indices to integer's so they can index an array
	ivec4 index = ivec4(Indices);

	//Get the bone skeletons data for this frame and multiply by weight to scale
	mat4 bone1 = Bones[index.x] * Weights.x;
	mat4 bone2 = Bones[index.y] * Weights.y;
	mat4 bone3 = Bones[index.z] * Weights.z;
	mat4 bone4 = Bones[index.w] * Weights.w;

	// calculate position of vertex from skeleton frame data
	vec4 P =Position;//vec4(0.f, 0.f, 0.f, 1.f);
	P =  bone1 * Position;
	P += bone2 * Position;
	P += bone3 * Position;
	P += bone4 * Position;

	//Calculate normal from skeleton frame data
	vec4 N = Normal;//vec4(0.f, 0.f, 0.f, 0.f);
	N =  bone1 * Normal;
	N += bone2 * Normal;
	N += bone3 * Normal;
	N += bone4 * Normal;
	N.w = 0.f;
	N = normalize(N);
	N = normalize(Model * N);

	//caclulate Tangent from skeleton frame data
	vec4 T = Tangent;//vec4(0.f, 0.f, 0.f, 0.f);
	T =  bone1 * Tangent;
	T += bone2 * Tangent;
	T += bone3 * Tangent;
	T += bone4 * Tangent;
	T.w = 0.f;
	T = normalize(T);
	T = normalize(Model * T);

	//calculate the bitangent 
	vec4 bitangent = vec4(cross( N.xyz, T.xyz), 0.f);

	//Transform the light direction by teh TBN matrix.
	//This is the equivalent of multiplying our light vector by a Tangent, BiTangent, Normal matrix
	vLightDir.x = dot(-lightDirection, T);
	vLightDir.y = dot(-lightDirection, bitangent);
	vLightDir.z = dot(-lightDirection, N);
	vLightDir.a = 0.f;
	vLightDir = normalize(vLightDir);

	//calculate the half vector for specular highlight values
	//half vector between camera and light vectors
	vec4 viewDir = normalize(cameraPosition - P);
	vec4 halfV = normalize(-lightDirection + viewDir);
	vHalfVec.x = dot(halfV, T);
	vHalfVec.y = dot(halfV, bitangent);
	vHalfVec.z = dot(halfV, N);
		
	//send outputs from vertex shader to fragment shader
	vNormal = N;
	vTangent = T;
	vUV = Tex1;

	gl_Position = ProjectionView * Model * P;

}