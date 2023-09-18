#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHApplication.h"

extern EH::Application application;

namespace EH
{
	Player::Player(std::wstring shader)
		:GameObject(shader)
	{

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
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			vertexData[0] -= 0.01f;
			vertexData[6] -= 0.01f;
			vertexData[12] -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			vertexData[0] += 0.01f;
			vertexData[6] += 0.01f;
			vertexData[12] += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			vertexData[1] += 0.01f;
			vertexData[7] += 0.01f;
			vertexData[13] += 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			vertexData[1] -= 0.01f;
			vertexData[7] -= 0.01f;
			vertexData[13] -= 0.01f;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			Bullet* object = new Bullet(L"shaders.hlsl");
			float tempdata[18] = {};
			for (size_t i = 0; i < 18; i++)
			{
				tempdata[i] = vertexData[i];
			}

			tempdata[0] /= 3.f;
			tempdata[1] /= 3.f;
			tempdata[6] /= 3.f;
			tempdata[7] /= 3.f;
			tempdata[12] /= 3.f;
			tempdata[13] /= 3.f;

			object->SetVertexData(tempdata);
			application.AddObject(object);
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			vertexData[0] *= 1.01f;
			vertexData[1] *= 1.01f;
			vertexData[6] *= 1.01f;
			vertexData[7] *= 1.01f;
			vertexData[12] *= 1.01f;
			vertexData[13] *= 1.01f;
		}

		if (GetAsyncKeyState('E') & 0x8000)
		{
			vertexData[0] /= 1.01f;
			vertexData[1] /= 1.01f;
			vertexData[6] /= 1.01f;
			vertexData[7] /= 1.01f;
			vertexData[12] /= 1.01f;
			vertexData[13] /= 1.01f;
		}

	}

	void Player::Render()
	{
		GameObject::Render();
	}

}