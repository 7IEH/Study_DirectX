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
		// ���� ���۸� IA ���������� �ܰ迡 �Ҵ��մϴ�.
		// 1. StartSlot : IA�� �Ҵ��ϱ� ���� inputslot�� ���� ��ġ�� �������ݴϴ�.
		// 2. NumBuffers : �Է� ���Կ� 
		// 3. ppVertexBufffers : �������� ��� �ִ� ������ ���� �ּ�
		// 4. pStrides : stride �迭�� ���� ��ġ. ��, ���� �ȿ� �ϳ��� ������ �����ϴ� ũ��
		// 5. pOffsets : offset �迭�� ���� ��ġ. ���۾ȿ� ������ ���� ��ġ�� offset ũ��

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		//GetDevice()->GetGPUContext().Get()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mStride, &mOffset);

		//// 1. VertexCount : �׸� ������ ��
		//// 2. StartVertexLocation : ���� ������ ù��° �ε���

		//GetDevice()->GetGPUContext().Get()->Draw(mNumVerts, 0);
	}
}