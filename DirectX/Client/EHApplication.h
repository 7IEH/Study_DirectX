#pragma once

#include "Commoninclude.h"

namespace EH
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;

		static bool global_windowDidResize;

		std::vector<class GameObject*> mGameObjects;
	};
}


