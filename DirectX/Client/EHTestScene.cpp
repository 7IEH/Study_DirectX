#include "EHTestScene.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHMeshRenderer.h"
#include "EHResources.h"

namespace EH 
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		GameObject* testobject = Object::Instantiate<GameObject>(enums::eLayerType::Player);
		MeshRenderer* temp = testobject->AddComponent<MeshRenderer>();
		temp->SetMash(Resources::Find<Mesh>(L"TriangleMesh"));
		temp->SetShader(Resources::Find<Shader>(L"TriangleShader"));
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}
}