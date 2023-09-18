#pragma once

#include "Commoninclude.h"

namespace EH
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(std::wstring shader);
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void SetVertexData(float vertexdata[18])
		{
			for (int i = 0;i < 18;i++)
			{
				vertexData[i] = vertexdata[i];
			}
		}

		float* GetVertexData() { return vertexData; }

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

		float vertexData[18];
		UINT mTest;
	};
}


