#include "common.fx"

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : TEXCOORD0;
	float2 tex : TEXCOORD1;
};

struct PixelInputTypeCustom
{
    float4 position : SV_POSITION;
	float4 color : TEXCOORD0;
	float textureMappingData : TEXCOORD1;
	float2 tex : TEXCOORD2;
};

Texture2D shaderTexture : register( t0 );

PixelInputTypeCustom VShader(VertexInputType input)
{
    PixelInputTypeCustom output;
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x;

    // Change the position vector to be 4 units for proper matrix calculations.
	
    input.position.w = 1.0f;	
	
	input.position.xy *= myRotationAndSizeCustom.yz;
		
	float2x2 theRotation = ComputeRotation(myRotationAndSizeCustom.x);
	input.position.xy = mul(input.position.xy, theRotation);
	
	input.position.xy += myPositionCustom;
	
	
    // Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = input.position;
	
	output.tex = input.tex;
    
	output.color = input.color;
	output.textureMappingData = myRotationAndSizeCustom.w;
	
    return output;
}

#ifdef USE_LIGHTS
float4 CalculateLight(PixelInputTypeCustom input)
{
	float4 DiffuseColor = input.color;
	float4 AmbientColor = float4(0.5f, 0.5f, 0.5f, 0.1f);
	float4 AmbientLight = AmbientColor * DiffuseColor;
	
	float2 Resolution = myResolution.xy;
	
	
	float4 finalColor = DiffuseColor + myAmbience;
	finalColor.a = DiffuseColor.a;
	
	
	for(uint i=0; i< myNumberOfLights; i++)
	{
		float2 direction = float2(myLights[i].myPosition.xy - (input.position.xy / Resolution.xy));	
		direction.x *= (Resolution.x / Resolution.y);
		
		float theLength = length(direction);
		theLength = normalize(theLength);
		
		float distance = (1 / length(direction)) * myLights[i].myPosition.w;
		finalColor += (DiffuseColor * distance * myLights[i].myLightColor) * myLights[i].myPosition.z;
	}
	
	
	return finalColor + AmbientLight;
}
#endif

SamplerState SampleType;
float4 PShader(PixelInputTypeCustom  input) : SV_TARGET
{
	float4 Diffuse = shaderTexture.Sample(SampleType, input.tex) * input.color;
	input.color = Diffuse;
	#ifdef USE_LIGHTS
	if(input.textureMappingData > 0.0f)
	{
		return CalculateLight(input);
	}
	#endif
    return input.color;
}