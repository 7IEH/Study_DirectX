#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Player : public GameObject
	{
	public:
		Player(std::wstring shader);
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:

	};
}


