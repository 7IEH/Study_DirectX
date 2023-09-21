#pragma once
#include "Commoninclude.h"
#include "EHScript.h"

namespace EH
{
	class Bullet : public Script
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetSpeed(float speed) { mSpeed = speed; }
		void SetDir(Math::Vector2 dir) { mDir = dir; }

	private:
		Math::Vector2 mDir;
		float mSpeed;
	};
}


