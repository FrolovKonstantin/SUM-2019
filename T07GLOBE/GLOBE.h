#define PI 3.14159265358979323846
#include <windows.h>

typedef struct
{
  DOUBLE X, Y, Z;
}VEC;

VOID GLOBE( void );
VOID DRAW (HDC hDC, INT w, INT h);

