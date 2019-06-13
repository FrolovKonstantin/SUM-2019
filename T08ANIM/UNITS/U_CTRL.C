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
  CHAR Buf[100];

  TextOut(Ani->hDC, 18, 18, Buf, sprintf(Buf, "%.3f", Ani->FPS));
  SelectObject(Ani->hDC, GetStockObject(DC_PEN));
  SetDCPenColor(Ani->hDC, RGB(123, 11, 0));
  
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
