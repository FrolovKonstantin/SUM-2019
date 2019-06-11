/*  *FILENAME: ANIM.c 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "..\DEF.h"
#include "ANIM.h"

VOID KF5_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < KF5_Anim.NumOfUnits; i++)
  {
    KF5_Anim.Units[i]->Close(KF5_Anim.Units[i], &KF5_Anim);
    free(KF5_Anim.Units[i]);
    KF5_Anim.Units[i] = NULL;
  }
  KF5_Anim.NumOfUnits = 0;
  KF5_RndClose();
}

VOID KF5_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < KF5_Anim.NumOfUnits; i++)
    KF5_Anim.Units[i]->Response(KF5_Anim.Units[i], &KF5_Anim);

  KF5_RndStart();
  for (i = 0; i < KF5_Anim.NumOfUnits; i++)
    KF5_Anim.Units[i]->Render (KF5_Anim.Units[i], &KF5_Anim);
  KF5_RndEnd();
}

/* End of "ANIM.c" function */