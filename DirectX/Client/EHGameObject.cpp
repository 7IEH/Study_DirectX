#include "EHGameObject.h"
#include "EHD3D.h"
#include "EHObject.h"
#include "EHApplication.h"
#include "EHBullet.h"

extern EH::Application application;

namespace EH
{
	GameObject::GameObject()
		:
		  mVertexShader(nullptr)
		, mPixelShader(nullptr)
		, mInputLayout(nullptr)
		, mStride(6 * sizeof(float))
		, mNumVerts(3)
		, mOffset(0)
		, mTest(0)
	{
		// Create VertexShader
		// 
		
		// Blob�� ���̴��� ������ ���̳ʸ� ������ �����ϰ� �ִ� ����ü�Դϴ�.

		//ID3DBlob* vsblob = nullptr;
		//ID3DBlob* shaderCompileErrorBlob = nullptr;
		//{
		//	HRESULT hResult = D3DCompileFromFile(
		//		  L"TriangleVS.hlsl"
		//		, nullptr
		//		, nullptr
		//		, "vs_main"
		//		, "vs_5_0", 0, 0, &vsblob
		//		, &shaderCompileErrorBlob);

		//	// 1. pFileName : ���̴� ������ ��� hlsl ���� �̸�
		//	// 2. pDefines : ���̴� ��ũ�θ� �����ϴ� D3D_SHADER_MACRO ���� �� ������ �迭�Դϴ� .
		//	// 3. pInclude : �����Ϸ��� ���� ������ ó���ϴ� �� ����ϴ� ID3DInclude �������̽� �� ���� ������ �������Դϴ�.
		//	// 4. pEntrypoint : shader���� ���� ������ �����ݴϴ�. shader���� ���� ������ ���� ����
		//	// 5. pTarget : shader�� ����� ���α׷� ������ �������ݴϴ�.
		//	// 6. Flags1 : hlsl ������ ������ �ϴ� ����� �������ݴϴ�.
		//	// 7. Flags2 : ȿ�� ������ �ɼ� �� �����Դϴ�.
		//	// 8. ppCode : ���̴� ������ ���� ����ü�� ��ȯ�մϴ�.
		//	// 9. ppErrorMags: blob ������ �־� error �߻� �� error ������ byte ����ü�� ��ȯ�մϴ�.

		//	if (FAILED(hResult))
		//	{
		//		const char* errorString = NULL;
		//		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		//			errorString = "Could not compile shader; file not found";
		//		else if (shaderCompileErrorBlob)
		//		{
		//			errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
		//			shaderCompileErrorBlob->Release();
		//		}
		//		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		//	}
		//	// �ش� vertex option�� ���� vertex shader�� �����մϴ�.
		//	// 1. pShaderBytecode : �����ϵ� ���̴��� ���� �������Դϴ�.
		//	// 2. BytecodeLength : �����ϵ� ������ ���̴��� ũ���Դϴ�.
		//	// 3. ID3D11ClassLinkage* : Ŭ���� ���� �������̽��� ���� �������Դϴ�.
		//	// 4. ID3D11VertexShader** : ������ vertexshader�� ��ȯ�մϴ�.

		//	hResult = GetDevice()->GetGPUDevice().Get()->
		//		CreateVertexShader(
		//		vsblob->GetBufferPointer()
		//		, vsblob->GetBufferSize()
		//		, nullptr
		//		, &mVertexShader);
		//	assert(SUCCEEDED(hResult));
		//}

		//// Create Pixle Shader
		//{
		//	ID3DBlob* psBlob;
		//	ID3DBlob* shaderCompileErrorBlob;
		//	HRESULT hResult = D3DCompileFromFile(
		//		 L"TrianglePS.hlsl"
		//		, nullptr
		//		, nullptr
		//		, "ps_main"
		//		, "ps_5_0"
		//		, 0, 0, &psBlob
		//		, &shaderCompileErrorBlob);

		//	// 1. pFileName : ���̴� ������ ��� hlsl ���� �̸�
		//	// 2. pDefines : ���̴� ��ũ�θ� �����ϴ� D3D_SHADER_MACRO ���� �� ������ �迭�Դϴ� .
		//	// 3. pInclude : �����Ϸ��� ���� ������ ó���ϴ� �� ����ϴ� ID3DInclude �������̽� �� ���� ������ �������Դϴ�.
		//	// 4. pEntrypoint : shader���� ���� ������ �����ݴϴ�. shader���� ���� ������ ���� ����
		//	// 5. pTarget : shader�� ����� ���α׷� ������ �������ݴϴ�.
		//	// 6. Flags1 : hlsl ������ ������ �ϴ� ����� �������ݴϴ�.
		//	// 7. Flags2 : ȿ�� ������ �ɼ� �� �����Դϴ�.
		//	// 8. ppCode : ���̴� ������ ���� ����ü�� ��ȯ�մϴ�.
		//	// 9. ppErrorMags: blob ������ �־� error �߻� �� error ������ byte ����ü�� ��ȯ�մϴ�.

		//	if (FAILED(hResult))
		//	{
		//		const char* errorString = NULL;
		//		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		//			errorString = "Could not compile shader; file not found";
		//		else if (shaderCompileErrorBlob)
		//		{
		//			errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
		//			shaderCompileErrorBlob->Release();
		//		}
		//		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		//	}

		//	// �ش� pixel option�� ���� pixel shader�� �����մϴ�.
		//	// 1. pShaderBytecode : �����ϵ� ���̴��� ���� �������Դϴ�.
		//	// 2. BytecodeLength : �����ϵ� ������ ���̴��� ũ���Դϴ�.
		//	// 3. ID3D11ClassLinkage* : Ŭ���� ���� �������̽��� ���� �������Դϴ�.
		//	// 4. ID3D11PixelShader** : ������ pixel shader�� ��ȯ�մϴ�.

		//	hResult = GetDevice()->GetGPUDevice().Get()->CreatePixelShader
		//	(
		//		psBlob->GetBufferPointer()
		//		, psBlob->GetBufferSize()
		//		, nullptr
		//		, &mPixelShader
		//	);
		//	assert(SUCCEEDED(hResult));
		//	psBlob->Release();
		//}

		//{
		//	// IA�ܰ迡�� ���� ��ҿ� ���� �����ϴ� �ܰ�
		//	// ��, ������ �̷� �������� �޾Ƽ� ����ϰڴٶ�� ���� ����ϴ� �ܰ��̴�.
		//	// 
		//	// D3D11_INPUT_ELEMENT_DESC ����ü �Ű�����
		//	// 1. SemanticName : ���̴� �ȿ��� ����ϴ� semantic�� �̸��� ����Ѵ�.
		//	// 2. SemanticIndex : ���̴� �ȿ��� ���� �ǹ̷� ���Ǵ� semantic�� ���� �Ҷ� ����ϴ� index ����?
		//	// 3. DXGI_FORMAT : semanticdata�� ����� ������ �����ϴ� ����Դϴ�. //ù��° ���� ��� float2 �ι�°�� float4�̴�.
		//	// 4. InputSlot : IA�� �ĺ��ϴ� ���� ��
		//	// 5. AlignedByteOffset : ���� �������� ������ �������� ���ϴ°� �����ϴ�.
		//	// 6. InputSlotClass : �ν��Ͻ� �ɼ��� ����� �� ����ϴ� �ɼǰ����ϴ�.
		//	// �ν��ͽ��̶�?
		//	// -> DP CALL(CPU -> GPU DRAW CALL)�� ���� ���� ������ �׷����� �� DP CALL�� Ƚ���� �������ٵ�, �̸� ���̱� ����
		//	// ����ϴ� ���
		//	// 7. InstanceDataStepRate : D3D11_INPUT_PER_VERTEX_DATA�� �������� ��� 0���� �����ϰ� instance �������� ������ ��쿡
		//	// ����ϴ� �Ű����� �����ϴ�.

		//	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		//	{
		//		{"POS",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		//		{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		//	};


		//	// ���������� �̷��� ����� ���̴�. ��, ���̴����� ����� ������ ���� ����ϴ� layout ��ü ����
		//	// 1.pInputElementDescs : �޾ƿ� ������ ������ �����ϴ� �Ű�����
		//	// 2. NumElements : �ش� ������ ũ�⸦ ����
		//	// 3. pShaderBytecodeWithInputSignature : vsblob -> vertexshader �ܰ� ��, ���� ���� �ܰ迡�� ������ ���Ŀ� ��ȿ���� �Ǵ��մϴ�.
		//	// 4. BytecodeLength : vsblob -> �����ϵ� vertexshader�� ũ�⸦ �����մϴ�.
		//	// 5. ppInputLayout : ������ inputlayout�� ��ȯ�մϴ�.
		//	// InputLayout 

		//	HRESULT hResult = GetDevice()->GetGPUDevice().Get()->CreateInputLayout(
		//		inputElementDesc
		//		, ARRAYSIZE(inputElementDesc)
		//		, vsblob->GetBufferPointer()
		//		, vsblob->GetBufferSize()
		//		, &mInputLayout);
		//	assert(SUCCEEDED(hResult));
		//	vsblob->Release();
		//}

		//// DC�� ������ vertex buffer�� �Էµ� ���� ������ ���� ��� ������ �׸����� ���� ���� ���ݴϴ�.

		//// ������ VERTEXBUFFER�� ����� ������ ������ ���� ������ �ؼ��� �̷� �������� �Ұ��̴� �������ݴϴ�.

		//// �� object���� ���� ���������� ó������ ������ ���۵��� �Ҵ����ݴϴ�.
		//// vertexshader�� ������ ���� ������, ���� �ܰ踦 ���� resterization�� ���� �ϳ��� ������ ��
		//// �������� ���� ������ �۾��� �մϴ�.

		//// ���� �׸��⿡ ����� buffer�� ������ݴϴ�.
		//// ������ ���Ŀ� ���� ������ݴϴ�.
		//// 1. ByteWidth : buffer�� ũ�⸦ �����մϴ�.
		//// 2. Usage : buffer�� �а� ���� ����� �����մϴ�.
		//// D3D11_USAGE_IMMUTABLE�� �� buffer�� ���� �� ������ �Ұ����մϴ�.
		//// 3. BindFlags : buffer ������ �����մϴ�.

		//D3D11_BUFFER_DESC vertexBufferDesc = {};
		//vertexBufferDesc.ByteWidth = sizeof(vertexData);
		//vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//// buffer�� �ʱ�ȭ �� ���� �����ϴ� ��ü�Դϴ�.
		//float tempdata[18] =
		//{
		//	0.f , 0.5f, 1.f, 0.f, 0.f, 0.f,
		//	0.5f , -0.5f, 0.f, 1.f, 0.f, 0.f,
		//	-0.5f , -0.5f, 0.f, 0.f, 1.f, 0.f
		//};

	
		//SetVertexData(tempdata);

		//D3D11_SUBRESOURCE_DATA vertexSubresourceData = { vertexData };

		//// 1. pDesc : ������ buffer�� ������ �����մϴ�.
		//// 2. pInitialData : buffer�� �ʱ�ȭ ��
		//// 3. ppbuffer : pDesc�� �Է��� ������ buffer�� ��ȯ�մϴ�.

		//HRESULT hResult = GetDevice()->GetGPUDevice().Get()->CreateBuffer(
		//	&vertexBufferDesc
		//	, &vertexSubresourceData
		//	, &mVertexBuffer);
		//assert(SUCCEEDED(hResult));

		// ->Vertex buffer ����
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		/*GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout);
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVertexShader, nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPixelShader, nullptr, 0);*/
	}

	void GameObject::Render()
	{
		// ���� ���۸� IA ���������� �ܰ迡 �Ҵ��մϴ�.
		// 1. StartSlot : IA�� �Ҵ��ϱ� ���� inputslot�� ���� ��ġ�� �������ݴϴ�.
		// 2. NumBuffers : �Է� ���Կ� 
		// 3. ppVertexBufffers : �������� ��� �ִ� ������ ���� �ּ�
		// 4. pStrides : stride �迭�� ���� ��ġ. ��, ���� �ȿ� �ϳ��� ������ �����ϴ� ũ��
		// 5. pOffsets : offset �迭�� ���� ��ġ. ���۾ȿ� ������ ���� ��ġ�� offset ũ��

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		//GetDevice()->GetGPUContext().Get()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mStride, &mOffset);

		//// 1. VertexCount : �׸� ������ ��
		//// 2. StartVertexLocation : ���� ������ ù��° �ε���

		//GetDevice()->GetGPUContext().Get()->Draw(mNumVerts, 0);
	}
}