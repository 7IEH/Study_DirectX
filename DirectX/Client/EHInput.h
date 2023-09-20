#pragma once

#include "Commoninclude.h"

namespace EH 
{
	enum class eKeyState
	{
		  DOWN
		, UP
		, PRESSED
		, NONE
	};

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		UP, DOWN, LEFT, RIGHT,
		MouseRightClick, MouseLeftClick, MouseWheelClick,
		Space, Tap,
		END,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool bPressed;
		};
		static void Initialize();
		static void Update();

		__forceinline static bool GetkeyDown(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::DOWN; }
		__forceinline static bool GetkeyUp(eKeyCode code) { return mKeys[(UINT)code].state == eKeyState::UP; }
		__forceinline static Key Getkey(eKeyCode code) { return mKeys[(UINT)code]; }

	private:
		static std::vector<Key> mKeys;
	};
}


