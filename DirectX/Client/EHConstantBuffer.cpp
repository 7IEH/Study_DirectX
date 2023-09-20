#include "EHConstantBuffer.h"
#include "EHD3D.h"

namespace EH
{
	ConstantBuffer::ConstantBuffer()
		:mType(enums::CBYTES::None)
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ConstantBuffer::Create(size_t size)
	{
		mDesc.ByteWidth = size; // 16 의 배수로
		mDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		mDesc.Usage = D3D11_USAGE_DYNAMIC;
		mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		mDesc.MiscFlags = 0;
		mDesc.StructureByteStride = 0;

		if(FAILED(GetDevice()->GetGPUDevice()->CreateBuffer(&mDesc,nullptr,mBuffer.GetAddressOf())))
			return false;

		return true;
	}

	void ConstantBuffer::Bind(void* data)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		GetDevice()->GetGPUContext()->Map(mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, data, mDesc.ByteWidth);
		GetDevice()->GetGPUContext()->Unmap(mBuffer.Get(), 0);
	}

	void ConstantBuffer::SetPipline(graphics::ShaderStage stage)
	{
		GetDevice()->SetConstantBuffer(stage, mType, mBuffer.Get());
	}
}