#pragma once

#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHGameObject.h"
#include "EHLayer.h"

namespace EH
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetLayer(enums::eLayerType type, GameObject* obj)
		{
			mLayers[(UINT)type].SetObject(obj);
		}

		Layer& GetLayer(enums::eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<Layer> mLayers;
	};
}


