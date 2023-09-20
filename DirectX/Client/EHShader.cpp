#include "EHShader.h"
#include <filesystem>
#include "EHD3D.h"

namespace EH
{
	Shader::Shader()
		:
		mTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}

	Shader::~Shader()
	{
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Shader::Create(const graphics::ShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		/*std::filesystem::path path
			= std::filesystem::current_path().parent_path();
		path += "\\Shaders_SOURCE\\";

		std::wstring shaderPath(path);
		shaderPath += file;*/
		ID3DBlob* shaderCompileErrorBlob = nullptr;

		if (stage == graphics::ShaderStage::VS)
		{
			HRESULT hResult = D3DCompileFromFile(file.c_str(), nullptr, nullptr, funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), &shaderCompileErrorBlob);

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

			hResult = GetDevice()->GetGPUDevice().Get()->CreateVertexShader(mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
			assert(SUCCEEDED(hResult));
		}

		if (stage == graphics::ShaderStage::PS)
		{
			HRESULT hResult = D3DCompileFromFile(file.c_str(), nullptr, nullptr, funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), &shaderCompileErrorBlob);

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

			hResult = GetDevice()->GetGPUDevice().Get()->CreatePixelShader
			(
				mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize()
				, nullptr
				, &mPS
			);
			assert(SUCCEEDED(hResult));
		}
	}


	void Shader::Update()
	{
		GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(mTopology);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout.Get());
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVS.Get(), nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPS.Get(), nullptr, 0);
	}
}