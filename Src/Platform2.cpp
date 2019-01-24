////
//  Platform2.mm
//  Game1
//
//  Created by Daudel, Jeffrey L on 4/26/14.
//  Copyright (c) 2014 Daudel, Jeffrey L. All rights reserved.
//

#include "Platform2.h"
#include <vector>
#include <fstream>

std::string roundDecimal( float64 v, int32 numDecimals )
{
	float64 exp = pow( 10, numDecimals );
	int64 v2 = static_cast< int64 >( v * exp );
	
	std::string s = std::to_string( v2 );
	
	if (numDecimals > 0)
	{
		for( ; s.length() < 3; )
		{
			s = std::string( "0" ) + s;
		}
	}
	
	std::string result = s.substr( 0, s.length() - numDecimals );
	
	if (numDecimals > 0)
	{
		result += "." + s.substr( s.length() - numDecimals, numDecimals );
	}
	
	return( result );
}

bool errorCheck( std::istream& istr, const char* str )
{
	std::string s;
	istr >> s;
	errorCheck( s == str );
	return( true );
}

