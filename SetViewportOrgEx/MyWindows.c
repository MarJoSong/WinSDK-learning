#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define PI 3.1415926
#define NUM 200

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
		MessageBox(NULL, TEXT("这个程序需要在 Windows NT 下才能执行!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("鱼C工作室"),
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
	static int cxClient, cyClient;
	static POINT apt[NUM];
	RECT rect;

	switch (message)
	{
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);

			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);
			MoveToEx(hdc, cxClient / 2, 0, NULL);
			LineTo(hdc, cxClient / 2, cyClient);

			SetMapMode(hdc, MM_LOMETRIC);
			SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
			TextOut(hdc, 100, 100, TEXT("正弦函数"), 4);
		
			GetClientRect(hwnd, &rect);
			DPtoLP(hdc, (PPOINT)&rect, 2);
			for (int i = 0; i < NUM; ++i)
			{
				apt[i].x = (rect.right - rect.left) * i / NUM;
				apt[i].y = (int)(sin(2 * PI * i / NUM) * rect.top);
			}
			MoveToEx(hdc, 0, 0, NULL);
			PolylineTo(hdc, apt, NUM);

			SetMapMode(hdc, MM_TEXT);
			EndPaint(hwnd, &ps);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}