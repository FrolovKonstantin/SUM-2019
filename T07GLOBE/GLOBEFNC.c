#include "GLOBE.h"
#include <math.h>
#define N 12
#define M 27

VOID GLOBE( void )
{
  INT R = 300, Cx = 0, Cy = 0, i, j;
  DOUBLE TET, FI;
  VEC G[N][M];

  for (i = 0, TET = 0; i < N; i++, TET += PI / N)
    for (j = 0, FI = 0; j < M; j++, FI += 2 * PI / M)
    {
      G[i][j].X = Cx + R *sin(TET) * sin(FI);
      G[i][j].Y = Cy + R * cos(TET);
      G[i][j].Z = R * sin(TET) * cos(FI);
    }
}

VOID DRAW (HDC hDC, INT w, INT h)
{
  INT x, y, i, j;
  VEC G[N][M];

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
       VEC p = G[i][j];
       x = (INT)p.X + w / 2;
       y = (INT)p.Y + h / 2;
       SelectObject (hDC, GetStockObject(NULL_PEN));
       SelectObject (hDC, GetStockObject(DC_BRUSH));
       SetDCBrushColor(hDC, RGB(200, 100, 60));
       Ellipse(hDC, x - 5, y -5, x + 5, y + 5);
    }
}