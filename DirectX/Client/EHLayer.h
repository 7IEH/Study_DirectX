#pragma once

#include "EHEntity.h"
#include "EHGameObject.h"

namespace EH
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void Render();

		void SetObject(GameObject* obj)
		{
			mGameObjects.push_back(obj);
		}

		std::vector<GameObject*>& GetObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;

	};
}


