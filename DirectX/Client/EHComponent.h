#pragma once
#include "Commoninclude.h"

namespace EH
{
	class Component
	{
	public:
		Component(enums::eCommponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void Render();

		void SetOwenr(class GameObject* owner) { mOwner = owner; }
		class GameObject* GetOwner() { return  mOwner; }

	private:
		class GameObject* mOwner;
		enums::eCommponentType mType;
	};
}


