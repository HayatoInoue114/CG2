#include "Object3d.hlsli"

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

struct Camera
{
    float3 worldPosition;
};

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1); 
TextureCube<float4> gEnvironmentTexture : register(t1);
ConstantBuffer<Camera> gCamera : register(b2);

struct PixelShaderOutput {
	float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	//float4 transformdUV = mul(float4(input.texcoord.x,input.texcoord.y,0.0f,1.0f),gMaterial.uvTransform);
	float4 textureColor = gTexture.Sample(gSampler, input.texcoord);

	//textureのa値が0.5以下の時にPixelを棄却
	if(textureColor.a <= 0.5) {
		discard;
	}

	if (gMaterial.enableLighting != 0) {// LIghtingする場合
		//half lambert
		float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
		float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        float3 cameraToPosition = normalize(input.worldPosition.xyz - gCamera.worldPosition);
        float3 reflectedVector = reflect(cameraToPosition, normalize(input.normal));
        float4 environmentColor = gEnvironmentTexture.Sample(gSampler, reflectedVector);
		//output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
        output.color.rgb = textureColor.rgb;
        output.color.rgb += environmentColor.rgb;
        //output.color.rgb = float3(1, 0, 0);
		output.color.a = gMaterial.color.a * textureColor.a;
	}
	else {
		output.color = gMaterial.color * textureColor;
	}

	return output;
}