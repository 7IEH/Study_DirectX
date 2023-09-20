#include "EHMeshRenderer.h"
#include "EHGameObject.h"

namespace EH
{
	MeshRenderer::MeshRenderer()
		: Component(enums::eCommponentType::MeshRenderer)
	{

	}
	MeshRenderer::~MeshRenderer()
	{

	}
	void MeshRenderer::Initialize()
	{

	}
	void MeshRenderer::FixedUpdate()
	{

	}
	void MeshRenderer::Update()
	{

	}
	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mShader->Update();
		mMesh->Render();
	}
}