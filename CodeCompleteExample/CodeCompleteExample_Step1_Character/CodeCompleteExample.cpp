// CodeCompleteExample.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "CodeCompleteExample.h"
#include <MMSystem.h>
#include "KCharacterManager.h"
#include "KMainUi.h"
#include "KCharacterController.h"
#include "KCharacterUtil.h"

// added line. jintaeks on 2016-09-28_11-31
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE               g_hInstance;								// 현재 인스턴스입니다.
TCHAR                   szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR                   szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.
HWND                    g_hwndMain = NULL;
HDC                     g_hdc = 0;
HBITMAP                 g_hBitmap = 0;
KCharacterManager       g_characterManager;
KCharacterWeakPtr       g_wpMyCharacter;
//KMainUi                 g_mainUi;
RECT                    g_clientRect;
KCharacterController    g_characterController;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                    MyRegisterClass(HINSTANCE hInstance);
BOOL                    InitInstance(HINSTANCE, int);
LRESULT CALLBACK        WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK        About(HWND, UINT, WPARAM, LPARAM);
void                    Initialize();
void                    Finalize();
void                    OnSize();
void                    OnIdle( float fElapsedTime_ );
void                    OnFrameMove( float fElapsedTime_ );
void                    OnFrameRender( HDC hdc_, float fElapsedTime_ );
void                    OnFrameRenderMyCharacter( HDC hdc_, float fElapsedTime_ );


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CODECOMPLETEEXAMPLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CODECOMPLETEEXAMPLE));

    Initialize();

    DWORD dwOldTime = ::timeGetTime();
	// 기본 메시지 루프입니다.
	while( true )
	{
        ::Sleep( 10 );
        ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
        const DWORD dwNewTime = ::timeGetTime();
        const BOOL bIsTranslateMessage = TranslateAccelerator(msg.hwnd, hAccelTable, &msg);
		if( !bIsTranslateMessage )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}//if

        OnIdle( float( dwNewTime - dwOldTime ) );
        Sleep( 10 );

        dwOldTime = dwNewTime;

        if( msg.message == WM_QUIT )
        {
            break;
        }//if
	}//while

    Finalize();

	return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CODECOMPLETEEXAMPLE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CODECOMPLETEEXAMPLE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hwndMain = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, NULL, NULL, hInstance, NULL);

   if (!g_hwndMain)
   {
      return FALSE;
   }

   ShowWindow(g_hwndMain, nCmdShow);
   UpdateWindow(g_hwndMain);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
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
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
        case IDM_CREATE_CHARACTER:
            {
                const int iCharIndex = g_characterManager.CreateCharacter();
                if( iCharIndex == 0 )
                {
                    g_wpMyCharacter = g_characterManager.GetCharacter( 0 );
                    //g_mainUi.SetCharacter( g_wpMyCharacter );
                    g_characterController.SetCharacter( g_wpMyCharacter );
                }//if
            }
            break;
        case IDM_DESTROY_CHARACTER:
            g_characterManager.DestroyCharacter();
            InvalidateRect( g_hwndMain, NULL, TRUE );
            break;
        case IDM_SET_CHARACTER_DATA:
            if( KCharacterPtr spCharacter = g_wpMyCharacter.lock() )
            {
                //MessageBox( g_hwndMain, L"Hello", L"Hello", MB_OK );
                const DWORD dwHp = spCharacter->GetHp();
                spCharacter->SetHp( dwHp + 1 );
            }
            break;
        case IDM_WRITE_CHARACTER_DATA:
            if( KCharacterPtr spCharacter = g_wpMyCharacter.lock() )
            {
                FILE* pFile = fopen( "CharacterData.txt", "wt" );
                KCharacterUtil::WriteCharacterData( spCharacter, pFile );
                //g_mainUi.WriteUiData( pFile );
                fclose( pFile );
            }//if
            break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
        {
		    hdc = BeginPaint(hWnd, &ps);
		    // TODO: 여기에 그리기 코드를 추가합니다.
            //WCHAR wszText[] = L"WM_PAINT : Hello Render";
            //::TextOut( hdc, 0, 0, wszText, _countof( wszText ) - 1 );
		    EndPaint(hWnd, &ps);
        }
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        OnSize();
        //::GetClientRect( g_hwndMain, &g_clientRect );
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

void Initialize() {
}//Initialize()

void Finalize() {
    g_characterManager.Finalize();
    g_wpMyCharacter.reset();
    //g_mainUi.Finalize();
    g_characterController.Finalize();

    if( g_hdc != 0 ) {
        DeleteDC( g_hdc );
        g_hdc = 0;
    }//if
    if( g_hBitmap != 0 ) {
        DeleteObject( g_hBitmap );
        g_hBitmap = 0;
    }//if
}//Finalize()

void OnSize() {
    Finalize();

    ::GetClientRect( g_hwndMain, &g_clientRect );
    const int iWidth = g_clientRect.right - g_clientRect.left + 1;
    const int iHeight = g_clientRect.bottom - g_clientRect.top + 1;

    HDC hdc = ::GetDC( g_hwndMain );
    g_hdc = CreateCompatibleDC( hdc );
    g_hBitmap = CreateCompatibleBitmap( g_hdc, iWidth, iHeight );
    SelectObject( g_hdc, g_hBitmap );
}//OnSize()

void OnIdle( float fElapsedTime_ )
{
    OnFrameMove( fElapsedTime_ );

    const int iWidth = g_clientRect.right - g_clientRect.left + 1;
    const int iHeight = g_clientRect.bottom - g_clientRect.top + 1;

    HDC hdc = ::GetDC( g_hwndMain );

    HBRUSH brush;
    brush = CreateSolidBrush( RGB( 255, 255, 255 ) );
    SelectObject( g_hdc, brush );
    Rectangle( g_hdc, 0, 0, iWidth, iHeight );

    {
        OnFrameRender( g_hdc, fElapsedTime_ );
    }
    BitBlt( hdc, 0, 0, iWidth, iHeight, g_hdc, 0, 0, SRCCOPY );
    DeleteObject( brush );

    ::ReleaseDC( g_hwndMain, hdc );
    //::UpdateWindow( g_hwndMain );
}//OnIdle()

void OnFrameMove( float fElapsedTime_ )
{
    g_characterManager.OnFrameMove( fElapsedTime_ );
    g_characterController.OnFrameMove( fElapsedTime_ );
    //g_mainUi.OnFrameMove( fElapsedTime_ );
}//OnFrameMove()

void OnFrameRender( HDC hdc_, float fElapsedTime_ )
{
    //WCHAR wszText[] = L"OnFrameRender : Hello Render";
    //::TextOut( hdc_, 0, 100, wszText, _countof( wszText ) - 1 );
    g_characterManager.OnFrameRender( hdc_, fElapsedTime_ );
    g_characterController.OnFrameRender( hdc_, fElapsedTime_ );
    OnFrameRenderMyCharacter( hdc_, fElapsedTime_ );
    //g_mainUi.OnFrameRender( hdc_, fElapsedTime_ );
}//OnFrameRender()

void OnFrameRenderMyCharacter( HDC hdc_, float fElapsedTime_ )
{
    // render my character extra.
    if( KCharacterPtr spCharacter = g_wpMyCharacter.lock() )
    {
        const int iManagerIndex = spCharacter->GetCharacterManagerIndex();
        WCHAR wszText[] = L"<- MyCharacter";
        ::TextOut( hdc_, 200, 1 + iManagerIndex * 16, wszText, _countof( wszText ) - 1 );
    }//if
}//OnFrameRenderMyCharacter()
