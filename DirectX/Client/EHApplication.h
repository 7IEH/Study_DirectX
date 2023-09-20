#pragma once

#include "Commoninclude.h"
#include "EHD3D.h"

namespace EH
{
	class Application
	{
	public:
		~Application();

		void Initialize(HWND);
		void Run();
		void Update();
		void Render();

		void Resize(bool resize) { mGlobal_windowDidResize = resize; }

		void AddObject(class GameObject* object) { mGameObjects.push_back(object); }

		HWND GetHWND() { return mHwnd; }

	private:
		HWND mHwnd;

		bool mGlobal_windowDidResize;

		std::vector<class GameObject*> mGameObjects;

		std::unique_ptr<EH::D3D> mGraphicsDevice;
	};
}


