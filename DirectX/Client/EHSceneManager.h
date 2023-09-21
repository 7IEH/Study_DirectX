#pragma once

#include "EHScene.h"

namespace EH
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void FixedUpdate();
		static void Update();
		static void Render();
		static void Release();

		template <typename T>
		static T* CreateScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			T* scene = nullptr;

			if (iter != mScenes.end())
			{
				scene = dynamic_cast<T*>(iter->second);
			}
			else
			{
				scene = new T();
				scene->SetName(name);
				mScenes.insert(std::make_pair(name, scene));
				mCurScene = scene;
				scene->Initialize();
			}
			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetCurScene() { return mCurScene; }

	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mCurScene;
	};
}


