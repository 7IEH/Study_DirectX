#pragma once

#include "Commoninclude.h"

namespace EH
{
	class Time
	{
	public:

		static void Initialize();
		static void Update();
		static void Render();

		__forceinline static float GetDeltaTime() { return mDeltaTime; }

	private:
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;

	};
}


