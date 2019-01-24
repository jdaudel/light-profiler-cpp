////
//  Light Profiler
//////////////////

#include "Profile.h"
#include "Platform.h"
#include "Platform2.h"
#include <string>
#include <algorithm>

ProfileStat::ProfileStat( const char* name )
{
	mName = name;
	clear();
}

void ProfileStat::clear()
{
	mInclusiveTime = 0;
	mExclusiveTime = 0;
	mCount = 0;
}

static ProfileManager* gProfilerManager = nullptr;

ProfileManager::ProfileManager()
{}

ProfileManager::~ProfileManager()
{}

ProfileManager* ProfileManager::getSingleton()
{
	if (gProfilerManager == nullptr)
	{
		gProfilerManager = new ProfileManager();
	}
	
	return( gProfilerManager );
}

void ProfileManager::setEnable( bool enable )
{
	mEnable = enable;
}

int32 ProfileManager::newStat( const char* name )
{
	int32 id = mStats.size();
	mStats.push_back( ProfileStat( name ) );
	return( id );
}

void ProfileManager::start( ProfileMarker* marker )
{
	if (mEnable == false)
	{
		return;
	}
	
	errorCheck( marker->mId < mStats.size() );
	ProfileStat& stat = mStats[ marker->mId ];
	
	marker->mStartTime = getTimer();
	marker->mChildTime = 0;
	
	mMarkers.push_back( marker );
	stat.mCount++;
}

void ProfileManager::end( ProfileMarker* marker )
{
	if (mEnable == false)
	{
		return;
	}
	
	ProfileMarker* last = mMarkers[ mMarkers.size() - 1 ];
	errorCheck( last == marker );
	mMarkers.pop_back();
	
	ProfileStat& stat = mStats[ marker->mId ];
	float64 time = getTimer() - marker->mStartTime;
	errorCheck( time >= 0 );
	
	stat.mInclusiveTime += time;
	
	// update exclusive (full time - child time)
	errorCheck( time >= marker->mChildTime );
	stat.mExclusiveTime += (time - marker->mChildTime);
	
	// update childTime
	if (mMarkers.size() > 0 )
	{
		ProfileMarker* parentMarker = mMarkers[ mMarkers.size() - 1 ];
		parentMarker->mChildTime += time;
	}
		
}

void ProfileManager::startSession()
{
	// must not be profiling
	errorCheck( mMarkers.size() == 0 );
	
	for( ProfileStat& stat : mStats )
	{
		stat.clear();
	}
	
	mSessionStart = getTimer();
}

void ProfileManager::getResults( std::string& resultOut )
{
	// sort them
	std::vector< ProfileStat > stats;
	for( ProfileStat& stat : mStats )
	{
		stats.push_back( stat );
	}
	
	std::sort( stats.begin(), stats.end(), []( const ProfileStat& s1, const ProfileStat& s2 )
			  {
				  return( s1.mInclusiveTime > s2.mInclusiveTime );
			  });
	
	float64 sessionTime = getTimer() - mSessionStart;
	std::string& s = resultOut;
	s += "session time: " + std::to_string( sessionTime * 1000 ) + " ms\n";
	
	for( ProfileStat& stat : stats )
	{
		float64 incPercent = stat.mInclusiveTime / sessionTime * 100;
		float64 excPercent = stat.mExclusiveTime / sessionTime * 100;

		s += std::string() + stat.mName + ", inc: " + roundDecimal( stat.mInclusiveTime * 1000, 2 ) + " ms"
			+ " (" + roundDecimal( incPercent, 1 ) + "%)"
			+ ", exc: " + roundDecimal( stat.mExclusiveTime * 1000, 2 ) + " ms"
			+ " (" + roundDecimal( excPercent, 1 ) + "%)"
			+ ", count: " + std::to_string( stat.mCount ) + "\n";
	}
	
}
