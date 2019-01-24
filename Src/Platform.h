
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "Types.h"
#include <functional>

// can be used for low and high res timers
float64 getTimer();

void errorCheck( bool expr );
void errorMsg( const char* msg );
void errorMsg( const std::string& msg );
void setErrorHandler( std::function< void() > handler );

bool fuzzyCompare( float32 v1, float32 v2, float32 tolerance );
bool isBounded( float32 v, float32 min, float32 max );

// get a normalized parameter. Range is [0 - 1].
// 0 - start, 1 - end
float64 normalizeT( float64 startValue, float64 endValue, float64 prevT );

// interpolate linearly between value0 and value1 by v [0, 1]
float64 interpolate( float64 value0, float64 value1, float64 t );

// polynomial interlopation
// degree = 0 = linear interpolation
float64 interpolatePoly( float64 value0, float64 value1, float64 v,
						float64 polyDegree );

// return a random number [0, 1]
float64 rand1();

// random float between [min, max]
float64 randFloat( float64 min, float64 max );

// random int between [min, max]
int32 randInt( int32 min, int32 max );

void quadratic( float64 a, float64 b, float64 c,
			   int32& numSolsOut, float64& sol1Out, float64& sol2Out );

float64 cap( float64 v, float64 min, float64 max );
float64 capMin( float64 v, float64 min );
float64 capMax( float64 v, float64 max );

int32 round( int32 value, int32 to );

// returns -1 if val < 0
// returns 1 if val > 0
// return s 0 if val == 0
template< typename T >
int32 sign( T val )
{
	return( (T(0) < val) - (val < T(0)));
}

#endif

