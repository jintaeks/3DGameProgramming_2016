// Win32DrawFunction.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32DrawFunction.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int     g_clientWidth = 0;
int     g_clientHeight = 0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HDC hdc);
void CalculatePi(HWND hWnd);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32DRAWFUNCTION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32DRAWFUNCTION));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32DRAWFUNCTION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32DRAWFUNCTION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			{
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				//char text[1024];
				//int i = 12;
				//sprintf(text, "Hello=%i", i);
				//MessageBoxA(hWnd, text, "Test", MB_OK);
			    CalculatePi( hWnd );
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
        OnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
    case WM_SIZE:
        g_clientHeight = HIWORD(lParam);
        g_clientWidth = LOWORD(lParam);
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// draw a line from (x1,y1) to (x2,y2)
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	const int halfWidth = g_clientWidth / 2;
	const int halfHeight = g_clientHeight/ 2;

	MoveToEx(hdc, x1 + halfWidth, -y1 + halfHeight, NULL);
	LineTo(hdc, x2 + halfWidth, -y2 + halfHeight);
}

// f(x) = x^2
float Function(float x)
{
	return x * x;
}

void Rotate(float theta, float& x, float& y)
{
	const float nx = x * cos(theta) - y * sin(theta);
	const float ny = x * sin(theta) + y * cos(theta);
	// set [out] parameter
	x = nx;
	y = ny;
}

void OnPaint(HDC hdc)
{
	const float fScale = 10.f;
	int x1XAxis = -(g_clientWidth / 2);
	int y1XAxis = 0;
	int x2XAxis = +(g_clientWidth / 2);
	int y2XAxis = 0;

	// draw x-axis
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(255, 0, 0));
	DrawLine(hdc, x1XAxis, y1XAxis, x2XAxis, y2XAxis);

	float x = 100.f;
	float y = 50.f;
	SetDCPenColor(hdc, RGB(0, 255, 0));
	DrawLine(hdc, 0, 0, x, y);
	Rotate(45.f * M_PI / 180.f, x, y);
	DrawLine(hdc, 0, 0, x, y);

	float xPrev = -100.f;
	float yPrev = Function(xPrev);
	SetDCPenColor(hdc, RGB(0, 0, 0));
	for (float x = -100.f; x <= +100.f; x += 1.f)
	{
		float y = Function(x);
		DrawLine(hdc, xPrev*fScale, yPrev*fScale
			, x*fScale, y*fScale);
		xPrev = x;
		yPrev = y;
	}
}

float random()
{
	return (float)rand() / (float)RAND_MAX;
}

void CalculatePi( HWND hWnd )
{
	const int counter = 10000;
	int c = 0;
	const int n = counter;
	for (int i = 0; i < counter; ++i)
	{
		// generate a point (x,y) which is in 1x1 rectangle
		float x = random();
		float y = random();

		// calculate length between (0,0) and (x,y)
		float length = sqrt(x * x + y * y);

		// if length <= 1, increase 'c'
		if (length <= 1.f)
		{
			c += 1;
		}
	}
	char text[1024];
	float myPi = ((float)c / (float)n) * 4.0f;
	sprintf_s(text, "pi = %f", myPi );
	MessageBoxA(hWnd, text, "PI", MB_OK);
}
