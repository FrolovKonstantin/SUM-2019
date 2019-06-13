/* FILE NAME   : IMPUT.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Konstantin Frolov.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'KF5'.
 */

#include "anim.h"
#define KF5_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)


VOID KF5_AnimJoystickInit( VOID )
{
  KF5_AnimJoystickResponse();
}/*KF5_AnimJoystickInit func*/

VOID KF5_AnimJoystickResponse( VOID )
{
  INT i;

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          KF5_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          KF5_Anim.JButClick[i] = KF5_Anim.JBut[i] && !KF5_Anim.JButOld[i];
          KF5_Anim.JButOld[i] = KF5_Anim.JBut[i];
        }

        /* Axes */
        KF5_Anim.JX = KF5_GET_JOYSTIC_AXIS(X);
        KF5_Anim.JY = KF5_GET_JOYSTIC_AXIS(Y);
        KF5_Anim.JZ = KF5_GET_JOYSTIC_AXIS(Z);
        KF5_Anim.JR = KF5_GET_JOYSTIC_AXIS(R);
        

        /* Point of view */
        KF5_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}   /*KF5_AnimJoystickResponse func*/