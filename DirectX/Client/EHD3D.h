#pragma once

#include "Commoninclude.h"

namespace EH
{
	class D3D
	{
	public:
		D3D();
		~D3D();

		// Function	
		bool CreateSwapChain(HWND hwnd);
		Microsoft::WRL::ComPtr<ID3D11Device> GetGPUDevice() { return mDevice; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetGPUContext() { return mContext; }
		Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return mSwapChain; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetView() { return mRenderTargetView; }

		void SetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> view) { mRenderTargetView = view; }

	private:
		// -------- D3D11 Global Variable--------

		// Create D3D11 Device and Context
		// D3D11Device는 그래픽 카드에 접근해서 
		// 여러가지 명령을 내릴 수 있도록 만들어주는 컴포넌트의 인터페이스 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		// ID3D11DeviceContext 인터페이스는 렌더 대상을 설정하고, 
		// 자원을 그래픽 파이프 라인에 묶고, GPU가 수행할 렌더링 명령들을 지시하는 데 쓰인다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mFrameBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	};

	// This is a helper to get access to a global device instance
	//	- The engine uses this, but it is not necessary to use a single global device object
	//	- This is not a lifetime managing object, just a way to globally expose a reference to an object by pointer
	inline D3D*& GetDevice()
	{
		static D3D* device = nullptr;
		return device;
	}
}


