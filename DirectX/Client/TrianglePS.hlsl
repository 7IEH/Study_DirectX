
struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

float4 ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}

// pixel shader가 하는일 색깔에 대해 리턴 해줍니다.
// 색깔과 관련된 데이터만 처리 가능