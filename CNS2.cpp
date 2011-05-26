// CNS2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CNS2.h"
#include "lp.h"

#include <stdio.h>
#include <conio.h>                             // getche
#include "commctrl.h"
#include <psapi.h>                             // PSAPI for EnumProcesses
#include <string.h>
#include <assert.h>
#pragma warning(disable:4786)                 // disable annoying C4786
#include <string>                                 // STL string class
#include <list>                                 // STL list class

#include <ole2.h>
#include <commctrl.h>
using namespace std;                             // use STL

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                    // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HHOOK hkprcSysMsg;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND hWnd;
HWND g_hwndTT;
RECT r;
wchar_t *wText;
POINT pt;
BOOL ptf;


 


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) ;
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_CNS2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CNS2));

    HCURSOR hCursor = LoadCursor(0, IDC_CROSS);
    HANDLE holdcursor = SetCursor(hCursor);


    hkprcSysMsg = SetWindowsHookEx(WH_MOUSE_LL,MouseProc,hInst, 0);

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnhookWindowsHookEx(hkprcSysMsg);   
    return (int) msg.wParam;
}


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    CHAR szBuf[128];
    CHAR szMsg[16];
    HDC hdc;
    static int c = 0;
    size_t cch;
    HRESULT hResult;

    if(nCode == HC_ACTION && wParam == WM_LBUTTONDOWN){

        if(!ptf){
            ptf = true;
            MSLLHOOKSTRUCT *hook = (MSLLHOOKSTRUCT *)lParam;
            pt= hook->pt;
            hResult = PostMessage( hWnd, WM_TIMER, 1,0);
        }
    }
    return CallNextHookEx(hkprcSysMsg, nCode, wParam,
        lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style             = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra        = 0;
    wcex.cbWndExtra        = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CNS2));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName    = MAKEINTRESOURCE(IDC_CNS2);
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


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
#include "shellapi.h"
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    NOTIFYICONDATA niData = {0};
    niData.cbSize =sizeof(NOTIFYICONDATA);
    niData.uID = IDI_ICON14;
    niData.uFlags = //some flags that determine the tray's behavior:
        NIF_ICON //we're adding an icon
        | NIF_MESSAGE //we want the tray to send a message to the window identified by hWnd when something happens to our icon (see uCallbackMesage member below).
        | NIF_TIP; //our icon has a tooltip.
    niData.hIcon =
        (HICON)LoadImage( hInstance,
            MAKEINTRESOURCE(IDI_ICON14),
            IMAGE_ICON, //tells the versatile LoadImage function that we are loading an icon
            16, 16, //x and y values. we want a 16x16-pixel icon for the tray.
            0);
    niData.hWnd = hWnd;
    niData.uCallbackMessage = 909;
    niData.szTip[0] = 'C';
    Shell_NotifyIcon(NIM_ADD,&niData);

    return true;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND    - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY    - post a quit message and return
//

void ShowContextMenu(HWND hWnd,int x,int y)
{
    HMENU hmenu;            // top-level menu
    HMENU hmenuTrackPopup;  // shortcut menu
 
    // Load the menu resource.
    if ((hmenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1))) == NULL)
        return;

    // TrackPopupMenu cannot display the menu bar so get
    // a handle to the first shortcut menu.
 
    hmenuTrackPopup = GetSubMenu(hmenu, 0);
 
    // Display the shortcut menu. Track the right mouse
    // button.
    SetForegroundWindow(hWnd);
    TrackPopupMenu(hmenuTrackPopup,
            TPM_LEFTALIGN ,
            x, y, 0, hWnd, NULL);
    PostMessage(hWnd, WM_NULL, 0, 0);

    // Destroy the menu.
 
    DestroyMenu(hmenu);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    if(ptf)     {
        ptf = false;
       
        string out = getProcesses(pt);
        int len = out.length()+1;
        wText = new wchar_t[len];
        memset(wText,0,len);
        ::MultiByteToWideChar( CP_ACP, NULL, out.c_str(), -1, wText,len );
        //gToolTip::PutInTaskBar(hWnd,hInst,NULL,NULL,wText,_T("Dave's Magic Widget"));
       
    }
    switch (message)
    {
    case 909:
        switch(lParam)
        {
        case WM_RBUTTONDOWN:
        case WM_CONTEXTMENU:
           POINT Mouse;
           GetCursorPos(&Mouse);
           ShowContextMenu(hWnd,Mouse.x,Mouse.y);
           break;
   
        }
        break;
    case WM_COMMAND:{
        switch(LOWORD(wParam)){
            case ID_FOO_BAR:
                exit(0);
        }
    }
           
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
