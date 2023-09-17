
struct VS_Input
{
    float2 pos : POS;
    float4 color : COL;
};

// 정점 쉐이더로 부터 받아올
// 정점에 대한 정보를 저장하는 공간
// 저장할 공간 : 시맨틱(태그)

struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

// vs_main에서 최종적으로 처리한
// 결과를 리턴하는 공간입니다.

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos, 0.f, 2.f);
    output.color = input.color;
    
    return output;
}

// 입력된 vs_input 정점들을 처리하는 공간

float4 ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}

// pixel shader가 하는일 색깔에 대해 리턴 해줍니다.
// 색깔과 관련된 데이터만 처리 가능