/*Frolov Konstantin, 05.06.2019*/
#include <stdio.h>
#include <windows.h>
#define MAX 8

INT P[MAX];
BOOL isParity = 1;

VOID swap (INT *a, INT *b)
{                                                       
    INT tmp = *a;

    *a = *b;
    *b = tmp;
}

VOID Store( VOID )
{
  FILE *f;
  int i;

  f = fopen("PERM.txt", "a");

  if (f == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(f, "%d,", P[i]);
  fprintf(f, "%d parity %s\n", P[MAX - 1], isParity ? "even" : "odd");
}

VOID Go( int pos)
{
  INT i, x;
  BOOL save_parity;


  if (pos == MAX)
    Store();
  else 
  {
    save_parity = isParity;
    Go(pos + 1);
    for (i = pos + 1; i < MAX; i++ )
    {
      swap (&P[pos], &P[i]);
      if (isParity == 0 && i != pos )
        isParity = 1;
      else if (isParity == 1 && i != pos)
        isParity = 0;
      Go(pos + 1);
    }
    x = P[pos];
    for (i = pos + 1; i < MAX; i++)
    P[i -1] = P[i];
    P[MAX - 1] = x;
    isParity = save_parity;
  }
}


VOID main( void )
{
  int i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;

  Go(0);
}
