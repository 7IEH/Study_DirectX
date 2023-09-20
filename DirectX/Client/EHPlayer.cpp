#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHApplication.h"
#include "EHTrasnform.h"
#include "EHInput.h"
#include "EHTime.h"

extern EH::Application application;

namespace EH
{
	Player::Player()
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
		Math::Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
		{
			pos.y += 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			pos.y -= 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			pos.x -= 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			pos.x += 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}
	}

	void Player::FixedUpdate()
	{
		
	}

	void Player::Render()
	{
	
	}

}