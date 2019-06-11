/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#ifndef __ANIM_H_
#define __ANIM_H_
#include "..\DEF.h"
#include "ANIM.h"
#include "RND/RND.h"


#define KF5_MAX_UNITS 3000
//#define UNIT_BASE_FIELDS \
//  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
//  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
//  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
//  VOID (*Render)( UNIT *Uni, ANIM *Ani )


typedef struct tagKF5_UNIT KF5_UNIT;
typedef struct tagKF5_ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  KF5_UNIT *Units[KF5_MAX_UNITS];
  INT NumOfUnits;
} KF5_ANIM;

typedef struct tagKF5_UNIT
{
  VOID (*Init)( KF5_UNIT *Uni, KF5_ANIM *Ani );     
  VOID (*Close)( KF5_UNIT *Uni, KF5_ANIM *Ani );     
  VOID (*Response)( KF5_UNIT *Uni, KF5_ANIM *Ani );  
  VOID (*Render)( KF5_UNIT *Uni, KF5_ANIM *Ani );
};

DBL
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
BOOL 
  IsPause;                     /* Pause flag */

KF5_ANIM KF5_Anim;
#endif
/* End of "ANIM.h" function */