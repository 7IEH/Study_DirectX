#include "EHD3D.h"

namespace EH 
{

	ID3D11Device1* D3D::mD3d11Device;
	ID3D11DeviceContext1* D3D::mD3d11DeviceContext;
	ID3D11RenderTargetView* D3D::mD3d11FrameBufferView;
	IDXGISwapChain1* D3D::mD3d11SwapChain;

	void D3D::Initialize(HWND hWnd)
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
			IDXGIFactory2* dxgiFactory;
			{
				// DXGI Interface ���� COM ��ü �̱⶧���� �����ϱ� ���ؼ��� QueryInterface�� �ʿ��մϴ�. 
				// ���� �Ҵ�� device ������ Ȱ���� dxgi �������̽� device�� ���� �Ҵ��մϴ�. 
				IDXGIDevice1* dxgiDevice;
				HRESULT hResult = mD3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
				assert(SUCCEEDED(hResult));

				// ���� ����� GPU�� ���� ������ DEBUG ������ ǥ���� �� ǥ���ϱ� ����
				// adapter ��ü�� �����մϴ�.
				IDXGIAdapter* dxgiAdapter;
				hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
				assert(SUCCEEDED(hResult));
				dxgiDevice->Release();

				DXGI_ADAPTER_DESC adapterDesc;
				dxgiAdapter->GetDesc(&adapterDesc);

				OutputDebugStringA("Graphics Device: ");
				OutputDebugStringW(adapterDesc.Description);

				// DXGIAdapter�� DXGIObject�� ��� �޴� ��ü�� �ش� DXGIobject ��ü�� Ȱ����
				// dxgifactory2 �������̽��� �����մϴ�.
				hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
				assert(SUCCEEDED(hResult));
				dxgiAdapter->Release();
			}

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

			// Hwnd�� ����� swapchain�� �����ϴ� �Լ�
			// 1. pDevice : ���� devicecontext ��, �׷��ִ� ��ü�� ���� ���� ���Ѿ���
			// 2. hWnd : ������ ������ �ڵ�
			// 3. pDesc : DXGI_SWAP_CHAIN_DESC1 ��, swapchain�� �ɼ� ��
			// 4. pFullScreen : fullscreen�� ���� ���� ü�� �ɼ��̴�. ������� ���� ��� 0���� ǥ��
			// 5. pRestrictToOutput : ���� ü�� ��� ���ѿ� ���� �ɼ��̴�.
			// 6. ppSwapChain : ������ swapchain�� ��ȯ�Ѵ�.

			HRESULT hResult = dxgiFactory->CreateSwapChainForHwnd(
				  mD3d11Device
				, hWnd
				, &d3d11SwapChainDesc
				, 0
				, 0
				, &mD3d11SwapChain);



			// ���� ü���̶� ���� ���α׷��� �� ȭ���� �����ϸ�, �̸� ���� ù ���ۿ� ��ü�ϴ� �۾��� �ǹ��մϴ�.
			// �̸� ������ �Ǵ� �ø����̶��մϴ�.
			// ���� �ص�� ����� ���� ü���� �������ϴ�.
			assert(SUCCEEDED(hResult));

			dxgiFactory->Release();
		}

		// FrameBuffer Render Target -> �׷��� ��ġ���� �׷��� bitmap ����
		// view�� �� bitmap�� ������ �� �ִ� COM��ü�̴�.
		// �� bitmap�� �ʿ��ϱ⿡ �����ϱ� ���� view��ü�� �������ݴϴ�.
		{
			ID3D11Texture2D* d3d11FrameBuffer;
			HRESULT hResult = mD3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(hResult));

			// swapchain�� ����� �� �ϳ��� �����ϱ� ���� �Լ�

			hResult = mD3d11Device->CreateRenderTargetView(d3d11FrameBuffer, 0, &mD3d11FrameBufferView);
			assert(SUCCEEDED(hResult));
			d3d11FrameBuffer->Release();

			// �� �� ���۸� ��������ϴ� view ��ü�� �����մϴ�.
			// ������ �Ű� ������ ���� ������ view ��ü�� ��ȯ �޽��ϴ�.
			
		}
	}

	void D3D::Update()
	{

	}

	void D3D::Render()
	{

	}
}