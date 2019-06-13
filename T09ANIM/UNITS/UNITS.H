/* FILE NAME   : UNITS.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Konstantin Frolov.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'KF5'.
*/
#ifndef __UNITS_H_
#define __UNITS_H_

#include "../anim/anim.h"

/* Giorno_Giovanna unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (kf5UNIT *) pointer to created unit.
 */
kf5UNIT * KF5_UnitGiorno_GiovannaCreate( VOID );
kf5UNIT * KF5_UnitTextCreate( VOID );
kf5UNIT * KF5_UnitCowCreate( VOID );

#endif 