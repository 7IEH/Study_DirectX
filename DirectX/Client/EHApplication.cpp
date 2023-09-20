#include "EHApplication.h"
#include "EHGameObject.h"
#include "EHD3D.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHTrasnform.h"
#include "EHRenderer.h"
#include "EHTime.h"
#include "EHInput.h"
#include "EHMeshRenderer.h"
#include "EHResources.h"
#include "EHSceneManager.h"

namespace EH
{
	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mGlobal_windowDidResize = false;
		mHwnd = hWnd;
		Time::Initialize();
		Input::Initialize();
		// DirectX Initialize
		mGraphicsDevice = std::make_unique<D3D>();
		GetDevice() = mGraphicsDevice.get();

		renderer::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::FixedUpdate()
	{
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render();
		// DC�� ������ rendertarget�� ���õ� ���뿡 ���� reset ��ŵ�ϴ�.

			// DXGI_SWAP_CHAIN_DESC1�� ���� ������ buffer�� �ɼ���
			// ���� ������¡ ���ݴϴ�.
			// 1. buffercount : ������ ���� ��� 0���� ����
			// 2. width : 0���� ������ ���� Ŭ���̾�Ʈ�� �ʺ� �����ɴϴ�.
			// 3. height : 0���� ������ ���� Ŭ���̾�Ʈ�� ���̸� �����ɴϴ�.
			// 4. newformat : ������� ���� ������ �����Ϸ��� DXGI_FORMAT_UNKNOWN �� ����մϴ�.
			// 5. SwapChainFlags : ���� ü�� ���ۿ� ���� �ɼ��� �����մϴ�.

			// swapchain�� �� ����۸� ����ŵ�ϴ�.

			// �� �� ���۸� ��������ϴ� view ��ü�� �����մϴ�.
			// ������ �Ű� ������ ���� ������ view ��ü�� ��ȯ �޽��ϴ�.

		// -> resizing �� rendertarget�� ������ �ȴ�.

		/*if (mGlobal_windowDidResize)
		{
			GetDevice()->GetGPUContext().Get()->OMSetRenderTargets(0, 0, 0);
			GetDevice()->GetView().Get()->Release();

			HRESULT res = GetDevice()->GetSwapChain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(res));

			ID3D11Texture2D* d3d11FrameBuffer;
		
			res = GetDevice()->GetSwapChain().Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(res));

		
			ID3D11RenderTargetView* temp;
			res = GetDevice()->GetGPUDevice().Get()->CreateRenderTargetView(d3d11FrameBuffer, NULL, &temp);
			GetDevice()->SetView(temp);

			assert(SUCCEEDED(res));
			d3d11FrameBuffer->Release();

			mGlobal_windowDidResize = false;
		}*/


		// ���� view�� rendertarget�� ColorRGBA�Ű������� ����� ��ȯ�մϴ�.

		FLOAT backgroundColor[4] = { 1.f,1.f,1.f,1.f };

		GetDevice()->GetGPUContext().Get()->ClearRenderTargetView(
			GetDevice()->GetView().Get(),
			backgroundColor);

		RECT winRect = {};
		GetClientRect(mHwnd, &winRect);
		D3D11_VIEWPORT viewport = { 0.f,0.f,(FLOAT)(winRect.right - winRect.left)
		,(FLOAT)(winRect.bottom - winRect.top),0.f,1.f };

		// ���� �� ������ ���ϴ� ���̶� �����ϸ� �˴ϴ�.
		// 1. TopLeftX : ����Ʈ�� ������ x��ġ
		// 2. TopLeftY : ����Ʈ�� ������ y��ġ
		// 3. Width : ����Ʈ�� �ʺ�
		// 4. Height : ����Ʈ�� ����
		// 5. MinDepth : �ּ� ���� 0~1 ������ ����
		// 6. MaxDepth : �ִ� ���� 0~1 ������ ����

		// �ش� ����Ʈ�� Rasterization �ܰ迡 �Ҵ��մϴ�.
		// 1. NumViewports : ������ ����Ʈ�� ����
		// 2. pViewports : ������ ����Ʈ �ּ�

		GetDevice()->GetGPUContext().Get()->RSSetViewports(1, &viewport);

		// ���� Ÿ�� �並 Output merger�� �Ѵ�.
		// 1. NumViews : ���� Ÿ���� ��
		// 2. ppRenderTargetViews : ���� Ÿ���� ����Ű�� view ��ü
		// 3. ���� �׽�Ʈ�� ����ϴ� ����

		ID3D11RenderTargetView* temp = GetDevice()->GetView().Get();
		GetDevice()->GetGPUContext().Get()->OMSetRenderTargets(1, &temp, nullptr);
		GetDevice()->SetView(temp);
	
		SceneManager::Render();


		// ����ۿ� ���������̹����� �����ݴϴ�.

		GetDevice()->GetSwapChain()->Present(1, 0);
	}
}
