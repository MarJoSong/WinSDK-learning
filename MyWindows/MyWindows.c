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
	int i;
	RECT rect;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);

			for (i = rect.top; i < rect.bottom; i+=30 )
			{
				MoveToEx(hdc, 0, i, NULL);
				LineTo(hdc, rect.right, i);
			}

			for (i = rect.left; i < rect.right; i += 30)
			{
				MoveToEx(hdc, i, 0, NULL);
				LineTo(hdc, i, rect.bottom);
			}

			EndPaint(hwnd, &ps);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}