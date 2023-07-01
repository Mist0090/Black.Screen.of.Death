#include "system.h"

void Reflect2D ( int *x, int *y, int w, int h )
{
#define FUNCTION(v, maxv) ( abs( v ) / ( maxv ) % 2 ? ( maxv ) - abs( v ) % ( maxv ) : abs( v ) % ( maxv ) );
	*x = FUNCTION ( *x, w - 1 );
	*y = FUNCTION ( *y, h - 1 );
#undef FUNCTION
}