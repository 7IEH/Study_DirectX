#pragma once
#include "EHScript.h"

namespace EH
{
	class Player : public Script
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:

	};
}


