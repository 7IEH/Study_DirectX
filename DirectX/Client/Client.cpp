#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE

#include "Commoninclude.h"
#include "EHApplication.h"
#include "EHDX11.h"

EH::Application application;

#define MAX_LOADSTRING 100

//-------- WinAPI Global Variable --------
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// Function
ATOM			 MyRegisterClass(HINSTANCE hInstance);
BOOL			 InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ------------------ END ------------------

HWND GhWnd;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance
	, _In_opt_ HINSTANCE hPrevInstance
	, _In_ LPWSTR lpCmdLine
	, _In_ int nCmdShow)
{

	HWND hWnd = nullptr;

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			application.Run();
		}
	}
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = szWindowClass;
	wcex.lpszMenuName = nullptr;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	RECT resolution = { 0,0,1600,900 };
	AdjustWindowRectEx(&resolution, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	HWND hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW
		, szWindowClass
		, szTitle
		, WS_OVERLAPPEDWINDOW | WS_VISIBLE
		, 0
		, 0
		, (int)resolution.right
		, (int)resolution.bottom
		, nullptr
		, nullptr
		, hInstance
		, nullptr);

	if (!hWnd) {
		MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
		return GetLastError();
	}

	application.Initialize(hWnd);
	GhWnd = hWnd;
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	return 0;
}
