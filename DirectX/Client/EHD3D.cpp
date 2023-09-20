#include "EHD3D.h"
#include "EHApplication.h"

extern EH::Application application;

namespace EH
{
	D3D::D3D()
	{
		// Device and Device Context Create
		{
			D3D_FEATURE_LEVEL featureLevels = (D3D_FEATURE_LEVEL)0;
			UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;

			// D3D11CreateDevice Parameter
			// 1. pAdapter : ������ �׷��� �����(GPU�� ����)(0 or NULL ���� �⺻ ��ġ�� ����) 
			// 2. DriverType : �� �׷��� ������� ������ ���� ���� GPU�� ����ϴ� �ϵ��� ����Ʈ
			// �ٸ� �ɼ��� ���� ���� �����
			// 3. Software : �Ʊ�� ���������� hardware�� ����ϴ� 0�� �־��� 2�� �μ��� software�� ����ϰڴ�
			// ����ÿ��� NULL ���� ������ �ȵ�
			// 4. Flags : �߰����� ��ġ ���� �÷��׵��Դϴ�. debug �ÿ��� D3D11_CREATE_DEVICE_DEBUG���
			// D3D11_CREATE_DEVICE_BGRA_SUPPORT ���� ��� Direct3D ���ҽ����� Direct2D ��ȣ ��뼺�� �ʿ��մϴ�
			// 5. *pFeatureLevels : ��, �� ��ġ�� �����ϴ� ������ �����ϴ� ����Դϴ�. �ּ� ������ �����
			// 6. FeatureLevels : ���� ��ġ�� �����ϴ� ��� ���ص��� ������ �迭�� ũ�⸦ ������
			// 7. SDKVersion : ����� SDK ������ �Է��մϴ�.
			// 8. **ppDevice : ���� device ��ġ�� ��ȯ�մϴ�.
			// 9. *pFeatureLevel : ���� feature ������ �����Ѵٸ� �� ��� ù��° ������ ��ȯ�մϴ�.
			// 10. *ppImmdiateContext : ���� ����̽� ���ؽ�Ʈ ��ü�� ��ȯ�մϴ�.

			HRESULT hResult = D3D11CreateDevice(nullptr
				, D3D_DRIVER_TYPE_HARDWARE
				, nullptr
				, creationFlags
				, nullptr
				, 0
				, D3D11_SDK_VERSION
				, mDevice.GetAddressOf()
				, &featureLevels
				, mContext.GetAddressOf());

			if (FAILED(hResult))
			{
				MessageBoxA(0, "D3D11CreativeDevice() failed", "fatal Error", MB_OK);
			}

			// COM(Component Object Model) ��ü�� ���������� �ȿ� �ִ°��� �� �� ������ Ư���� �Լ��� ����ؾ���
			// COM ��ü�� �빮�� I�� ����
			// QueryInterface�� �� COM ��ü�ȿ� �ִ°��� �޶���ϴ� �Լ�
			// QueryInterface(���ϴ� ���� ����, ���ϴ� ���� ���� �ٱ���);
			// ������ device���� ID3D11Device1 ��ü�� ������
			// ID3D11Device1�� ��� ���ؼ��� ID3D11Device�� ���� �����ؾ���
			// ����������, ID3D11DeviceContext1�� ������ؼ��� ID3D11DeviceContext�� ���� �����ؾ���

			//hResult = baseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&mD3d11Device);
			//assert(SUCCEEDED(hResult));
			//// ���� �ʿ���� baseDevice�� �Ҵ��� �������ش�.
			//baseDevice->Release();

			//hResult = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&mD3d11DeviceContext);
			//assert(SUCCEEDED(hResult));
			//baseDeviceContext->Release();

			// -> �̷μ� device�� devicecontext�� �����Ϸ�

		}

		if (!CreateSwapChain(application.GetHWND()))
		{
			MessageBoxA(0, "D3D11CreativeSwapChain() failed", "fatal Error", MB_OK);
		}

		// FrameBuffer Render Target -> �׷��� ��ġ���� �׷��� bitmap ����
		// view�� �� bitmap�� ������ �� �ִ� COM��ü�̴�.
		// �� bitmap�� �ʿ��ϱ⿡ �����ϱ� ���� view��ü�� �������ݴϴ�.
		{
			HRESULT hResult = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mFrameBuffer.GetAddressOf());
			assert(SUCCEEDED(hResult));

			// swapchain�� ����� �� �ϳ��� �����ϱ� ���� �Լ�
			hResult = mDevice->CreateRenderTargetView(mFrameBuffer.Get(), 0, mRenderTargetView.GetAddressOf());
			assert(SUCCEEDED(hResult));

			// �� �� ���۸� ��������ϴ� view ��ü�� �����մϴ�.
			// ������ �Ű� ������ ���� ������ view ��ü�� ��ȯ �޽��ϴ�.
		}
	}
	D3D::~D3D()
	{
	}

	bool D3D::CreateSwapChain(HWND hWnd)
	{
		// SwapChain Create
		{
			// ��ü ȭ�� ��ȯ�� ó���ϴ� DXGI ��ü�� �����ϴ� �޼��带 �����ϴ� ��
			/*DXGI �� DirectX �׷��� ��Ÿ�ӿ� �������� �������� �۾��� �����Ѵ�.

				�⺻���� �۾���

				-�ϵ���� ����̽��� ����(�׷��� ī�尡 �������� �� �ִ�.)

				- ���÷��� ����� ����

				- �����ġ�� ����(����͸� ���� �� ����� �� �ִ�.)

				- ���� ü�� ����

				- ���������̼�

				- Ǯ��ũ�� ���*/
				// �� �߿� ����ü���� �����ϱ� ���ؼ� DXGI(DirectX Graphics Infrastructure)�� ����ؾ��ϸ�
				// , DXGI �������̽��� ����ϱ� ���ؼ��� DXGI Factory ��ü�� �����ؾ��Ѵ�.
			Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory = nullptr;
			Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
			Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
			// DXGI Interface ���� COM ��ü �̱⶧���� �����ϱ� ���ؼ��� QueryInterface�� �ʿ��մϴ�. 
			// ���� �Ҵ�� device ������ Ȱ���� dxgi �������̽� device�� ���� �Ҵ��մϴ�. 

			HRESULT hResult = mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)dxgiDevice.GetAddressOf());
			assert(SUCCEEDED(hResult));

			// ���� ����� GPU�� ���� ������ DEBUG ������ ǥ���� �� ǥ���ϱ� ����
			// adapter ��ü�� �����մϴ�.
			hResult = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)dxgiAdapter.GetAddressOf());
			assert(SUCCEEDED(hResult));
			dxgiDevice->Release();

			DXGI_ADAPTER_DESC adapterDesc;
			dxgiAdapter->GetDesc(&adapterDesc);

			OutputDebugStringA("Graphics Device: ");
			OutputDebugStringW(adapterDesc.Description);

			// DXGIAdapter�� DXGIObject�� ��� �޴� ��ü�� �ش� DXGIobject ��ü�� Ȱ����
			// dxgifactory2 �������̽��� �����մϴ�.
			hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf());
			assert(SUCCEEDED(hResult));
			dxgiAdapter->Release();


			// ���� DXGIFactory�� Ȱ���� swapchain�� �����ϱ� ����
			// swapchain�� option�� �������ݴϴ�.
			// 1. Width : ���� �ػ��� �ʺ� ���մϴ�. 0���� �����ÿ� ��Ÿ�ӿ��� ���� �ػ��� �ʺ� �����ɴϴ�.
			// 2. Height : ���� �ػ��� ���̸� ���մϴ�. 0���� �����ÿ� ��Ÿ�ӿ��� ���� �ػ��� ���̸� �����ɴϴ�.
			// 3. Format : ǥ�� ������ �����ϴ� DXGI_FORMAT ����ü�Դϴ�. DXGI_FORMAT_B8G8R8A8_UNORM_SRGB ��: 91
			// ���ĸ� �����Ͽ� �� ä�ο� ���� 8��Ʈ�� �����ϴ� 4�� ���� ����� 32��Ʈ ��ȣ ���� ����ȭ�� ǥ�� RGB �����Դϴ�.
			// 4. sampleDesc ��ü�� Count : �ȼ��� ��Ƽ���� ��, ��Ƽ�ٸ���̿� ���� �ɼ��Դϴ�. ���� �������� �� �ڿ� ������ ��� ���Դϴ�.
			// 5. sampleDesc ��ü�� Quality : �̹��� ǰ�� �������� ���� �������� ������ �������ϴ�. (0~1)
			// 6. BufferUsage : ǥ�� �� ���ҽ� ����� �ɼǿ� ���� �÷����Դϴ�. DXGI_USAGE_RENDER_TARGET_OUTPUT ǥ�� �Ǵ� ���ҽ��� ��� ������ ������� ����մϴ�.
			// 7. buffercount : ��, ��ü�ϴ� ȭ����� ���� ��Ÿ���ϴ�.
			// 8. Scaling : �� ������ �ػ󵵰� ��� �Ϸ��� �ػ󵵿� ���� ���� ��� ũ�⸦ ��� ������ ���� �޴���.
			// 9. SwapEffect : ����� ����۸� ��� ������ ���� �޴���
			// 10. AlphaMode : �� ������ alpha���� �����մϴ�.
			// 11. Flags : ���� ü�� �ɼ� ��

			DXGI_SWAP_CHAIN_DESC d3d11SwapChainDesc = {};
			d3d11SwapChainDesc.OutputWindow = application.GetHWND();	                // Front Buffer �� ��½�ų ������ �ڵ�
			d3d11SwapChainDesc.Windowed = true;		                // ������, ��üȭ�� ���
			d3d11SwapChainDesc.BufferCount = 2;
			d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // ���� ������ ����� �������� �ʴ´�.

			d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			d3d11SwapChainDesc.BufferDesc.Width = 1600;
			d3d11SwapChainDesc.BufferDesc.Height = 900;
			d3d11SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			d3d11SwapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
			d3d11SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			d3d11SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			d3d11SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

			d3d11SwapChainDesc.SampleDesc.Count = 1;
			d3d11SwapChainDesc.SampleDesc.Quality = 0;
			// Hwnd�� ����� swapchain�� �����ϴ� �Լ�

			// 1. pDevice : ���� devicecontext ��, �׷��ִ� ��ü�� ���� ���� ���Ѿ���
			// 2. hWnd : ������ ������ �ڵ�
			// 3. pDesc : DXGI_SWAP_CHAIN_DESC1 ��, swapchain�� �ɼ� ��
			// 4. pFullScreen : fullscreen�� ���� ���� ü�� �ɼ��̴�. ������� ���� ��� 0���� ǥ��
			// 5. pRestrictToOutput : ���� ü�� ��� ���ѿ� ���� �ɼ��̴�.
			// 6. ppSwapChain : ������ swapchain�� ��ȯ�Ѵ�.

			hResult = dxgiFactory->CreateSwapChain(
				mDevice.Get()
				, &d3d11SwapChainDesc
				, mSwapChain.GetAddressOf());

			// ���� ü���̶� ���� ���α׷��� �� ȭ���� �����ϸ�, �̸� ���� ù ���ۿ� ��ü�ϴ� �۾��� �ǹ��մϴ�.
		// �̸� ������ �Ǵ� �ø����̶��մϴ�.
		// ���� �ص�� ����� ���� ü���� �������ϴ�.
			assert(SUCCEEDED(hResult));

			dxgiFactory->Release();
		}

		return true;
	}

	void D3D::SetConstantBuffer(graphics::ShaderStage stage, enums::CBYTES type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case graphics::ShaderStage::VS:
			{
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		case graphics::ShaderStage::HS:
			{
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		case graphics::ShaderStage::DS:
			{
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		case graphics::ShaderStage::GS:
			{
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		case graphics::ShaderStage::PS:
			{
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		case graphics::ShaderStage::CS:
			{
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			}
			break;
		}
	}
}