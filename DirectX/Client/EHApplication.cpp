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
		// DC에 설정된 rendertarget에 관련된 내용에 대해 reset 시킵니다.

			// DXGI_SWAP_CHAIN_DESC1를 통해 설정한 buffer의 옵션을
			// 전부 리사이징 해줍니다.
			// 1. buffercount : 변동이 없을 경우 0으로 설정
			// 2. width : 0으로 설정시 현재 클라이언트의 너비를 가져옵니다.
			// 3. height : 0으로 설정시 현재 클라이언트의 높이를 가져옵니다.
			// 4. newformat : 백버퍼의 기존 형식을 유지하려면 DXGI_FORMAT_UNKNOWN 를 사용합니다.
			// 5. SwapChainFlags : 스왑 체인 동작에 대한 옵션을 설정합니다.

			// swapchain에 한 백버퍼를 가리킵니다.

			// 그 백 버퍼를 대상으로하는 view 객체를 생성합니다.
			// 마지막 매개 변수를 통해 생성된 view 객체를 반환 받습니다.

		// -> resizing 된 rendertarget을 가지게 된다.

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


		// 현재 view의 rendertarget을 ColorRGBA매개변수의 색깔로 변환합니다.

		FLOAT backgroundColor[4] = { 1.f,1.f,1.f,1.f };

		GetDevice()->GetGPUContext().Get()->ClearRenderTargetView(
			GetDevice()->GetView().Get(),
			backgroundColor);

		RECT winRect = {};
		GetClientRect(mHwnd, &winRect);
		D3D11_VIEWPORT viewport = { 0.f,0.f,(FLOAT)(winRect.right - winRect.left)
		,(FLOAT)(winRect.bottom - winRect.top),0.f,1.f };

		// 내가 볼 영역을 정하는 것이라 생각하면 됩니다.
		// 1. TopLeftX : 뷰포트의 왼쪽의 x위치
		// 2. TopLeftY : 뷰포트의 위쪽의 y위치
		// 3. Width : 뷰포트의 너비
		// 4. Height : 뷰포트의 높이
		// 5. MinDepth : 최소 깊이 0~1 사이의 범위
		// 6. MaxDepth : 최대 깊이 0~1 사이의 범위

		// 해당 뷰포트를 Rasterization 단계에 할당합니다.
		// 1. NumViewports : 적용할 뷰포트의 갯수
		// 2. pViewports : 적용할 뷰포트 주소

		GetDevice()->GetGPUContext().Get()->RSSetViewports(1, &viewport);

		// 렌더 타켓 뷰를 Output merger를 한다.
		// 1. NumViews : 렌더 타겟의 수
		// 2. ppRenderTargetViews : 렌더 타겟을 가리키는 view 객체
		// 3. 깊이 테스트에 사용하는 버퍼

		ID3D11RenderTargetView* temp = GetDevice()->GetView().Get();
		GetDevice()->GetGPUContext().Get()->OMSetRenderTargets(1, &temp, nullptr);
		GetDevice()->SetView(temp);
	
		SceneManager::Render();


		// 백버퍼에 렌더링된이미지를 보여줍니다.

		GetDevice()->GetSwapChain()->Present(1, 0);
	}
}
