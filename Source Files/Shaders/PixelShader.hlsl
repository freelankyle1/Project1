cbuffer CBuf
{
    float4 face_colors[1];
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    return input.col;
    //return face_colors[tid/2];
}