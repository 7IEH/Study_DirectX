#include "EHApplication.h"
#include "EHDX11.h"

namespace EH
{
	Application::Application()
		:mHwnd(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		DX11::Initialize(hWnd);
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
		FLOAT backgroundColor[4] = { 0.1f,0.2f,0.6f,1.0f };

		DX11::GetD3DDeviceContext()->ClearRenderTargetView(
			DX11::GetD3DView(),
			backgroundColor);


		DX11::GetSwapChain()->Present(1, 0);
	}
}
