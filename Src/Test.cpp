
/////////////////////////////////////////////
// A Light weight exclusive / inclusive performance counter
// Main test file for profiler
///////////////////////////////////////////////

#include "Profile.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>


int main()
{
	// start a profile session
	ProfileManager* prof = ProfileManager::getSingleton();
	prof->setEnable(true);
	prof->startSession();


	for( int32 parent = 0; parent < 5; ++ parent )
	{
		PROFILE_MARKER("parent_1");
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		for( int32 child = 0; child < 10; ++ child )
		{ 
			PROFILE_MARKER("child_1");
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	std::string results;
	prof->getResults(results);
	std::cout << results.c_str() << std::endl;

	return 0;
}

