
struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

float4 ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}

// pixel shader�� �ϴ��� ���� ���� ���� ���ݴϴ�.
// ����� ���õ� �����͸� ó�� ����