cbuffer CBuf
{
    float4 face_colors[1];
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPELR : register(s0);

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float3 pixelColor = objTexture.Sample(objSamplerState, input.tex);
    return float4(pixelColor, 1.0f);

}