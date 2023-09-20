#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHApplication.h"
#include "EHTrasnform.h"

extern EH::Application application;

namespace EH
{
	Player::Player()
	{
		AddComponent<Transform>();
	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		GameObject::Update();

		float* vertexData = GetVertexData();
		Transform* tr = GetComponent<Transform>();
		Math::Vector3 pos = tr->GetPosition();
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			pos.x -= 0.01f;
			tr->SetPosition(pos);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			pos.x += 0.01f;
			tr->SetPosition(pos);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			pos.y += 0.01f;
			tr->SetPosition(pos);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			pos.y -= 0.01f;
			tr->SetPosition(pos);
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			Bullet* object = new Bullet();
			pos.y += 0.1f;
			object->GetComponent<Transform>()->SetPosition(pos);
			object->GetComponent<Transform>()->SetScale(Math::Vector3(0.1f,0.1f,0.1f));
			float tempdata[18] =
			{
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f,
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f,
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f
			};
			object->SetVertexData(tempdata);
			application.AddObject(object);
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			Math::Vector3 scale = tr->GetScale();
			scale.x += 0.001f;
			scale.y += 0.001f;
			scale.z += 0.001f;
			tr->SetScale(scale);
		}

		if (GetAsyncKeyState('E') & 0x8000)
		{
			Math::Vector3 scale = tr->GetScale();
			scale.x -= 0.001f;
			scale.y -= 0.001f;
			scale.z -= 0.001f;
			tr->SetScale(scale);
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);

			float x = (2.f * (float)pt.x / 1600.f) - 1.f;
			float y = (-2.f * (float)pt.y / 900.f) + 1.f;

			float radian = atan2(y - pos.y, x - pos.x);

			Bullet* object = new Bullet();
			pos.y += 0.1f;
			object->GetComponent<Transform>()->SetPosition(pos);
			object->GetComponent<Transform>()->SetScale(Math::Vector3(0.1f, 0.1f, 0.1f));
			object->SetRadian(radian);
			float tempdata[18] =
			{
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f,
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f,
				0.f , 0.f, 0.f, 0.f, 0.f, 1.f
			};
			object->SetVertexData(tempdata);
			application.AddObject(object);
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{

		}
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}