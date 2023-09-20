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
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}