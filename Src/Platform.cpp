
#include "Platform.h"
#include <string>
#include <assert.h>
#include <Windows.h>
//#include <chrono>

float64 getTimer()
{
	//auto time = std::chrono::system_clock::now().time_since_epoch();
	//return( time.count() );

	int64 time;
	QueryPerformanceCounter( (LARGE_INTEGER*)&time );
	int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float64 time2 = time / (float64)freq;
    return( time2 );
}

static std::function<void() > gErrorHandler = nullptr;

void setErrorHandler( std::function< void() > handler )
{
	gErrorHandler = handler;
}

void errorCheck( bool expr )
{
	if (expr == false)
	{
		errorMsg( "Failed error check" );
	}
}

void errorMsg( const char* error )
{
    printf( "%s", error );
	fflush( stdout );
	fflush( stderr );
	if (gErrorHandler == nullptr)
	{
    	assert( false );
	}
	else
	{
		gErrorHandler();
	}
}

void errorMsg( const std::string& msg )
{
	errorMsg( msg.c_str() );
}

bool fuzzyCompare( float32 v1, float32 v2, float32 tolerance )
{
	return( fabs( v1 - v2 ) <= tolerance );
}

bool isBounded( float32 v, float32 min, float32 max )
{
	return( v >= min && v <= max );
}

float64 normalizeT( float64 startValue, float64 endValue, float64 prevT )
{
	float64 t = (prevT - startValue) / (endValue - startValue);
	t = cap( t, 0, 1 );
	return( t );
}

float64 interpolate( float64 v0, float64 v1, float64 t )
{
	return( v0 + (v1 - v0) * t );
}

float64 interpolatePoly( float64 v0, float64 v1, float64 t,
								float64 polyDegree )
{
	float64 result = v0 + ((v1 - v0) * pow( t, polyDegree ));
	return( result );
}

float64 rand1()
{
	return( ((float64)rand()) / RAND_MAX );
}

float64 randFloat( float64 min, float64 max )
{
	float64 result = min + ((max - min) * rand1());
	return( result );
}

int32 randInt( int32 min, int32 max )
{
	int32 result = static_cast< int32 >( randFloat( min, max + 1));
	if (result > max)
	{
		result = max;
	}
	
	return( result );
}

void quadratic( float64 a, float64 b, float64 c,
			  int32& numSolsOut, float64& sol1Out, float64& sol2Out )
{
	if (a == 0
		&& b == 0)
	{
		numSolsOut = 0;
		return;
	}
	
	// trivial non-quadratic case
    if (a == 0)
	{
		numSolsOut = 1;
		sol1Out = -c / b;
		return;
	}
	
	float64 v = (b * b) - (4 * a * c);
	if (v < 0)
	{
		// no real solutions
		numSolsOut = 0;
	}
	else if (v == 0)
	{
		numSolsOut = 1;
		sol1Out = -b / (2 * a );
	}
	else
	{
		numSolsOut = 2;
		sol1Out = ((-b - sqrt( v )) / (2 * a));
		sol2Out = ((-b + sqrt( v )) / (2 * a));
	}
}

float64 cap( float64 v, float64 min, float64 max )
{
	float64 result = v;
	if (result < min)
	{
		result = min;
	}
	if (result > max)
	{
		result = max;
	}
	
	return( result );
}

float64 capMin( float64 v, float64 min )
{
	float64 result;
	if (v < min)
	{
		result = min;
	}
	else
	{
		result = v;
	}
	
	return( result );
}

float64 capMax( float64 v, float64 max )
{
	float64 result;
	if (v > max)
	{
		result = max;
	}
	else
	{
		result = v;
	}
	
	return( result );
}


int32 round( int32 value, int32 to )
{
	int32 remainder = (value % to);
	int32 result = value - remainder;
	
	// check if should round up
	if (remainder >= to / 2.0)
	{
		result += to;
	}
	return( result );
}

