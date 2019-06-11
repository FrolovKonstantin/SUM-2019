/* FILE NAME   : DEF.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Konstantin Frolov.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'KF5'.
*/

#include "DEF.H"
#include "ANIM/RND/RND.H"
#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include "resource.h"
#pragma warning(disable: 4047 4024 4047 4013)

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShawCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;


  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(hInstance, IDC_CURSOR1);
  wc.hIcon = LoadIcon(hInstance, IDI_ICON1);
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
  hWnd = CreateWindow(WND_CLASS_NAME, "POMOGITE MNE POJALUISTA", WS_OVERLAPPEDWINDOW,
      0, 0,
      1000, 1000,
      NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (TRUE)
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
          if (msg.message == WM_QUIT)
              break;
          DispatchMessage(&msg);
      }
      else
          SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
}

VOID FlipFullScreen( HWND hWnd )
{
static BOOL IsFullScreen = FALSE;
static RECT SaveRC;

if (!IsFullScreen)
{
  RECT rc;
  HMONITOR hmon;
  MONITORINFOEX moninfo;

  GetWindowRect(hWnd, &SaveRC);

  hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

  moninfo.cbSize = sizeof(moninfo);
  GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

  rc = moninfo.rcMonitor;

  AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

  SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
  IsFullScreen = TRUE;
}
else
{
  SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
  IsFullScreen = FALSE;
}
}


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
HDC hDc;
PAINTSTRUCT ps;
static kf5PRIM Pr, Pr1, Pr2;
MATR m;

switch (Msg)
{
  case WM_CREATE:
    KF5_RndInit(hWnd);
    KF5_RndPrimLoad(&Pr, "cow.object");
    KF5_RndPrimLoad(&Pr1, "Giorno_Giovanna.obj");
    KF5_RndPrimLoad(&Pr2, "Mista.object");
    SetTimer(hWnd, 47, 50, NULL);
    return 0;
  case WM_SIZE:
    KF5_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_TIMER:
    KF5_RndStart();
    KF5_RndCamSet(VecSet(0, 60, 50), VecSet(0, 40, 0), VecSet(0, 1, 0));

    m = MatrMulMatr3(MatrScale(VecSet(0.4, 0.4, 0.4)), MatrRotateY(clock() / 100.0), MatrTranslate(VecSet(35, -15, -40)));
    KF5_RndPrimDraw(&Pr1, m);

    m = MatrMulMatr3(MatrScale(VecSet(0.4, 0.4, 0.4)), MatrRotateY(-clock() / 100.0), MatrTranslate(VecSet(-35, -15, -40)));
    KF5_RndPrimDraw(&Pr2, m);

    m = MatrMulMatr3(MatrScale(VecSet(1.4, 1.4, 1.4)), MatrTranslate(VecSet(-25, -15, -16)), MatrRotateY(-clock() / 100.0 ));
    KF5_RndPrimDraw(&Pr, m);

    hDc = GetDC(hWnd);
    KF5_RndCopyFrame(hDc);
    KF5_RndEnd();
    ReleaseDC(hWnd, hDc);
    return 0;
  case WM_CLOSE:
    SendMessage(hWnd, WM_DESTROY, wParam, lParam);
    return 0;
  case WM_PAINT:
   hDc = BeginPaint(hWnd, &ps);
    KF5_RndCopyFrame(hDc);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
   return 1;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      DestroyWindow(hWnd);
    if (wParam == VK_INSERT)
      FlipFullScreen(hWnd);
  return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;
}
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/*End of MAIN.C*/