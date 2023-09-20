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
		void FixedUpdate();
		void Render();

		void Resize(bool resize) { mGlobal_windowDidResize = resize; }

		HWND GetHWND() { return mHwnd; }

	private:
		HWND mHwnd;
		bool mGlobal_windowDidResize;
		std::unique_ptr<EH::D3D> mGraphicsDevice;
	};
}


