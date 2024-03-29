

cbuffer cbuf : register(b0)
{
   matrix transform;
};

struct VS_INPUT
{
    float3 pos : POSITION;
    float4 col : COLOR;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};



VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.pos = mul(float4(input.pos, 1.0f), transform);
    output.col = input.col;
    
    return output;
    //return mul(float4(pos, 1.0f), transform);
   
}