/* FILENAME: ANIM.h 
 * PROGRAMMER: Kiselev Igor
 * DATE: 11.06.2019 
 * PURPOSE: project
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "RND/RND.h"

#define KF5_MAX_UNITS 3000

#define KF5_UNIT_BASE_FIELDS \
  VOID (*Init)( kf5UNIT *Uni, kf5ANIM *Ani );      \
  VOID (*Close)( kf5UNIT *Uni, kf5ANIM *Ani );     \
  VOID (*Response)( kf5UNIT *Uni, kf5ANIM *Ani );  \
  VOID (*Render)( kf5UNIT *Uni, kf5ANIM *Ani )


typedef struct tagkf5UNIT kf5UNIT;
typedef struct tagkf5ANIM
{ 
  HWND hWnd;                     /* Work window handle */
  HDC hDC;                       /* Work window device context */
  HGLRC hRC;                     /* OpenGL rendering context */
  INT W, H;                      /* Frame size */
  kf5UNIT *Units[KF5_MAX_UNITS];
  INT NumOfUnits;

  /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL 
    IsPause;                     /* Pause flag */
  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */
} kf5ANIM;
typedef struct tagkf5UNIT
{
  VOID (*Init)( kf5UNIT *Uni, kf5ANIM *Ani );     
  VOID (*Close)( kf5UNIT *Uni, kf5ANIM *Ani );     
  VOID (*Response)( kf5UNIT *Uni, kf5ANIM *Ani );  
  VOID (*Render)( kf5UNIT *Uni, kf5ANIM *Ani );

};

extern kf5ANIM KF5_Anim;

VOID KF5_AnimInit( HWND hWnd );
VOID KF5_AnimClose( VOID );

VOID KF5_AnimResize(INT w, INT h);

VOID KF5_AnimRender( VOID );
VOID KF5_AnimCopyFrame(HDC hDC);
VOID KF5_AnimUnitAdd(kf5UNIT *Uni);

kf5UNIT * KF5_AnimUnitCreate( INT size);

VOID KF5_TimerInit( VOID );
VOID KF5_TimerResponse( VOID );

VOID KF5_AnimJoystickInit( VOID );
VOID KF5_AnimJoystickResponse( VOID );

#endif
/* End of "ANIM.h" function */