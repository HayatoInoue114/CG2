#include "Particle.hlsli"

struct Material {
	float4 color;
	int enableLighting;
	float4x4 uvTransform;
};

struct DirectionalLight
{
	float4 color; //!< ライトの色
	float3 direction; //!< ライトの向き
	float intensity; //!< 輝度
};

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1); 

struct PixelShaderOutput {
	float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	float4 transformdUV = mul(float4(input.texcoord,0.0f,1.0f),gMaterial.uvTransform);
	float4 textureColor = gTexture.Sample(gSampler, transformdUV.xy);
	output.color = gMaterial.color * textureColor * input.color;

	//textureのa値が0.5以下の時にPixelを棄却
	if(output.color.a == 0.0) {
		discard;
	}
	return output;
}