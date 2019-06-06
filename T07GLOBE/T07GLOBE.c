/*Frolov Konstantin, 10-5, 1.06.2019*/
#include "GLOBE.h"
#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include <math.h>
#include <stdlib.h>
#include <time.h>


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShawCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDI_ERROR);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Oh no", "ERROR", MB_OK);
    return 0;
  }
  hWnd = CreateWindow(WND_CLASS_NAME, "OKNO", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE; /* текущий режим */
  static RECT SaveRC;               /* сохраненный размер */

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* сохраняем старый размер окна */
    GetWindowRect(hWnd, &SaveRC);

    /* определяем в каком мониторе находится окно */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* получаем информацию для монитора */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* переходим в полный экран */
    /* для одного монитора:
    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    */
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP, /* можно HWND_TOPMOST */
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    /* восстанавливаем размер окна */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'FlipFullScreen' function */


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  static int w, h;
  static HDC hMemDC;
  static HBITMAP hBm;
  SYSTEMTIME st;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 50, NULL);
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);
    GLOBE();
    return 0;

  case WM_LBUTTONDBLCLK:
    FlipFullScreen(hWnd);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, w, h);
    SelectObject(hMemDC, hBm);
    return 0;
  case WM_TIMER:
    GetLocalTime(&st);

    hDc = GetDC(hWnd);
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, w, h);

    BitBlt(hDc, 0, 0, w , h, hMemDC, 0, 0, SRCCOPY);
    DRAW(hMemDC, w, h);
    ReleaseDC(hWnd, hDc);
    return 0;
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

