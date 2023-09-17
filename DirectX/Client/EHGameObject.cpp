#include "EHGameObject.h"
#include "EHD3D.h"

namespace EH
{
	GameObject::GameObject(std::wstring shader)
		:
		mShader(shader)
		, mVertexShader(nullptr)
		, mPixelShader(nullptr)
		, mInputLayout(nullptr)
		, mStride(6 * sizeof(float))
		, mNumVerts(3)
		, mOffset(0)
		, mTest(0)
	{
		// Create VertexShader
		// 
		
		// Blob은 쉐이더의 정보를 바이너리 단위로 저장하고 있는 구조체입니다.

		ID3DBlob* vsblob = nullptr;
		ID3DBlob* shaderCompileErrorBlob = nullptr;
		{
			HRESULT hResult = D3DCompileFromFile(
				mShader.c_str()
				, nullptr
				, nullptr
				, "vs_main"
				, "vs_5_0", 0, 0, &vsblob
				, &shaderCompileErrorBlob);

			// 1. pFileName : 쉐이더 정보가 담긴 hlsl 파일 이름
			// 2. pDefines : 셰이더 매크로를 정의하는 D3D_SHADER_MACRO 구조 의 선택적 배열입니다 .
			// 3. pInclude : 컴파일러가 포함 파일을 처리하는 데 사용하는 ID3DInclude 인터페이스 에 대한 선택적 포인터입니다.
			// 4. pEntrypoint : shader에서 진입 지점을 정해줍니다. shader에도 진입 지점이 많기 때문
			// 5. pTarget : shader의 사용할 프로그램 버전을 지정해줍니다.
			// 6. Flags1 : hlsl 파일을 컴파일 하는 방법을 지정해줍니다.
			// 7. Flags2 : 효과 컴파일 옵션 의 조합입니다.
			// 8. ppCode : 쉐이더 정보를 담은 구조체를 반환합니다.
			// 9. ppErrorMags: blob 생성에 있어 error 발생 시 error 정보를 byte 구조체로 반환합니다.

			if (FAILED(hResult))
			{
				const char* errorString = NULL;
				if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
					errorString = "Could not compile shader; file not found";
				else if (shaderCompileErrorBlob)
				{
					errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
					shaderCompileErrorBlob->Release();
				}
				MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			}
			// 해당 vertex option를 가진 vertex shader를 생성합니다.
			// 1. pShaderBytecode : 컴파일된 셰이더에 대한 포인터입니다.
			// 2. BytecodeLength : 컴파일된 꼭짓점 셰이더의 크기입니다.
			// 3. ID3D11ClassLinkage* : 클래스 연결 인터페이스에 대한 포인터입니다.
			// 4. ID3D11VertexShader** : 생성된 vertexshader를 반환합니다.

			hResult = D3D::GetD3DDevice()->CreateVertexShader(
				vsblob->GetBufferPointer()
				, vsblob->GetBufferSize()
				, nullptr
				, &mVertexShader);
			assert(SUCCEEDED(hResult));
		}

		// Create Pixle Shader
		{
			ID3DBlob* psBlob;
			ID3DBlob* shaderCompileErrorBlob;
			HRESULT hResult = D3DCompileFromFile(
				mShader.c_str()
				, nullptr
				, nullptr
				, "ps_main"
				, "ps_5_0"
				, 0, 0, &psBlob
				, &shaderCompileErrorBlob);

			// 1. pFileName : 쉐이더 정보가 담긴 hlsl 파일 이름
			// 2. pDefines : 셰이더 매크로를 정의하는 D3D_SHADER_MACRO 구조 의 선택적 배열입니다 .
			// 3. pInclude : 컴파일러가 포함 파일을 처리하는 데 사용하는 ID3DInclude 인터페이스 에 대한 선택적 포인터입니다.
			// 4. pEntrypoint : shader에서 진입 지점을 정해줍니다. shader에도 진입 지점이 많기 때문
			// 5. pTarget : shader의 사용할 프로그램 버전을 지정해줍니다.
			// 6. Flags1 : hlsl 파일을 컴파일 하는 방법을 지정해줍니다.
			// 7. Flags2 : 효과 컴파일 옵션 의 조합입니다.
			// 8. ppCode : 쉐이더 정보를 담은 구조체를 반환합니다.
			// 9. ppErrorMags: blob 생성에 있어 error 발생 시 error 정보를 byte 구조체로 반환합니다.

			if (FAILED(hResult))
			{
				const char* errorString = NULL;
				if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
					errorString = "Could not compile shader; file not found";
				else if (shaderCompileErrorBlob)
				{
					errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
					shaderCompileErrorBlob->Release();
				}
				MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			}

			// 해당 pixel option를 가진 pixel shader를 생성합니다.
			// 1. pShaderBytecode : 컴파일된 셰이더에 대한 포인터입니다.
			// 2. BytecodeLength : 컴파일된 꼭짓점 셰이더의 크기입니다.
			// 3. ID3D11ClassLinkage* : 클래스 연결 인터페이스에 대한 포인터입니다.
			// 4. ID3D11PixelShader** : 생성된 pixel shader를 반환합니다.

			hResult = D3D::GetD3DDevice()->CreatePixelShader
			(
				psBlob->GetBufferPointer()
				, psBlob->GetBufferSize()
				, nullptr
				, &mPixelShader
			);
			assert(SUCCEEDED(hResult));
			psBlob->Release();
		}

		{
			// IA단계에서 단일 요소에 대해 설정하는 단계
			// 즉, 정점을 이런 형식으로 받아서 사용하겠다라는 것을 명시하는 단계이다.
			// 
			// D3D11_INPUT_ELEMENT_DESC 구조체 매개변수
			// 1. SemanticName : 셰이더 안에서 사용하는 semantic의 이름을 명시한다.
			// 2. SemanticIndex : 셰이더 안에서 같은 의미로 사용되는 semantic을 구분 할때 사용하는 index 느낌?
			// 3. DXGI_FORMAT : semanticdata가 저장될 형식을 지정하는 요소입니다. //첫번째 같은 경우 float2 두번째는 float4이다.
			// 4. InputSlot : IA를 식별하는 정수 값
			// 5. AlignedByteOffset : 선택 사항으로 정점의 오프셋을 뜻하는거 같습니다.
			// 6. InputSlotClass : 인스턴싱 옵션을 사용할 때 사용하는 옵션같습니다.
			// 인스터싱이란?
			// -> DP CALL(CPU -> GPU DRAW CALL)이 같은 모델을 여러번 그려야할 때 DP CALL의 횟수가 증가할텐데, 이를 줄이기 위해
			// 사용하는 기법
			// 7. InstanceDataStepRate : D3D11_INPUT_PER_VERTEX_DATA를 선택했을 경우 0으로 지정하고 instance 형식으로 지정할 경우에
			// 사용하는 매개변수 같습니다.

			D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
			{
				{"POS",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
			};


			// 정점형식은 이렇게 사용할 것이다. 즉, 쉐이더에서 사용할 점점에 대해 명시하는 layout 객체 생성
			// 1.pInputElementDescs : 받아올 정점의 형식을 지정하는 매개변수
			// 2. NumElements : 해당 형식의 크기를 지정
			// 3. pShaderBytecodeWithInputSignature : vsblob -> vertexshader 단계 즉, 아직 정점 단계에서 정점의 형식에 유효성을 판단합니다.
			// 4. BytecodeLength : vsblob -> 컴파일된 vertexshader의 크기를 참조합니다.
			// 5. ppInputLayout : 생성된 inputlayout을 반환합니다.
			// InputLayout 

			HRESULT hResult = D3D::GetD3DDevice()->CreateInputLayout(
				inputElementDesc
				, ARRAYSIZE(inputElementDesc)
				, vsblob->GetBufferPointer()
				, vsblob->GetBufferSize()
				, &mInputLayout);
			assert(SUCCEEDED(hResult));
			vsblob->Release();
		}

		// DC에 앞으로 vertex buffer에 입력될 정점 정보를 통해 어떠한 도형을 그릴지에 대해 지정 해줍니다.

		// 앞으로 VERTEXBUFFER에 저장될 정점의 정보에 대한 형태의 해석은 이런 형식으로 할것이다 지정해줍니다.

		// 각 object마다 정점 정보에대해 처리해줄 각각의 버퍼들을 할당해줍니다.
		// vertexshader는 정점에 대한 정보를, 정점 단계를 지나 resterization을 통해 하나의 도형이 된
		// 정점들의 색을 입히는 작업을 합니다.

		
		D3D::GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		D3D::GetD3DDeviceContext()->IASetInputLayout(mInputLayout);
		D3D::GetD3DDeviceContext()->VSSetShader(mVertexShader, nullptr, 0);
		D3D::GetD3DDeviceContext()->PSSetShader(mPixelShader, nullptr, 0);

	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// 이제 그리기에 사용할 buffer를 만들어줍니다.
		// 버퍼의 형식에 대해 명시해줍니다.
		// 1. ByteWidth : buffer의 크기를 지정합니다.
		// 2. Usage : buffer를 읽고 쓰는 방법을 지정합니다.
		// D3D11_USAGE_IMMUTABLE은 이 buffer는 만든 후 수정이 불가능합니다.
		// 3. BindFlags : buffer 유형을 선택합니다.

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = sizeof(mVertextData);
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mVertextData[0] -= 0.01f;
			mVertextData[6] -= 0.01f;
			mVertextData[12] -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mVertextData[0] += 0.01f;
			mVertextData[6] += 0.01f;
			mVertextData[12] += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mVertextData[1] += 0.01f;
			mVertextData[7] += 0.01f;
			mVertextData[13] += 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mVertextData[1] -= 0.01f;
			mVertextData[7] -= 0.01f;
			mVertextData[13] -= 0.01f;
		}

		// buffer에 초기화 될 값을 저장하는 객체입니다.

		D3D11_SUBRESOURCE_DATA vertexSubresourceData = { mVertextData };

		// 1. pDesc : 생성할 buffer의 형식을 지정합니다.
		// 2. pInitialData : buffer의 초기화 값
		// 3. ppbuffer : pDesc에 입력한 형식의 buffer을 반환합니다.

		HRESULT hResult = D3D::GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc
			, &vertexSubresourceData
			, &mVertexBuffer);
		assert(SUCCEEDED(hResult));

		// ->Vertex buffer 생성
	}

	void GameObject::Render()
	{
		// 정점 버퍼를 IA 파이프라인 단계에 할당합니다.
		// 1. StartSlot : IA에 할당하기 위한 inputslot에 시작 위치를 지정해줍니다.
		// 2. NumBuffers : 입력 슬롯에 
		// 3. ppVertexBufffers : 정점들이 담겨 있는 버퍼의 시작 주소
		// 4. pStrides : stride 배열의 시작 위치. 즉, 버퍼 안에 하나의 정점를 구분하는 크기
		// 5. pOffsets : offset 배열의 시작 위치. 버퍼안에 정점의 시작 위치에 offset 크기


		D3D::GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mStride, &mOffset);


		// 1. VertexCount : 그릴 정점의 수
		// 2. StartVertexLocation : 정점 버퍼의 첫번째 인덱스

		D3D::GetD3DDeviceContext()->Draw(mNumVerts, 0);
	}
}