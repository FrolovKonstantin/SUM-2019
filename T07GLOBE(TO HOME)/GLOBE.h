#define PI 3.14159265358979323846
#include <windows.h>
#define N 30
#define M 37

typedef struct
{
  DOUBLE X, Y, Z;
}VEC;

VOID GLOBE( void );
VOID DRAW (HDC hDC, INT w, INT h);
VEC ROT_X(VEC p, DOUBLE angle);
VEC ROT_Y(VEC p, DOUBLE angle);
