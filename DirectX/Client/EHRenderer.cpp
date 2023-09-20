#include "EHRenderer.h"
#include "EHResources.h"
#include "EHD3D.h"
#include "EHResources.h"


namespace EH::renderer
{
	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;

	void LoadBuffer()
	{
		std::vector<Vertex> vertexes;
		vertexes.resize(3);
		vertexes[0].pos = Math::Vector3(0.f, 0.5f, 0.f);
		vertexes[0].Color = Math::Vector4(1.f, 0.f, 0.f, 0.f);

		vertexes[1].pos = Math::Vector3(0.5f, -0.5f, 0.f);
		vertexes[1].Color = Math::Vector4(0.f, 1.f, 0.f,0.f);

		vertexes[2].pos = Math::Vector3(-0.5f, -0.5f, 0.f);
		vertexes[2].Color = Math::Vector4(0.f, 0.f, 1.f,0.f);

		/*std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);*/

		mesh->CreateVertexBuffer(vertexes.data(), 3);
		Resources::Insert(L"TriangleMesh", mesh);

	}

	void LoadShader()
	{
		shader->Create(graphics::ShaderStage::VS, L"TriangleVS.hlsl", "vs_main");
		shader->Create(graphics::ShaderStage::PS, L"TrianglePS.hlsl", "ps_main");
		Resources::Insert(L"TriangleShader", shader);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{"POS",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		HRESULT hResult = GetDevice()->GetGPUDevice().Get()->CreateInputLayout(
			inputElementDesc
			, ARRAYSIZE(inputElementDesc)
			, shader->GetVSCode()->GetBufferPointer()
			, shader->GetVSCode()->GetBufferSize()
			, shader->GetInputLayoutAddressOf());

		assert(SUCCEEDED(hResult));
	}

	void Initialize()
	{
		mesh = new Mesh();
		shader = new Shader();

		LoadShader();
		LoadBuffer();
	}

	void Release()
	{
		delete mesh;
		delete shader;
	}
}