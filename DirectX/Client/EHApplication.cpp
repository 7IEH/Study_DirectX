#include "EHApplication.h"
#include "EHGameObject.h"
#include "EHDX11.h"
#include "EHObject.h"

namespace EH
{
	bool Application::global_windowDidResize = false;

	Application::Application()
		:mHwnd(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		DX11::Initialize(hWnd);

		GameObject* object = Object::Instantiate<GameObject>(L"shaders.hlsl");
		float tempdata[18] =
		{
			 0.0f + 0.2f,  0.5f, 0.f, 1.f, 0.f, 1.f,
			 0.5f + 0.2f,  -0.5f, 1.f, 1.f, 0.f, 1.f,
			-0.5f + 0.2f, -0.5f, 0.f, 0.f, 1.f, 1.f
		};
		object->SetVertexData(tempdata);
		mGameObjects.push_back(object);

		object = Object::Instantiate<GameObject>(L"shaders.hlsl");
		float tempdata2[18] =
		{
			 0.0f - 0.2f,  0.5f, 0.f, 1.f, 0.f, 1.f,
			0.5f - 0.2f,  -0.5f, 1.f, 0.f, 0.f, 1.f,
			-0.5f - 0.2f, -0.5f, 0.f, 0.f, 1.f, 1.f
		};
		object->SetVertexData(tempdata2);
		mGameObjects.push_back(object);
		
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (;iter != mGameObjects.end();iter++)
		{
			(*iter)->Update();
		}
	}

	void Application::Render()
	{
		if (global_windowDidResize)
		{
			DX11::GetD3DDeviceContext()->OMSetRenderTargets(0, 0, 0);
			DX11::GetD3DView()->Release();

			HRESULT res = DX11::GetSwapChain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(res));

			ID3D11Texture2D* d3d11FrameBuffer;
			res = DX11::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(res));

			ID3D11RenderTargetView* temp;

			res = DX11::GetD3DDevice()->CreateRenderTargetView(d3d11FrameBuffer, NULL, &temp);
			DX11::SetD3DView(temp);
			assert(SUCCEEDED(res));
			d3d11FrameBuffer->Release();

			global_windowDidResize = false;
		}

		FLOAT backgroundColor[4] = { 1.f,1.f,1.f,1.f };

		DX11::GetD3DDeviceContext()->ClearRenderTargetView(
			DX11::GetD3DView(),
			backgroundColor);


		RECT winRect = {};
		GetClientRect(mHwnd, &winRect);
		D3D11_VIEWPORT viewport = { 0.f,0.f,(FLOAT)(winRect.right - winRect.left)
		,(FLOAT)(winRect.bottom - winRect.top),0.f,1.f };
		DX11::GetD3DDeviceContext()->RSSetViewports(1, &viewport);


		ID3D11RenderTargetView* temp = DX11::GetD3DView();
		DX11::GetD3DDeviceContext()->OMSetRenderTargets(1, &temp, nullptr);
		DX11::SetD3DView(temp);
	
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (;iter != mGameObjects.end();iter++)
		{
			(*iter)->Render();
		}

		DX11::GetSwapChain()->Present(1, 0);
	}
}
