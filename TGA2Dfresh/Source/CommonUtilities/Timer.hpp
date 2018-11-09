#pragma once
#include <chrono>

//#define MIN(a,b) (((a)<(b)) ? a : b)

class Timer
{
public:
	Timer();
	Timer(const Timer &aTimer) = delete;
	Timer& operator=(const Timer &aTimer) = delete;

	float GetDeltaTime();
	double GetTotalTime();
	void Update();

private:
	std::chrono::high_resolution_clock::time_point myStartTime;
	std::chrono::high_resolution_clock::time_point myCurrentTime;
	std::chrono::high_resolution_clock::time_point myLastFrame;

	float myDeltaTime;
	double myTotalTime;
};