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

		void Resize(bool resize) { mGlobal_windowDidResize = resize; }

	private:
		HWND mHwnd;

		bool mGlobal_windowDidResize;

		std::vector<class GameObject*> mGameObjects;
	};
}


