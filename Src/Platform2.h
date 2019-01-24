

#ifndef _PLATFORM_2_H
#define _PLATFORM_2_H

#include "Types.h"
#include "Platform.h"

#include <string>
#include <map>
#include <set>

std::string roundDecimal( float64 v, int32 numDecimals );

bool errorCheck( std::istream& istr, const char* str );

#endif

