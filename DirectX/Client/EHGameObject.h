#pragma once

#include "Commoninclude.h"
#include "EHComponent.h"
#include "EHTrasnform.h"

namespace EH
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void Render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwenr(this);
			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* temp = nullptr;
			for (Component* comp : mComponents)
			{
				temp = dynamic_cast<T*>(comp);
				if (temp != nullptr)
					return temp;
			}
			return temp;
		}

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

		std::vector<Component*> mComponents;
	};
}


