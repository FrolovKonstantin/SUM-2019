/* FILE NAME   : U_Text.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */
#include <stdio.h>
#include "units.h"

/* Text unit type */
typedef struct
{
  KF5_UNIT_BASE_FIELDS;
} kf5UNIT_Text;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Text *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitInit( kf5UNIT_Text *Uni, kf5ANIM *Ani )
{
  HFONT hFnt, hOldFnt;

  hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_SCRIPT, "Bookman Old Style");
  hOldFnt = SelectObject(KF5_Anim.hDC, hFnt);
  wglUseFontBitmaps(KF5_Anim.hDC, 0, 256, 102);
  hOldFnt = SelectObject(KF5_Anim.hDC, hOldFnt);
  DeleteObject(hFnt);
} /* End of 'KF5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Text *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitClose( kf5UNIT_Text *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Text *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitResponse( kf5UNIT_Text *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Text *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitRender(kf5UNIT_Text *Uni, kf5ANIM *Ani )
{ 
  char Buf[100];
  int len;

  glLoadIdentity();
  glColor3d(1, 1, 1);
  glRasterPos2d(-0.9, 0.9);
  glListBase(102);
  len = sprintf(Buf, "FPS: %.3f, primitives: %i, triangles: %i", Ani->FPS, KF5_RndCounterPrims, KF5_triangles);
  glCallLists(len, GL_UNSIGNED_BYTE, Buf);
} /* End of 'KF5_UnitRender' function */

/* Text unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kf5UNIT *) pointer to created unit.
 */
kf5UNIT * KF5_UnitTextCreate( VOID )
{
  kf5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = KF5_AnimUnitCreate(sizeof(kf5UNIT_Text))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)KF5_UnitInit;
  Uni->Close = (VOID *)KF5_UnitClose;
  Uni->Response = (VOID *)KF5_UnitResponse;
  Uni->Render = (VOID *)KF5_UnitRender;
  return Uni;
} /* End of 'KF5_AnimUnitCreate' function */
