#include "EHScene.h"

namespace EH
{
	Scene::Scene()
	{
		mLayers.resize((UINT)enums::eLayerType::End);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
}