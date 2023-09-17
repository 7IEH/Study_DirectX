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
			// 전체 화면 전환을 처리하는 DXGI 개체를 생성하는 메서드를 구현하는 것
			/*DXGI 는 DirectX 그래픽 런타임에 독립적인 저수준의 작업을 관리한다.

				기본적인 작업은

				-하드웨어 디바이스의 열거(그래픽 카드가 여러개일 수 있다.)

				- 디스플레이 모드의 나열

				- 출력장치의 나열(모니터를 여러 개 사용할 수 있다.)

				- 스왑 체인 생성

				- 프레젠테이션

				- 풀스크린 모드*/
			// 이 중에 스왑체인을 생성하기 위해서 DXGI(DirectX Graphics Infrastructure)를 사용해야하며
			// , DXGI 인터페이스를 사용하기 위해서는 DXGI Factory 객체를 생성해야한다.
			IDXGIFactory2* dxgiFactory;
			{
				// DXGI Interface 역시 COM 객체 이기때문에 접근하기 위해서는 QueryInterface가 필요합니다. 
				// 현재 할당된 device 정보를 활용해 dxgi 인터페이스 device를 먼저 할당합니다. 
				IDXGIDevice1* dxgiDevice;
				HRESULT hResult = mD3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
				assert(SUCCEEDED(hResult));

				// 현재 연결된 GPU에 대한 정보를 DEBUG 정보를 표시할 때 표시하기 위해
				// adapter 객체에 접근합니다.
				IDXGIAdapter* dxgiAdapter;
				hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
				assert(SUCCEEDED(hResult));
				dxgiDevice->Release();

				DXGI_ADAPTER_DESC adapterDesc;
				dxgiAdapter->GetDesc(&adapterDesc);

				OutputDebugStringA("Graphics Device: ");
				OutputDebugStringW(adapterDesc.Description);

				// DXGIAdapter는 DXGIObject를 상속 받는 객체로 해당 DXGIobject 객체를 활용해
				// dxgifactory2 인터페이스에 접근합니다.
				hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
				assert(SUCCEEDED(hResult));
				dxgiAdapter->Release();
			}

			// 얻은 DXGIFactory를 활용해 swapchain을 생성하기 위해
			// swapchain에 option을 설정해줍니다.
			// 1. Width : 현재 해상도의 너비를 뜻합니다. 0으로 설정시에 런타임에서 현재 해상도의 너비를 가져옵니다.
			// 2. Height : 현재 해상도의 높이를 뜻합니다. 0으로 설정시에 런타임에서 현재 해상도의 높이를 가져옵니다.
			// 3. Format : 표시 형식을 설명하는 DXGI_FORMAT 구조체입니다. DXGI_FORMAT_B8G8R8A8_UNORM_SRGB 값: 91
			// 알파를 포함하여 각 채널에 대해 8비트를 지원하는 4개 구성 요소의 32비트 부호 없는 정규화된 표준 RGB 형식입니다.
			// 4. sampleDesc 객체의 Count : 픽셀당 멀티샘플 즉, 안티앨리어싱에 관한 옵션입니다. 값이 높을수록 더 자연 스러운 곡선을 보입니다.
			// 5. sampleDesc 객체의 Quality : 이미지 품질 수준으로 값이 높을수록 성능이 낮아집니다. (0~1)
			// 6. BufferUsage : 표면 및 리소스 만들기 옵션에 대한 플래그입니다. DXGI_USAGE_RENDER_TARGET_OUTPUT 표면 또는 리소스를 출력 렌더링 대상으로 사용합니다.
			// 7. buffercount : 즉, 교체하는 화면들의 수를 나타냅니다.
			// 8. Scaling : 백 버퍼의 해상도가 출력 하려는 해상도와 맞지 않을 경우 크기를 어떻게 할지에 대한 메뉴얼.
			// 9. SwapEffect : 출력한 백버퍼를 어떻게 할지에 대한 메뉴얼
			// 10. AlphaMode : 백 버퍼의 alpha값을 조정합니다.
			// 11. Flags : 스왑 체인 옵션 값

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

			// Hwnd와 연결된 swapchain를 생성하는 함수
			// 1. pDevice : 현재 devicecontext 즉, 그려주는 객체에 대해 연결 시켜야함
			// 2. hWnd : 연결할 윈도우 핸들
			// 3. pDesc : DXGI_SWAP_CHAIN_DESC1 즉, swapchain에 옵션 값
			// 4. pFullScreen : fullscreen에 대한 스왑 체인 옵션이다. 사용하지 않을 경우 0으로 표시
			// 5. pRestrictToOutput : 스왑 체인 출력 제한에 대한 옵션이다.
			// 6. ppSwapChain : 생성된 swapchain을 반환한다.

			HRESULT hResult = dxgiFactory->CreateSwapChainForHwnd(
				  mD3d11Device
				, hWnd
				, &d3d11SwapChainDesc
				, 0
				, 0
				, &mD3d11SwapChain);



			// 스왑 체인이랑 응용 프로그램이 새 화면을 제공하면, 이를 현재 첫 버퍼와 교체하는 작업을 의미합니다.
			// 이를 스와핑 또는 플리핑이라합니다.
			// 현재 해들과 연결된 스왑 체인을 만들어냅니다.
			assert(SUCCEEDED(hResult));

			dxgiFactory->Release();
		}

		// FrameBuffer Render Target -> 그래픽 장치에서 그려줄 bitmap 느낌
		// view는 그 bitmap에 접근할 수 있는 COM객체이다.
		// 그 bitmap이 필요하기에 접근하기 위한 view객체를 생성해줍니다.
		{
			ID3D11Texture2D* d3d11FrameBuffer;
			HRESULT hResult = mD3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
			assert(SUCCEEDED(hResult));

			// swapchain에 백버퍼 중 하나에 접근하기 위한 함수

			hResult = mD3d11Device->CreateRenderTargetView(d3d11FrameBuffer, 0, &mD3d11FrameBufferView);
			assert(SUCCEEDED(hResult));
			d3d11FrameBuffer->Release();

			// 그 백 버퍼를 대상으로하는 view 객체를 생성합니다.
			// 마지막 매개 변수를 통해 생성된 view 객체를 반환 받습니다.
			
		}
	}

	void D3D::Update()
	{

	}

	void D3D::Render()
	{

	}
}