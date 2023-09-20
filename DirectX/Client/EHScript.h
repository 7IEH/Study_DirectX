#pragma once

#include "EHComponent.h"

namespace EH
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	private:
	};
}

