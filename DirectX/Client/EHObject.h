#pragma once
#include "Commoninclude.h"
#include "EHSceneManager.h"

namespace EH::Object
{
	template <typename T>
	T* Instantiate(enums::eLayerType eType)
	{
		T* obj = new T();
		Scene* curscene = SceneManager::GetCurScene();
		curscene->SetLayer(eType, obj);

		return obj;
	}
}
