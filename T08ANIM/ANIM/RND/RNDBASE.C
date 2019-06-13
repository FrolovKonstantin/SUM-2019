/* FILE NAME   : RNDBASE.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#include "..\..\DEF.H"
#include "RND.h"

VOID KF5_RndStart(VOID)
{
  SelectObject(KF5_hDCRndFrame, KF5_hBmRndFrame);
  SelectObject(KF5_hDCRndFrame, GetStockObject(WHITE_BRUSH));
  Rectangle(KF5_hDCRndFrame, 0, 0, KF5_RndFrameW, KF5_RndFrameW);
  SelectObject(KF5_hDCRndFrame, GetStockObject(NULL_BRUSH));
  SelectObject(KF5_hDCRndFrame, GetStockObject(BLACK_PEN));
}
VOID KF5_RndEnd(VOID)
{

}

VOID KF5_RndCamSet(VEC Loc, VEC At, VEC Up1)
{
  KF5_RndMatrView = MatrView(Loc, At, Up1);
  KF5_RndMatrVP = MatrMulMatr(KF5_RndMatrView, KF5_RndMatrProj);
}

VOID KF5_RndInit(HWND hWnd)
{
  HDC hDC;

  hDC = GetDC(hWnd);
  KF5_hDCRndFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);

  KF5_RndCamSet(VecSet(-100, 0, -20), VecSet(0, 0, 0), VecSet(0, 1, 0));
}

VOID KF5_RndClose(VOID)
{
  DeleteObject(KF5_hBmRndFrame);
  DeleteDC(KF5_hDCRndFrame);
}

VOID KF5_RndCopyFrame(HDC hDC)
{
  BitBlt(hDC, 0, 0, KF5_RndFrameW, KF5_RndFrameH,
    KF5_hDCRndFrame, 0, 0, SRCCOPY);
}

VOID KF5_RndResize(INT W, INT H)
{
  HDC hDC;

  if (KF5_hBmRndFrame != NULL)
    DeleteObject(KF5_hBmRndFrame);

  hDC = GetDC(KF5_hWndRnd);
  KF5_hBmRndFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(KF5_hWndRnd, hDC);
  SelectObject(KF5_hDCRndFrame, KF5_hBmRndFrame);

  KF5_RndFrameW = W;
  KF5_RndFrameH = H;
  KF5_RndProjSet();
}
VOID KF5_RndProjSet(VOID)
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = KF5_RndProjSize / 2;
  if (KF5_RndFrameW >= KF5_RndFrameH)
    ratio_x *= (DBL)KF5_RndFrameW / KF5_RndFrameH;
  else
    ratio_y *= (DBL)KF5_RndFrameH / KF5_RndFrameW;
  KF5_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    KF5_RndProjDist, KF5_RndProjFarClip);
  KF5_RndMatrVP = MatrMulMatr(KF5_RndMatrView, KF5_RndMatrProj);
}

/*End of RNDBASE.C*/