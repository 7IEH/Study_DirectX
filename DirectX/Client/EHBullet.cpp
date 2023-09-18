#include "EHBullet.h"

namespace EH
{
	Bullet::Bullet(std::wstring shader)
		: GameObject(shader)
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
	}

	void Bullet::Update()
	{
		GameObject::Update();
		float* vertexdata = GetVertexData();
		vertexdata[1] += 0.03f;
		vertexdata[7] += 0.03f;
		vertexdata[13] += 0.03f;

		SetVertexData(vertexdata);
	}

	void Bullet::Render()
	{
		GameObject::Render();
	}
}