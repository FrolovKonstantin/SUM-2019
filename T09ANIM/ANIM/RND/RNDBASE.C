/* FILE NAME   : RNDBASE.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#include "..\..\DEF.H"
#include "..\anim.h"

VOID KF5_RndStart( VOID )
{
  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  KF5_RndCounterPrims = 0, KF5_triangles = 0;
}

VOID KF5_RndEnd( VOID )
{
  glFinish();
}

VOID KF5_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  KF5_RndMatrView = MatrView(Loc, At, Up1);
  KF5_RndMatrVP = MatrMulMatr(KF5_RndMatrView, KF5_RndMatrProj);
}

VOID KF5_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Store window and context handles */
  KF5_Anim.hWnd = hWnd;
  KF5_Anim.hDC = GetDC(KF5_Anim.hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(KF5_Anim.hDC, &pfd);
  DescribePixelFormat(KF5_Anim.hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(KF5_Anim.hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  KF5_Anim.hRC = wglCreateContext(KF5_Anim.hDC);
  wglMakeCurrent(KF5_Anim.hDC, KF5_Anim.hRC);

  /* Set default render parameters */
  glClearColor(0.30, 0.50, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  KF5_RndCamSet(VecSet(-100, 0, -20), VecSet(0, 0, 0), VecSet(0, 1, 0));
}

VOID KF5_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(KF5_Anim.hRC);
  ReleaseDC(KF5_Anim.hWnd, KF5_Anim.hDC);
}

VOID KF5_RndCopyFrame( VOID )
{
  SwapBuffers(KF5_Anim.hDC);
}

VOID KF5_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
  KF5_Anim.W = W;
  KF5_Anim.H= H;
  KF5_RndProjSet();
}
VOID KF5_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = KF5_RndProjSize / 2;
  if (KF5_Anim.W >= KF5_Anim.H)
    ratio_x *= (DBL)KF5_Anim.W / KF5_Anim.H;
  else
    ratio_y *= (DBL)KF5_Anim.H / KF5_Anim.W;
  KF5_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    KF5_RndProjDist, KF5_RndProjFarClip);
  KF5_RndMatrVP = MatrMulMatr(KF5_RndMatrView, KF5_RndMatrProj);
}

/*End of RNDBASE.C*/