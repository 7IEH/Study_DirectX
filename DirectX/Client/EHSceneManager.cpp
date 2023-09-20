#include "EHSceneManager.h"
#include "EHTestScene.h"

namespace EH
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mCurScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TestScene>(L"TestScene");
		LoadScene(L"TestScene");
	}

	void SceneManager::FixedUpdate()
	{
		mCurScene->FixedUpdate();
	}

	void SceneManager::Update()
	{
		mCurScene->Update();
	}

	void SceneManager::Render()
	{
		mCurScene->Render();
	}

	void SceneManager::Release()
	{
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mCurScene = iter->second;
		return iter->second;
	}
}