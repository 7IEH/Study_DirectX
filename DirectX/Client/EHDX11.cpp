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
			// 1. pAdapter : 연결할 그래픽 어댑터(GPU를 뜻함)(0 or NULL 사용시 기본 장치에 연결) 
			// 2. DriverType : 그 그래픽 어댑터의 종류를 뜻함 보통 GPU를 사용하니 하드웨어가 디폴트
			// 다른 옵션은 때에 따라 사용함
			// 3. Software : 아까와 마찬가지로 hardware를 사용하니 0를 넣어줌 2번 인수에 software를 사용하겠다
			// 선언시에는 NULL 값을 넣으면 안됨
			// 4. Flags : 추가적인 장치 생성 플래그들입니다. debug 시에는 D3D11_CREATE_DEVICE_DEBUG사용
			// D3D11_CREATE_DEVICE_BGRA_SUPPORT 같은 경우 Direct3D 리소스와의 Direct2D 상호 운용성에 필요합니다
			// 5. *pFeatureLevels : 즉, 내 장치가 지원하는 수준을 점검하는 기능입니다. 최소 수준을 잡아줌
			// 6. FeatureLevels : 위에 장치가 지원하는 기술 수준들을 나열한 배열의 크기를 가져옴
			// 7. SDKVersion : 사용할 SDK 버전을 입력합니다.
			// 8. **ppDevice : 만들어낸 device 장치를 반환합니다.
			// 9. *pFeatureLevel : 위에 feature 수준이 성공한다면 그 기능 첫번째 수준을 반환합니다.
			// 10. *ppImmdiateContext : 만들어낸 디바이스 콘텍스트 객체를 반환합니다.
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

			// COM(Component Object Model) 객체는 직접적으로 안에 있는것을 알 수 없으니 특별한 함수를 사용해야함
			// COM 객체는 대문자 I로 시작
			// QueryInterface는 그 COM 객체안에 있는것을 달라고하는 함수
			// QueryInterface(원하는 것의 종류, 원하는 것을 담을 바구니);
			// 생성한 device에서 ID3D11Device1 객체를 가져옴
			// ID3D11Device1를 얻기 위해서는 ID3D11Device를 먼저 생성해야함
			// 마찬가지로, ID3D11DeviceContext1를 얻기위해서는 ID3D11DeviceContext를 먼저 생성해야함
			hResult = baseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&mD3d11Device);
			assert(SUCCEEDED(hResult));
			// 이제 필요없는 baseDevice는 할당을 해제해준다.
			baseDevice->Release();

			hResult = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&mD3d11DeviceContext);
			assert(SUCCEEDED(hResult));
			baseDeviceContext->Release();

			// -> 이로서 device와 devicecontext는 생성완료

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

		// FrameBuffer Render Target -> 그래픽 장치에서 그려줄 bitmap 느낌
		// view는 그 bitmap에 접근할 수 있는 COM
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