/*  *FILENAME: UNITS.c 
    *PROGRAMMER: Frolov Konstantin
    *DATE: 11.06.2019 
    *PURPOSE: project*/

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitInit( kf5UNIT *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitClose( kf5UNIT *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitResponse( kf5UNIT *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitRender( kf5UNIT *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (kf5UNIT *) pointer to created unit.
 */
kf5UNIT * KF5_AnimUnitCreate( INT Size )
{
  kf5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(kf5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = KF5_UnitInit;
  Uni->Close = KF5_UnitClose;
  Uni->Response = KF5_UnitResponse;
  Uni->Render = KF5_UnitRender;
  return Uni;
} /* End of 'KF5_AnimUnitCreate' function */

/* End of "UNITS.c" function */