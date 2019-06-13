/* FILE NAME   : U_Giorno_Giovanna.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#include "units.h"

/* Giorno_Giovanna unit type */
typedef struct
{
  KF5_UNIT_BASE_FIELDS;
  kf5PRIM Giorno_Giovanna;
} kf5UNIT_Giorno_Giovanna;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitInit( kf5UNIT_Giorno_Giovanna *Uni, kf5ANIM *Ani )
{
  KF5_AnimJoystickInit();
  KF5_RndPrimLoad(&Uni->Giorno_Giovanna, "Giorno_Giovanna.obj");
} /* End of 'KF5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitClose( kf5UNIT_Giorno_Giovanna *Uni, kf5ANIM *Ani )
{
  KF5_RndPrimFree(&Uni->Giorno_Giovanna);
} /* End of 'KF5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitResponse( kf5UNIT_Giorno_Giovanna *Uni, kf5ANIM *Ani )
{
} /* End of 'KF5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       kf5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       kf5ANIM *Ani;
 * RETURNS: None.
 */
static VOID KF5_UnitRender( kf5UNIT_Giorno_Giovanna *Uni, kf5ANIM *Ani )
{
  MATR m;
  KF5_AnimJoystickResponse();

  m = MatrMulMatr3(MatrScale(VecSet(0.3, 0.3, 0.3)),
                   MatrTranslate(VecSet(8 * KF5_Anim.JX, -40 -8 * KF5_Anim.JY, -8 * KF5_Anim.JZ)),
                   MatrRotateY(-90 + 90 * KF5_Anim.JR));
  KF5_RndPrimDraw(&Uni->Giorno_Giovanna, m);
} /* End of 'KF5_UnitRender' function */

/* Giorno_Giovanna unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kf5UNIT *) pointer to created unit.
 */
kf5UNIT * KF5_UnitGiorno_GiovannaCreate( VOID )
{
  kf5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = KF5_AnimUnitCreate(sizeof(kf5UNIT_Giorno_Giovanna))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)KF5_UnitInit;
  Uni->Close = (VOID *)KF5_UnitClose;
  Uni->Response = (VOID *)KF5_UnitResponse;
  Uni->Render = (VOID *)KF5_UnitRender;
  return Uni;
} /* End of 'KF5_AnimUnitCreate' function */
