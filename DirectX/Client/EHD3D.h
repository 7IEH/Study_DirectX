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
		// D3D11Device�� �׷��� ī�忡 �����ؼ� 
		// �������� ����� ���� �� �ֵ��� ������ִ� ������Ʈ�� �������̽� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		// ID3D11DeviceContext �������̽��� ���� ����� �����ϰ�, 
		// �ڿ��� �׷��� ������ ���ο� ����, GPU�� ������ ������ ��ɵ��� �����ϴ� �� ���δ�.
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


