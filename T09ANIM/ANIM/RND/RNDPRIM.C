/* FILE NAME   : RNDPRIM.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Konstantin Frolov.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'KF5'.
*/

#include "..\..\DEF.H"
#include "../anim.h"
#include <string.h>
#include <stdio.h>

BOOL KF5_RndPrimCreate(kf5PRIM *Pr, INT NoofV, INT NoofI)
{
  INT size;

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(kf5PRIM));


  /* Calculate memory size for primitive data */
  size = sizeof(kf5VERTEX) * NoofV + sizeof(INT) * NoofI;

  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
      return FALSE;

  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);

  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);

  /* Store data sizes */
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'KF5_RndPrimCreate' function */

VOID KF5_RndPrimFree(kf5PRIM *Pr)
{
  if (Pr->V != NULL)
      free(Pr->V);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(kf5PRIM));
} /* End of 'KF5_RndPrimFree' function */

VOID KF5_RndPrimDraw(kf5PRIM *Pr, MATR World)
{
  INT i;
  MATR M = MatrMulMatr3(Pr->Trans, World, KF5_RndMatrVP);

  KF5_RndCounterPrims++;
  KF5_triangles += Pr->NumOfI / 3;
  /* Allocate memory for projections */

    /* Set transform matrix */
  glLoadMatrixf(M.A[0]);

  /* Draw all triangles */
  glBegin(GL_TRIANGLES);
  for (i = 0; i < Pr->NumOfI;)
  {

    glVertex3fv(&Pr->V[Pr->I[i++]].P.X);
    glVertex3fv(&Pr->V[Pr->I[i++]].P.X);
    glVertex3fv(&Pr->V[Pr->I[i++]].P.X);
  }
  glEnd();
  
} /* End of 'KF5_RndPrimDraw' function */


BOOL KF5_RndPrimLoad(kf5PRIM *Pr, CHAR *FileName)
{
  INT nv, nf;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(kf5PRIM));

  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
      return FALSE;

  /* Count vertex and facet quantity */
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      if (Buf[0] == 'v' && Buf[1] == ' ')
          nv++;
      else if (Buf[0] == 'f' && Buf[1] == ' ')
          nf++;

  /* Create primitive */
  if (!KF5_RndPrimCreate(Pr, nv, nf * 3))
  {
      fclose(F);
      return FALSE;
  }

  /* Load primitive data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      if (Buf[0] == 'v' && Buf[1] == ' ')
      {
          DBL x, y, z;

          sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
          Pr->V[nv++].P = VecSet(x, y, z);
      }
      else if (Buf[0] == 'f' && Buf[1] == ' ')
      {
          INT n1, n2, n3;

          sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
              sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
              sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
              sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
          Pr->I[nf++] = n1 - 1;
          Pr->I[nf++] = n2 - 1;
          Pr->I[nf++] = n3 - 1;
      }
  fclose(F);
  return TRUE;
} /* End of 'KF5_RndPrimLoad' function */

/*End of RNDPRIM.C*/