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

		void AddObject(class GameObject* object) { mGameObjects.push_back(object); }

	private:
		HWND mHwnd;

		bool mGlobal_windowDidResize;

		std::vector<class GameObject*> mGameObjects;
	};
}


