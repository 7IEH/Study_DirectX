#pragma once
#include "EHComponent.h"
#include "Commoninclude.h"

namespace EH
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetPosition(Math::Vector3 position) { mPosition = position; }
		Math::Vector3 GetPosition() { return mPosition; }

		void SetScale(Math::Vector3 scale) { mScale = scale; }
		Math::Vector3 GetScale() { return mScale; }

	private:
		Math::Vector3 mPosition;
		Math::Vector3 mScale;
	};
}


