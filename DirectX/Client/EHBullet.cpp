#include "EHBullet.h"
#include "EHTrasnform.h"
#include "EHTime.h"
#include "EHGameObject.h"

namespace EH
{
	Bullet::Bullet()
		: 
		mDir(Math::Vector2(0.f,1.f))
		,mSpeed(1.f)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Math::Vector3 pos = tr->GetPosition();
		pos.x += mDir.x * mSpeed * Time::GetDeltaTime();
		pos.y += mDir.y * mSpeed * Time::GetDeltaTime();

		tr->SetPosition(pos);
	}

	void Bullet::FixedUpdate()
	{

	}

	void Bullet::Render()
	{
		
	}
}