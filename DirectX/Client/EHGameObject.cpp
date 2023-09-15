#include "EHGameObject.h"
#include "EHDX11.h"

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
	{
		// Create VertexShader
		ID3DBlob* vsblob = nullptr;
		ID3DBlob* shaderCompileErrorBlob = nullptr;
		{
			HRESULT hResult = D3DCompileFromFile(
				 L"shaders.hlsl"
				, nullptr
				, nullptr
				, "vs_main"
				, "vs_5_0", 0, 0, &vsblob
				, &shaderCompileErrorBlob);
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

			hResult = DX11::GetD3DDevice()->CreateVertexShader(
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
			
			hResult = DX11::GetD3DDevice()->CreatePixelShader
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
			D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
			{
				{"POS",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
			};

			HRESULT hResult = DX11::GetD3DDevice()->CreateInputLayout(
				 inputElementDesc
				, ARRAYSIZE(inputElementDesc)
				, vsblob->GetBufferPointer()
				, vsblob->GetBufferSize()
				, &mInputLayout);
			assert(SUCCEEDED(hResult));
			vsblob->Release();
		}
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		D3D11_BUFFER_DESC vertextBufferDesc = {};
		vertextBufferDesc.ByteWidth = sizeof(mVertextData);
		vertextBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertextBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;


		D3D11_SUBRESOURCE_DATA vertexSubresourceData = { mVertextData };

		HRESULT hResult = DX11::GetD3DDevice()->CreateBuffer(
			  &vertextBufferDesc
			, &vertexSubresourceData
			, &mVertexBuffer);
		assert(SUCCEEDED(hResult));
	}

	void GameObject::Render()
	{
		DX11::GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX11::GetD3DDeviceContext()->IASetInputLayout(mInputLayout);

		DX11::GetD3DDeviceContext()->VSSetShader(mVertexShader, nullptr, 0);
		DX11::GetD3DDeviceContext()->PSSetShader(mPixelShader, nullptr, 0);

		DX11::GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mStride, &mOffset);

		DX11::GetD3DDeviceContext()->Draw(mNumVerts, 0);
	}
}