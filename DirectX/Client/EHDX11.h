#pragma once

#include "Commoninclude.h"

namespace EH
{
	class DX11
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

	private:
		// -------- D3D11 Global Variable--------

		// Create D3D11 Device and Context
		// D3D11Device�� �׷��� ī�忡 �����ؼ� 
		// �������� ����� ���� �� �ֵ��� ������ִ� ������Ʈ�� �������̽� ��ü
		static ID3D11Device1* mD3d11Device;
		// ID3D11DeviceContext �������̽��� ���� ����� �����ϰ�, 
		// �ڿ��� �׷��� ������ ���ο� ����, GPU�� ������ ������ ��ɵ��� �����ϴ� �� ���δ�.
		static ID3D11DeviceContext1* mD3d11DeviceContext;
		static ID3D11RenderTargetView* mD3d11FrameBufferView;

		// Create SwapChian
		// Double buffering interface
		static IDXGISwapChain1* mD3d11SwapChain;
	};
}


