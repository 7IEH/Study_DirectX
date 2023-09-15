#pragma once

#include "Commoninclude.h"

namespace EH
{
	class GameObject
	{
	public:
		GameObject(std::wstring shader);
		~GameObject();

		void Initialize();
		void Update();
		void Render();

		void SetVertexData(float vertexdata[18])
		{
			for (int i = 0;i < 18;i++)
			{
				mVertextData[i] = vertexdata[i];
			}
		}



	private:
		std::wstring mShader;
		// 나중에 옮기기
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11InputLayout* mInputLayout;

		ID3D11Buffer* mVertexBuffer;
		UINT mNumVerts;
		UINT mStride;
		UINT mOffset;

		float mVertextData[18];
	};
}


