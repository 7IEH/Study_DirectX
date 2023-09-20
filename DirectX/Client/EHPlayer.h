#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:

	};
}


