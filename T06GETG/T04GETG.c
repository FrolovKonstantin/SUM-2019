/*Frolov Konstantin, 05.06.2019*/
#include <stdio.h>
#include <windows.h>
#define MAX 4
#include <math.h>

INT P[MAX];
BOOL isParity = 1;
DOUBLE A[MAX][MAX];
INT N;
DOUBLE det, GDET;
FILE *f;


VOID swap (INT *a, INT *b)
{                                                       
    INT tmp = *a;

    *a = *b;
    *b = tmp;
}


BOOL LOADMRTX (CHAR *fname)
{
  int i, j;
  N = 0;

  f = fopen (fname, "r");

  if (f == NULL)
    return FALSE;
  fscanf(f, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(f, "%lf", &A[i][j]);
  fclose(f);
  return TRUE;
}

INT Store( VOID )
{
  int i;
  double prod;

  for (i = 0, prod = 1; i < N; i++)
    prod *= A[i][P[i]];
  det += (isParity ? 1 : -1) * prod;
  return 1;
}

VOID Go( int pos)
{
  int i, x;
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
  
VOID GAUS( void )
{
  float coef;
  INT i, j, max_r, max_c, y, x, k;
  DOUBLE GDET = 1;

  for (i = 0; i < N; i++)
  {
    max_r = max_c = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_r][max_c]))
          max_c = x, max_r = y;
    if (A[max_r][max_c] == 0)
    {
      GDET = 0;
      break;
    }
    if (max_r != i)
    {
      for (x = i; x < N; x++)
        swap(&A[i][x], &A[max_r][x]);
      GDET = -GDET;
    }
    if (max_c != i)
    {
      for (y = i; y < N; y++)
        swap(&A[y][i], &A[y][max_c]);
      GDET = -GDET;
    }
    coef = A[j][i] / A[i][i];
    A[j][i] = 0;
    for (k = i + 1; k < N; k++)
      A[j][k] -= A[i][k] * coef;
  }
  GDET *= A[i][i];
}


VOID main( void )
{
  int i;

  for (i = 0; i < MAX; i++)
    P[i] = i;
  LOADMRTX("IN.txt");
  Go(0);
  GAUS();
  printf("determinat is %f", det);
  printf("determinat is %f", GDET);
  getchar();
}
