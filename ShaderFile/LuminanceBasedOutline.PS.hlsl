#include "CopyImage.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

static const float kPrewittHorizontalKernel[3][3] =
{
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
};

static const float2 kPrewittVerticalKernel[3][3] =
{
    { -1.0f / 6.0f , -1.0f / 6.0f ,  -1.0f / 6.0f },
    { 0.0f , 0.0f, 0.0f ,  1.0f, 0.0f },
    { 1.0f / 6.0f ,  1.0f / 6.0f,  1.0f / 6.0f },
};

float Luminance(float3 v)
{
    return dot(v, float3(0.2125f, 0.7154f, 0.0721f));
}

PixelShaderOutput main(VertexShaderOutput input)
{
    float2 difference = float2(0.0f, 0.0f);
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            float2 texcoord = input.texcoord + kIndex3x3[x][y] * uvStepSize;
            float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            float luminance = Luminance(fetchColor);
            difference.x += luminance * kPrewittHorizontalKernel[x][y];
            difference.y += luminance * kPrewittVerticalKernel[x][y];
        }
    }
    float weight = length(difference);
    weight = saturate(weight);
    
    PixelShaderOutput output;
    output.color.rgb = weight;
    output.color.a = 1.0f;
    
    return output;
}