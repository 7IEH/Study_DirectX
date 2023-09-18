#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	class Bullet : public GameObject
	{
	public:
		Bullet(std::wstring shader);
		virtual ~Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:
		float mSpeed;
		float mDir;
	};
}


