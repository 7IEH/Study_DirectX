#pragma once

#include "Commoninclude.h"

namespace EH
{
	class D3D
	{
	public:
		// Function
		static void Initialize(HWND hWnd);
		static void Update();
		static void Render();

		static ID3D11Device1* GetD3DDevice() { return mD3d11Device; }
		static ID3D11DeviceContext1* GetD3DDeviceContext() { return mD3d11DeviceContext; }
		static ID3D11RenderTargetView* GetD3DView() { return mD3d11FrameBufferView; }
		static IDXGISwapChain1* GetSwapChain() { return mD3d11SwapChain; }

		static void SetD3DView(ID3D11RenderTargetView* view) { mD3d11FrameBufferView = view; }

	private:
		// -------- D3D11 Global Variable--------

		// Create D3D11 Device and Context
		// D3D11Device는 그래픽 카드에 접근해서 
		// 여러가지 명령을 내릴 수 있도록 만들어주는 컴포넌트의 인터페이스 객체
		static ID3D11Device1* mD3d11Device;
		// ID3D11DeviceContext 인터페이스는 렌더 대상을 설정하고, 
		// 자원을 그래픽 파이프 라인에 묶고, GPU가 수행할 렌더링 명령들을 지시하는 데 쓰인다.
		static ID3D11DeviceContext1* mD3d11DeviceContext;
		static ID3D11RenderTargetView* mD3d11FrameBufferView;

		// Create SwapChian
		// Double buffering interface
		static IDXGISwapChain1* mD3d11SwapChain;

		// Vertex Shader
		static ID3DBlob* vsBlob;

	};
}


