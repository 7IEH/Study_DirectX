#include "EHGameObject.h"
#include "EHD3D.h"
#include "EHObject.h"
#include "EHApplication.h"
#include "EHBullet.h"

extern EH::Application application;

namespace EH
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		/*GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout);
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVertexShader, nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPixelShader, nullptr, 0);*/
	}

	void GameObject::Render()
	{
		// 정점 버퍼를 IA 파이프라인 단계에 할당합니다.
		// 1. StartSlot : IA에 할당하기 위한 inputslot에 시작 위치를 지정해줍니다.
		// 2. NumBuffers : 입력 슬롯에 
		// 3. ppVertexBufffers : 정점들이 담겨 있는 버퍼의 시작 주소
		// 4. pStrides : stride 배열의 시작 위치. 즉, 버퍼 안에 하나의 정점를 구분하는 크기
		// 5. pOffsets : offset 배열의 시작 위치. 버퍼안에 정점의 시작 위치에 offset 크기

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		//GetDevice()->GetGPUContext().Get()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mStride, &mOffset);

		//// 1. VertexCount : 그릴 정점의 수
		//// 2. StartVertexLocation : 정점 버퍼의 첫번째 인덱스

		//GetDevice()->GetGPUContext().Get()->Draw(mNumVerts, 0);
	}
}