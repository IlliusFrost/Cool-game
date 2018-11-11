#include "common.fx"

SamplerState SampleType;
Texture2D shaderTextures : register( t1 );

float scanline(float2 uv) {
	return sin(myResolution.y * uv.y * 0.7 - myTimings.x * 10.0);
}

float slowscan(float2 uv) {
	return sin(myResolution.y * uv.y * 0.02 + myTimings.x * 6.0);
}

float2 colorShift(float2 uv) {
	return float2(
		uv.x,
		uv.y + sin(myTimings.x)*0.02
	);
}

float noise(float2 uv) {
	return 1.0 + myRandomValues.y * 0.5;
}

float2 crt(float2 coord, float bend)
{
	// put in symmetrical coords
	coord = (coord - 0.5) * 2.0;

	coord *= 0.5;	
	
	// deform coords
	coord.x *= 1.0 + pow((abs(coord.y) / bend), 2.0);
	coord.y *= 1.0 + pow((abs(coord.x) / bend), 2.0);

	// transform back to 0.0 - 1.0 space
	coord  = (coord / 1.0) + 0.5;

	return coord;
}

float2 colorshift(float2 uv, float amount, float rand) {
	
	return float2(
		uv.x,
		uv.y + amount * rand // * sin(uv.y * iResolution.y * 0.12 + iTime)
	);
}

float2 scandistort(float2 uv) {
	float scan1 = clamp(cos(uv.y * 2.0 + myTimings.x), 0.0, 1.0);
	float scan2 = clamp(cos(uv.y * 2.0 + myTimings.x + 4.0) * 10.0, 0.0, 1.0) ;
	float amount = scan1 * scan2 * uv.x * 0.2; 
	
	//uv.x -= 0.05 * mix(texture(iChannel1, vec2(uv.x, amount)).r * amount, amount, 0.9);

	return uv;
	 
}


float vignette(float2 uv) {
	uv = (uv - 0.5) * 0.98;
	return clamp(pow(abs(cos(uv.x * 3.1415)), 1.2) * pow(abs(cos(uv.y * 3.1415)), 1.2) * 50.0, 0.0, 1.0);
}


float rand_1_05(in float2 uv)
{
    float2 noise = (frac(sin(dot(uv ,float2(12.9898,78.233)*2.0)) * 43758.5453));
    return abs(noise.x + noise.y) * 0.5;
}

float chromaticDisplacement(float displaceFactor)
{
	float amount = 0.0;
	amount = (1.0 + sin(myTimings.x * 6.0)) * 0.5;
	amount *= 1.0 + sin(myTimings.x * 2.0) * 0.5;
	amount *= 1.0 + sin(myTimings.x * 2.0) * 0.5;
	amount *= 1.0 + sin(myTimings.x * 2.0) * 0.5;
	amount = pow(amount,1.0);
	amount *= displaceFactor;
	amount *= abs(sin(myTimings.x * 0.5));
	amount *= amount;
	return amount;
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTextures.Sample(SampleType, input.tex) * input.color;
	float2 uv = input.tex.xy;
	
	float2 sd_uv = scandistort(uv);
	float2 crt_uv = crt(sd_uv, 2.0);
	
	float4 color;
	
	//float2 rand = float2(sin(myTimings.x * 3.0 + sin(myTimings.x)) * sin(myTimings.x * 0.2), clamp(sin(myTimings.x * 1.52 * uv.y + sin(myTimings.x)) * sin(myTimings.x* 1.2), 0.0, 1.0));
	float3 rand = float3(rand_1_05(float2(myTimings.x * 0.01, myTimings.x * 0.02)), rand_1_05(float2(myTimings.x * 0.03, myTimings.x * 0.015)), rand_1_05(float2(myTimings.x * 0.005, myTimings.x * 0.04)));
	
	float chromaticDis = chromaticDisplacement(0.02);
	color.r = shaderTextures.Sample(SampleType, crt(float2(sd_uv.x + chromaticDis, sd_uv.y), 2.0)).r;
	color.g = shaderTextures.Sample(SampleType, crt(float2(sd_uv.x, sd_uv.y), 2.0)).g;
	color.b = shaderTextures.Sample(SampleType, crt(float2(sd_uv.x - chromaticDis, sd_uv.y), 2.0)).b;
	color.a = Diffuse.a;


	//color = Diffuse;

	float sl = scanline(crt_uv);
	float4 scanline_color = float4(sl, sl, sl, sl);
	float sc = slowscan(crt_uv);
	float4 slowscan_color = float4(sc, sc, sc, sc);

	float4 result = lerp(color, lerp(scanline_color, slowscan_color, 0.5), 0.05) *
		vignette(uv);
	result.a = Diffuse.a;

	if (crt_uv.x > 0.99) { result -= float4(1.0, 1.0, 1.0, 0.0) * pow((crt_uv.x - 0.99) / 0.01, 2.0); }
	if (crt_uv.y > 0.99) { result -= float4(1.0, 1.0, 1.0, 0.0) * pow((crt_uv.y - 0.99) / 0.01, 2.0); }
	if (crt_uv.x < 0.01) { result -= float4(1.0, 1.0, 1.0, 0.0) * pow((1.0 - crt_uv.x / 0.01), 2.0); }
	if (crt_uv.y < 0.01) { result -= float4(1.0, 1.0, 1.0, 0.0) * pow((1.0 - crt_uv.y / 0.01), 2.0); }

	return result;
}

