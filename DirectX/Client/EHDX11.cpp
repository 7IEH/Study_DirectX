#include "EHDX11.h"

namespace EH 
{

	ID3D11Device1* DX11::mD3d11Device;
	ID3D11DeviceContext1* DX11::mD3d11DeviceContext;
	ID3D11RenderTargetView* DX11::mD3d11FrameBufferView;
	IDXGISwapChain1* DX11::mD3d11SwapChain;

	void DX11::Initialize(HWND hWnd)
	{
		// Device and Device Context Create
		{
			ID3D11Device* baseDevice;
			ID3D11DeviceContext* baseDeviceContext;
			D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
			UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

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
			HRESULT hResult = D3D11CreateDevice(0
				, D3D_DRIVER_TYPE_HARDWARE
				, 0
				, creationFlags
				, featureLevels
				, ARRAYSIZE(featureLevels)
				, D3D11_SDK_VERSION
				, &baseDevice
				, 0
				, &baseDeviceContext);

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
			hResult = baseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&mD3d11Device);
			assert(SUCCEEDED(hResult));
			// ���� �ʿ���� baseDevice�� �Ҵ��� �������ش�.
			baseDevice->Release();

			hResult = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&mD3d11DeviceContext);
			assert(SUCCEEDED(hResult));
			baseDeviceContext->Release();

			// -> �̷μ� device�� devicecontext�� �����Ϸ�

		}

		// SwapChain Create
		{
			IDXGIFactory2* dxgiFactory;
			{
				IDXGIDevice1* dxgiDevice;
				HRESULT hResult = mD3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
				assert(SUCCEEDED(hResult));

				IDXGIAdapter* dxgiAdapter;
				hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
				assert(SUCCEEDED(hResult));
				dxgiDevice->Release();

				DXGI_ADAPTER_DESC adapterDesc;
				dxgiAdapter->GetDesc(&adapterDesc);

				OutputDebugStringA("Graphics Device: ");
				OutputDebugStringW(adapterDesc.Description);

				hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
				assert(SUCCEEDED(hResult));
				dxgiAdapter->Release();
			}

			DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
			d3d11SwapChainDesc.Width = 0;
			d3d11SwapChainDesc.Height = 0;
			d3d11SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
			d3d11SwapChainDesc.SampleDesc.Count = 1;
			d3d11SwapChainDesc.SampleDesc.Quality = 0;
			d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			d3d11SwapChainDesc.BufferCount = 2;
			d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
			d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			d3d11SwapChainDesc.Flags = 0;

			HRESULT hResult = dxgiFactory->CreateSwapChainForHwnd(
				  mD3d11Device
				, hWnd
				, &d3d11SwapChainDesc
				, 0
				, 0
				, &mD3d11SwapChain);
			assert(SUCCEEDED(hResult));

			dxgiFactory->Release();
		}

		// FrameBuffer Render Target -> �׷��� ��ġ���� �׷��� bitmap ����
		// view�� �� bitmap�� ������ �� �ִ� COM
		{
			ID3D11Texture2D* d3d11FrameBuffer;
			HRESULT hResult = mD3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(hResult));

			hResult = mD3d11Device->CreateRenderTargetView(d3d11FrameBuffer, 0, &mD3d11FrameBufferView);
			assert(SUCCEEDED(hResult));
			d3d11FrameBuffer->Release();
		}
	}

	void DX11::Update()
	{

	}

	void DX11::Render()
	{

	}
}