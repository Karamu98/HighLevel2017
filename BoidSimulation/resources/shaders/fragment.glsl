#version 330

in vec4 vNormal;
in vec4 vTangent;
in vec4 vLightDir;
in vec4 vHalfVec;
in vec2 vUV;

out vec4 FragColor;




uniform sampler2D DiffuseTexture;
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;

void main()
{
	//sample the texture data fro albedo, normal map, and specular map
	vec4 albedo =  texture2D(DiffuseTexture, vUV);
	vec4 nMap =  texture2D(NormalMap, vUV) * 2.0 - 1.0;
	vec4 specColor = texture2D(SpecularMap, vUV) * 2.f;

	//calculate specular factor

	float specularFactor = pow( max(0.0, dot(vLightDir, vHalfVec)), 6.f);
	//calculate lambertian term
	float lambertFactor  = max( dot(nMap, vLightDir), 0.0 ) ;

	//put components together
	vec4 ambientComponent  = vec4(0.15f, 0.15f, 0.15f, 1.f);
	vec4 diffuseComponent  = albedo *  lambertFactor;
	vec4 specularComponent = specColor * specularFactor;

	//get final colour
	FragColor = ambientComponent + (diffuseComponent + specularComponent);
	FragColor.a = albedo.a;

}
