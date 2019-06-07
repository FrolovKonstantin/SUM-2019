#include "GLOBE.h"
#include <math.h>

VEC G[N][M];

VOID GLOBE( void )
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < N; i++, t += PI / (N - 1))
    for (j = 0, p = 0; j < M; j++, p += 2 * PI / (M - 1))
     {
        x = R * cos(p) * sin(t);
        y = R * cos(t);
        z = R * sin(p) * sin(t);
        
        G[i][j].X = x;
        G[i][j].Y = y;
        G[i][j].Z = z;
     }
}




VOID DRAW(HDC hDC, INT w, INT h)
{
    INT x, y, i, j, Xc = w / 2, Yc = h / 2;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            VEC p = G[i][j];
            x = (INT)p.X + w / 2;
            y = (INT)p.Y + h / 2;
            SelectObject(hDC, GetStockObject(NULL_PEN));
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB(255, 0, 0));
            Ellipse(hDC, x - 4, y - 4, x + 4, y + 4);
        }
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(0, 0, 255));
    for (i = 0; i < N; i++)
    {
        x = Xc + G[i][0].X;
        y = Yc + G[i][0].Y;
        MoveToEx(hDC, x, y, NULL);
        for (j = 1; j < M; j++)
        {
            x = Xc + G[i][j].X;
            y = Yc + G[i][j].Y;
            LineTo(hDC, x, y);
        }
    }

    for (j = 0; j < M; j++)
    {
        x = Xc + G[0][j].X;
        y = Yc + G[0][j].Y;
        MoveToEx(hDC, x, y, NULL);
        for (i = 1; i < N; i++)
        {
            x = Xc + G[i][j].X;
            y = Yc + G[i][j].Y;
            LineTo(hDC, x, y);
        }
    }
}


VEC ROT_Y(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.X = p.X * co - p.Y * si;
    r.Y = p.X * si + p.Y * co;
    r.Z = p.Z;

    return r;
}

VEC ROT_X(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.Y = p.Y  * co - p.Z * si;
    r.Z = p.Y * si + p.Z * co;
    r.X = p.X;

    return r;
}