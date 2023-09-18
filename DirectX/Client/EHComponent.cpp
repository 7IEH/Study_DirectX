#include "EHComponent.h"

namespace EH
{
	Component::Component(enums::eCommponentType type)
		:
		  mOwner(nullptr)
		, mType(type)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
	}

	void Component::Update()
	{
	}

	void Component::Render()
	{
	}
}