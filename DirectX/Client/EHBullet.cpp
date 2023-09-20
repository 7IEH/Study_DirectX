#include "EHBullet.h"
#include "EHTrasnform.h"

namespace EH
{
	Bullet::Bullet()
		: 
		mRadian(90*(3.14f/180.f))
	{
		AddComponent<Transform>();
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
		Transform* tr = GetComponent<Transform>();
		Math::Vector3 pos = tr->GetPosition();
		pos.x += cosf(mRadian) * 0.01f;
		pos.y += sinf(mRadian) * 0.01f;
		//tr->SetDegree(mRadian * 180.f / 3.14f);
		//float degree = mRadian * 180.f / 3.14f;
		tr->SetPosition(pos);
	}

	void Bullet::Render()
	{
		GameObject::Render();
	}
}