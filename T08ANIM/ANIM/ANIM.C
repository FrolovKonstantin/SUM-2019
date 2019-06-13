/*  *FILENAME: ANIM.c 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "..\DEF.h"
#include "ANIM.h"

kf5ANIM KF5_Anim;

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

VOID KF5_AnimUnitAdd(kf5UNIT *Uni)
{
  if (KF5_Anim.NumOfUnits < KF5_MAX_UNITS)
    KF5_Anim.Units[KF5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &KF5_Anim); 
}

VOID KF5_AnimCopyFrame(HDC hDC)
{
  KF5_RndCopyFrame(hDC);
}

VOID KF5_AnimEnd( VOID )
{

}

VOID KF5_AnimResize(INT w, INT h)
{
  KF5_RndResize(w, h);
}

VOID KF5_AnimInit (HWND hWnd)
{
  KF5_RndInit(hWnd);
}


/* End of "ANIM.c" function */