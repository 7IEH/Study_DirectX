
struct VS_Input
{
    float2 pos : POS;
    float4 color : COL;
};

struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos, 0.f, 2.f);
    output.color = input.color;
    
    return output;
}

float ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}