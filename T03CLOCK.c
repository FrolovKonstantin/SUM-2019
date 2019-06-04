/*Frolov Konstantin, 10-5, 1.06.2019*/
#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.14159265358979323846

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
  static HDC hMemDC, hMemClockDc, hMemAnd, hMemNeg;
  static HBITMAP hBm, hBmClock;
  BITMAP bm;
  SYSTEMTIME st;
  HPEN hPen, hPen1, hPen2;
  POINT pnts1[4];
  POINT pnts2[4];
  POINT pnts3[4];


  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 50, NULL);
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    hMemClockDc = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);
    hBmClock = LoadImage(NULL, "CLOCK.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(hMemClockDc, hBmClock);

    hMemAnd = CreateCompatibleDC(hDc);
    hMemAnd = LoadImage(NULL, "and.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemNeg = CreateCompatibleDC(hDc);
    hMemNeg = LoadImage(NULL, "neg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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
    ReleaseDC(hWnd, hDc);
    return 0;
  case WM_TIMER:
    GetLocalTime(&st);

    hPen = CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
    hPen1 = CreatePen(PS_SOLID, 8, RGB(0, 0, 0));
    hPen2 = CreatePen(PS_SOLID, 12, RGB(0, 0, 0));

    hDc = GetDC(hWnd);
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, w, h);

    GetObject(hBmClock, sizeof(bm), &bm);
    BitBlt(hMemDC, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight , hMemClockDc, 0, 0, SRCCOPY);
    
    /*SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, cos((((2 * p) / 60) * (st.wSecond + tm.wMilliseconds / 1000.0)) - (p / 2)) * (bm.bmWidth / 2.6) + w /2,
                   sin((((2 * p) / 60) * (st.wSecond + tm.wMilliseconds / 1000.0)) - (p / 2)) * (bm.bmHeight / 2.6) + h / 2);

    SelectObject(hMemDC, hPen1);
    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, cos((((2 * p) / 60) * (st.wMinute + tm.wSecond / 60.0)) - (p / 2)) * (bm.bmWidth / 2.6) + w / 2,
                   sin((((2 * p) / 60) * (st.wMinute + tm.wSecond / 60.0)) - (p / 2)) * (bm.bmHeight / 2.6) + h / 2);

    SelectObject(hMemDC, hPen2);
      MoveToEx(hMemDC,w / 2 , h / 2, NULL);
      LineTo(hMemDC, cos((((2 * p) / 12) * ((st.wHour  % 12 + tm.wMinute / 60.0))) - (p / 2)) * (bm.bmWidth / 2.6) + w / 2,
                     sin((((2 * p) / 12) * ((st.wHour % 12 + tm.wMinute / 60.0) )) - (p / 2)) * (bm.bmWidth / 2.6) + h / 2);*/

    pnts1[0].x = w / 2;
    pnts1[1].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI / 45) * 200 + w / 2 ;
    pnts1[2].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI / 45) * 200 + w / 2;
    pnts1[3].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + w / 2;
    pnts1[0].y = h / 2;
    pnts1[1].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI/ 45) * 200 + h / 2;
    pnts1[2].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI / 45) * 200 + h / 2;
    pnts1[3].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + h / 2;

    pnts2[0].x = w / 2;
    pnts2[1].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI / 45) * 250 + w / 2 ;
    pnts2[2].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI / 45) * 250 + w / 2;
    pnts2[3].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + w / 2;
    pnts2[0].y = h / 2;
    pnts2[1].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI/ 45) * 250 + h / 2;
    pnts2[2].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI / 45) * 250 + h / 2;
    pnts2[3].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + h / 2;

    pnts3[0].x = w / 2;
    pnts3[1].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2) - PI / 45) * 250 + w / 2 ;
    pnts3[2].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2) - PI / 45) * 250 + w / 2;
    pnts3[3].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + w / 2;
    pnts3[0].y = h / 2;
    pnts3[1].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2) - PI/ 45) * 250 + h / 2;
    pnts3[2].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2) - PI / 45) * 250 + h / 2;
    pnts3[3].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute/ 60.0)) - (PI / 2)) * (bm.bmWidth / 2.6) + h / 2;

    Polygon(hMemDC, pnts1, 4);
    Polygon(hMemDC, pnts2, 4);
    Polygon(hMemDC, pnts3, 4);

    BitBlt(hDc, 0, 0, w , h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDc);
    DeleteObject(hPen);
    DeleteObject(hPen1);
    DeleteObject(hPen2);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBmClock);
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    DeleteDC(hMemClockDc);
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

