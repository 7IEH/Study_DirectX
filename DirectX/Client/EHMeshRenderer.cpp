#include "EHMeshRenderer.h"

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
		mShader->Update();
		mMesh->Render();
	}
}