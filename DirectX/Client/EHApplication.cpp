#include "EHApplication.h"
#include "EHGameObject.h"
#include "EHD3D.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHTrasnform.h"

namespace EH
{
	Application::Application()
		:
		  mHwnd(nullptr)
		, mGlobal_windowDidResize(false)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;

		// DirectX Initialize
		D3D::Initialize(hWnd);

		Player* object = Object::Instantiate<Player>(L"shaders.hlsl");
		object->GetComponent<Transform>()->SetPosition(Math::Vector3(0.f, 0.f, 0.f));
		object->GetComponent<Transform>()->SetScale(Math::Vector3(0.1f, 0.1f, 0.1f));

		float tempdata[18] =
		{
			0.f , 0.f, 0.f, 0.f, 1.f, 1.f,
			0.f , 0.f, 1.f, 1.f, 0.f, 1.f,
			0.f , 0.f, 0.f, 0.f, 1.f, 1.f
		};
		object->SetVertexData(tempdata);
		mGameObjects.push_back(object);

		/*object = Object::Instantiate<GameObject>(L"shaders.hlsl");
		float tempdata2[18] =
		{
			 0.0f - 0.5f,  0.5f, 0.f, 1.f, 0.f, 1.f,
			0.5f - 0.5f,  -0.5f, 1.f, 0.f, 0.f, 1.f,
			-0.5f - 0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f
		};
		object->SetVertexData(tempdata2);
		mGameObjects.push_back(object);	*/
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		std::vector<class GameObject*> objects = mGameObjects;
		std::vector<GameObject*>::iterator iter = objects.begin();

		for (;iter != objects.end();iter++)
		{
			(*iter)->Update();
		}
	}

	void Application::Render()
	{

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

		if (mGlobal_windowDidResize)
		{
			D3D::GetD3DDeviceContext()->OMSetRenderTargets(0, 0, 0);
			D3D::GetD3DView()->Release();

			HRESULT res = D3D::GetSwapChain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(res));

			ID3D11Texture2D* d3d11FrameBuffer;
		
			res = D3D::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(res));

		
			ID3D11RenderTargetView* temp;
			res = D3D::GetD3DDevice()->CreateRenderTargetView(d3d11FrameBuffer, NULL, &temp);
			D3D::SetD3DView(temp);

			assert(SUCCEEDED(res));
			d3d11FrameBuffer->Release();

			mGlobal_windowDidResize = false;
		}


		// ���� view�� rendertarget�� ColorRGBA�Ű������� ����� ��ȯ�մϴ�.

		FLOAT backgroundColor[4] = { 1.f,1.f,1.f,1.f };

		D3D::GetD3DDeviceContext()->ClearRenderTargetView(
			D3D::GetD3DView(),
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

		D3D::GetD3DDeviceContext()->RSSetViewports(1, &viewport);

		// ���� Ÿ�� �並 Output merger�� �Ѵ�.
		// 1. NumViews : ���� Ÿ���� ��
		// 2. ppRenderTargetViews : ���� Ÿ���� ����Ű�� view ��ü
		// 3. ���� �׽�Ʈ�� ����ϴ� ����

		ID3D11RenderTargetView* temp = D3D::GetD3DView();
		D3D::GetD3DDeviceContext()->OMSetRenderTargets(1, &temp, nullptr);
		D3D::SetD3DView(temp);
	

		std::vector<GameObject*>::iterator iter = mGameObjects.begin();
		for (;iter != mGameObjects.end();iter++)
		{
			(*iter)->Render();
		}

		// ����ۿ� ���������̹����� �����ݴϴ�.

		D3D::GetSwapChain()->Present(1, 0);
	}
}
