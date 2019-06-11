/*  *FILENAME: UNITS.c 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "..\DEF.h"
#include "ANIM.h"


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KF5_UNIT *Uni;
 *   - animation context:
 *       KF5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitInit( KF5_UNIT *Uni, KF5_ANIM *Ani )
{
} /* End of 'KF5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KF5_UNIT *Uni;
 *   - animation context:
 *       KF5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitClose( KF5_UNIT *Uni, KF5_ANIM *Ani )
{
} /* End of 'KF5_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KF5_UNIT *Uni;
 *   - animation context:
 *       KF5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitResponse( KF5_UNIT *Uni, KF5_ANIM *Ani )
{
} /* End of 'KF5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KF5_UNIT *Uni;
 *   - animation context:
 *       KF5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitRender( KF5_UNIT *Uni, KF5_ANIM *Ani )
{
} /* End of 'KF5_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (KF5_UNIT *) pointer to created unit.
 */
KF5_UNIT * KF5_AnimUnitCreate( INT Size )
{
  KF5_UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(KF5_UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = KF5_UnitInit;
  Uni->Close = KF5_UnitClose;
  Uni->Response = KF5_UnitResponse;
  Uni->Render = KF5_UnitRender;
  return Uni;
} /* End of 'KF5_AnimUnitCreate' function */



/*   Тут живёт странный и непонятный кусок функции
static VOID KF5_UnitInit( IK3UNIT_BALL *Uni, IK3ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} 
static VOID KF5_UnitResponse( IK3UNIT_BALL *Uni, IK3ANIM *Ani );
{
  Uni->Pos += Ani->DeltaTime * 2.4;
}  */


/* End of "UNITS.c" function */