
struct VS_Input
{
    float3 pos : POS;
    float4 color : COL;
};

struct VS_Output
{
    float4 position : SV_Position;
    float4 color : COL;
};

cbuffer TRANSFORM : register(b0)
{
    float3 cbpos;
    int pad1;
    float3 cbscale;
    int pad2;
};

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos + cbpos.xyz, 1.f);
    output.position.xyz *= cbscale;
    output.color = input.color;
    
    return output;
}