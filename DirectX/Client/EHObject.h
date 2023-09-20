#pragma once
#include "Commoninclude.h"

namespace EH::Object
{
	template <typename T>
	T* Instantiate()
	{
		T* obj = new T();

		return obj;
	}
}
