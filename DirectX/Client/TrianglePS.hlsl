
//SamplerState SampleType;
//Texture2D shaderTexture;

struct VS_Output
{
    float4 position : SV_POSITION;
    float4 color : COL;
};

float4 ps_main(VS_Output input) : SV_TARGET
{  
    return input.color;
}

  //float4 textureColor;
    
    //textureColor = shaderTexture.Sample(SampleType, input.tex);

// pixel shader�� �ϴ��� ���� ���� ���� ���ݴϴ�.
// ����� ���õ� �����͸� ó�� ����