#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void SetSpeed(float speed) { mSpeed = speed; }
		void SetRadian(float radian) { mRadian = radian; }

	private:
		float mSpeed;
		float mRadian;
	};
}


