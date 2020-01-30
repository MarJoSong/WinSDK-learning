#include <windows.h>

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
	HPEN hPen, hOldPen;
	RECT rect;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);

			
			hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
			hOldPen = SelectObject(hdc, hPen);

			MoveToEx(hdc, rect.left, rect.bottom / 4, NULL);
			LineTo(hdc, rect.right, rect.bottom / 4);
			DeleteObject(hPen);
			hPen = GetStockObject(BLACK_PEN);
			SelectObject(hdc, hPen);
			Ellipse(hdc, rect.left, rect.bottom / 4, rect.right / 2, rect.bottom * 3 / 4);

			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, rect.left, rect.bottom * 3 / 4, NULL);
			LineTo(hdc, rect.right, rect.bottom * 3 / 4);
			DeleteObject(hPen);

			hPen = CreatePen(PS_INSIDEFRAME, 30, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			Ellipse(hdc, rect.right / 2, rect.bottom / 4, rect.right, rect.bottom * 3 / 4);
			DeleteObject(hPen);

			SelectObject(hdc, hOldPen);

			EndPaint(hwnd, &ps);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}