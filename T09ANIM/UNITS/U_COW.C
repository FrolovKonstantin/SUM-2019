/* FILE NAME   : U_Cow.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#include "units.h"

/* Cow unit type */
typedef struct
{
  KF5_UNIT_BASE_FIELDS;
  kf5PRIM Cow;
} kf5UNIT_Cow;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Cow *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitInit( kf5UNIT_Cow *Uni, kf5ANIM *Ani )
{
  KF5_AnimJoystickInit();
  KF5_RndPrimLoad(&Uni->Cow, "cow.object");
} /* End of 'KF5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Cow *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitClose( kf5UNIT_Cow *Uni, kf5ANIM *Ani )
{
  KF5_RndPrimFree(&Uni->Cow);
} /* End of 'KF5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Cow *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitResponse( kf5UNIT_Cow *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Cow *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitRender( kf5UNIT_Cow *Uni, kf5ANIM *Ani )
{
  MATR m;
  KF5_AnimJoystickResponse();

  m = MatrMulMatr3(MatrScale(VecSet(1, 1, 1)),
                   MatrTranslate(VecSet(10, - 40, -10)),
                   MatrRotateY(180));
  KF5_RndPrimDraw(&Uni->Cow, m);
} /* End of 'KF5_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kf5UNIT *) pointer to created unit.
 */
kf5UNIT * KF5_UnitCowCreate( VOID )
{
  kf5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = KF5_AnimUnitCreate(sizeof(kf5UNIT_Cow))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)KF5_UnitInit;
  Uni->Close = (VOID *)KF5_UnitClose;
  Uni->Response = (VOID *)KF5_UnitResponse;
  Uni->Render = (VOID *)KF5_UnitRender;
  return Uni;
} /* End of 'KF5_AnimUnitCreate' function */
