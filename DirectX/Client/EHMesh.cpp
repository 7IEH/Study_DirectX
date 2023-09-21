#include "EHMesh.h"
#include "EHD3D.h"
#include "EHRenderer.h"

namespace EH
{
	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT Count)
	{
		mIndexCount = Count;
		mVBDesc.ByteWidth = sizeof(renderer::Vertex) * Count;
		mVBDesc.Usage = D3D11_USAGE_IMMUTABLE;
		mVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.CPUAccessFlags = 0;
		
		D3D11_SUBRESOURCE_DATA SubData = {};
		SubData.pSysMem = data;

		if (FAILED(GetDevice()->GetGPUDevice()->CreateBuffer(&mVBDesc, &SubData, mVertexBuffer.GetAddressOf())))
			return false;

		return true;
	}

	void Mesh::BindBuffer()
	{
		UINT stride = sizeof(renderer::Vertex);
		UINT offset = 0;
		GetDevice()->GetGPUContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	}

	void Mesh::Render()
	{
		BindBuffer();
		GetDevice()->GetGPUContext()->Draw(mIndexCount,0);
	}
}