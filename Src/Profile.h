// Light Profiler


#ifndef _PROFILE_H
#define _PROFILE_H

#include "Types.h"

#include <vector>

class ProfileMarker;

class ProfileStat
{
public:
	
	ProfileStat( const char* name );
	void clear();
	
	float64 mInclusiveTime;
	float64 mExclusiveTime;
	int64 mCount;
	const char* mName;
	
};

class ProfileManager
{
public:
	
	static ProfileManager* getSingleton();
	
	// allocate a new stat to track
	int32 newStat( const char* name );
	void start( ProfileMarker* marker );
	void end( ProfileMarker* marker );
	
	void setEnable( bool enable );
	void startSession();
	void getResults( std::string& resultOut );
	
	
private:
	
	ProfileManager();
	~ProfileManager();
	
	std::vector< ProfileMarker* > mMarkers;
	std::vector< ProfileStat > mStats;
	
	float64 mSessionStart = 0;
	bool mEnable = false;
	
};

#define PROFILE_MARKER( name ) static int32 markerId ## __LINE__\
	= ProfileManager::getSingleton()->newStat( name );\
	ProfileMarker __marker ## __LINE__ ( markerId ## __LINE__ );


class ProfileMarker
{
public:
	
	inline ProfileMarker( int32 id )
	{
		mId = id;
		ProfileManager::getSingleton()->start( this );
	}
	
	~ProfileMarker()
	{
		ProfileManager::getSingleton()->end( this );
	}
	
	int32 mId;
	float64 mStartTime;
	float64 mChildTime;
	
private:

};


#endif
