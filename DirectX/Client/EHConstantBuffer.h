#pragma once

#include "Commoninclude.h"

namespace EH
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(graphics::ShaderStage stage);
		void SetType(enums::CBYTES type) { mType = type; }

	private:
		enums::CBYTES mType;
		D3D11_BUFFER_DESC mDesc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	};
}


