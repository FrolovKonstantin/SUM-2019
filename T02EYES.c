/*Frolov Konstantin, 10-5, 1.06.2019*/
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
  wc.style = CS_VREDRAW | CS_HREDRAW;

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

VOID DrawEyes( HDC hDc, INT x, INT y, INT r, INT r1, INT mx, INT my )
{
  int lx, ly;
  double t;

  t = sqrt((mx - x) * (mx - x) + (my - y) * (my - y));
  lx = (int)((mx - x) / t * (r1 - r));
  ly = (int)((my - y) / t * (r1 - r));

  SelectObject(hDc, GetStockObject(WHITE_BRUSH));
  Ellipse(hDc, x - r1, y - r1, x + r1, y + r1);
  if (t + r < r1)  
  {
    SelectObject(hDc, GetStockObject(BLACK_BRUSH));
    Ellipse(hDc, mx - r , my - r, mx + r, my + r);
  }
  else
  {
   SelectObject(hDc, GetStockObject(BLACK_BRUSH));
   Ellipse(hDc, x + lx - r, y + ly - r,x + lx + r, y + ly + r);
  }
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  PAINTSTRUCT ps;
  static int w, h;
  static HDC hMemDC;
  static HBITMAP hBm;
  POINT pt;
  int i;
  double t ;

  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 47, 50, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, w, h);
    ReleaseDC(hWnd, hDc);
    SelectObject(hMemDC, hBm);
    return 0;
  case WM_TIMER:
    hDc = GetDC(hWnd);
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDC,GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0,1920, 1080);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    srand(15);
    t = clock() / 400.0;
    for (i = 0; i < 10; i++)
      DrawEyes(hMemDC , rand() % w + sin(2 * t + 10 * i) * 10, rand() % h + sin(t + i), 35, 60, pt.x, pt.y);
    BitBlt(hDc, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDc);
    return 0;
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

