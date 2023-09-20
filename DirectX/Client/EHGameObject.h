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

	private:
		std::vector<Component*> mComponents;
	};
}


