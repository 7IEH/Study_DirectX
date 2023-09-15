#pragma once
#include "Commoninclude.h"

namespace EH::Object
{
	template <typename T>
	T* Instantiate(std::wstring shader)
	{
		T* obj = new T(shader);

		return obj;
	}
}
