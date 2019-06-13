/* FILE NAME   : DATA.C
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Konstantin Frolov.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'KF5'.
*/

#include "../../DEF.H"

HWND KF5_hWndRnd;
HDC KF5_hDCRndFrame;
HBITMAP KF5_hBmRndFrame;
INT KF5_RndFrameW, KF5_RndFrameH;

DBL
KF5_RndProjSize = 0.1,  /* Project plane fit square */
KF5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
KF5_RndProjFarClip = 100;  /* Distance to project far clip plane (far) */

MATR
KF5_RndMatrView, /* View coordinate system matrix */
KF5_RndMatrProj, /* Projection coordinate system matrix */
KF5_RndMatrVP;   /* Stored (View * Proj) matrix */

/*End of RNDDATA.C*/