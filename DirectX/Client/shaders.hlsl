
struct VS_Input
{
    float2 pos : POS;
    float4 color : COL;
};

// ���� ���̴��� ���� �޾ƿ�
// ������ ���� ������ �����ϴ� ����
// ������ ���� : �ø�ƽ(�±�)

struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

// vs_main���� ���������� ó����
// ����� �����ϴ� �����Դϴ�.

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos, 0.f, 2.f);
    output.color = input.color;
    
    return output;
}

// �Էµ� vs_input �������� ó���ϴ� ����

float4 ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}

// pixel shader�� �ϴ��� ���� ���� ���� ���ݴϴ�.
// ����� ���õ� �����͸� ó�� ����