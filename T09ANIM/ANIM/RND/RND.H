/* FILE NAME   : DEF.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

#include <gl/gl.h>
#include <gl/glu.h>
extern INT KF5_RndCounterPrims, KF5_triangles;

extern DBL
  KF5_RndProjSize,
  KF5_RndProjDist,
  KF5_RndProjFarClip;

extern MATR
  KF5_RndMatrView,
  KF5_RndMatrProj,
  KF5_RndMatrVP;



VOID KF5_RndInit( HWND hWnd );
VOID KF5_RndClose( VOID );

VOID KF5_RndStart( VOID );
VOID KF5_RndEnd( VOID );

VOID KF5_RndCopyFrame( VOID );
VOID KF5_RndResize( INT W, INT H );

VOID KF5_RndCamSet( VEC Loc, VEC At, VEC Up1 );
VOID KF5_RndProjSet( VOID );

/*** Primitives ***/

typedef struct tagkf5VERTEX
{
  VEC P;  /* Vertex position */
} kf5VERTEX;

typedef struct tagkf5PRIM
{
  kf5VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh - by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} kf5PRIM;

BOOL KF5_RndPrimLoad( kf5PRIM *Pr, CHAR *FileName );
VOID KF5_RndPrimDraw( kf5PRIM *Pr, MATR World );
VOID KF5_RndPrimFree( kf5PRIM *Pr );
BOOL KF5_RndPrimCreate( kf5PRIM *Pr, INT NoofV, INT NoofI );

#endif
/*End of RND.H*/