#pragma once

#include "EHResource.h"

namespace EH
{
	class Texture : public Resource
	{
	private:
		struct TargaHeader
		{

		};

	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path);
		
		void Create();

	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTextureView;

	};
}


