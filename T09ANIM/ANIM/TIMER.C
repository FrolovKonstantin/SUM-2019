/* FILE NAME   : TIMER.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Konstantin Frolov.
* LAST UPDATE : 11.06.2019.
* NOTE        : Module prefix 'KF5'.
*/
#include "..\DEF.h"
#include "ANIM.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID KF5_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  KF5_Anim.IsPause = FALSE;
  KF5_Anim.FPS = 30.0;
  PauseTime = 0;
}/*KF5_TimerInit func*/

VOID KF5_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  KF5_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  KF5_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (KF5_Anim.IsPause)
  {
    KF5_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    KF5_Anim.DeltaTime = KF5_Anim.GlobalDeltaTime;
    KF5_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    KF5_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /*KF5_TimerResponse func*/