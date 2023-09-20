#pragma once

#include "EHScene.h"

namespace EH
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:

	};
}


