#include "EHLayer.h"

namespace EH
{
	Layer::Layer()
		:
		mGameObjects{}
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->FixedUpdate();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Update();
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Render();
		}

		/*std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (;iter != mGameObjects.end();)
		{
			if ((*iter)->GetState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		*/
	}
}