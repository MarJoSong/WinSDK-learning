#include <windows.h>
#include <strsafe.h>
#include "SysMets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindows");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("���������Ҫ�� Windows NT �²���ִ��!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("���޿Ƽ�"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	POINT apt[] = { 300, 100, 200, 500, 500, 200, 100, 200, 400, 500, 300, 100 };

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);
#if 0
			Polyline(hdc, apt, 6);
			LineTo(hdc, 100, 100);
#else
			PolylineTo(hdc, apt, 6);
			LineTo(hdc, 100, 100);
#endif
			EndPaint(hwnd, &ps);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}