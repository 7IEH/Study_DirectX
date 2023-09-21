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

		mScript->FixedUpdate();
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		mScript->Update();
		/*GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout);
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVertexShader, nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPixelShader, nullptr, 0);*/
	}

	void GameObject::Render()
	{

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}


		mScript->Render();
	}
}