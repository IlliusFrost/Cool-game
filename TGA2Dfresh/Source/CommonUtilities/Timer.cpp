#include "stdafx.h"
#include <iostream>
#include "Timer.hpp"
#include <chrono>

Timer::Timer()
{
	myStartTime = std::chrono::high_resolution_clock::now();
	myLastFrame = myStartTime;
}

void Timer::Update()
{
	myCurrentTime = std::chrono::high_resolution_clock::now();
	myDeltaTime = static_cast<float> (std::chrono::duration_cast<std::chrono::microseconds>(myCurrentTime - myLastFrame).count()) / 1000000;
	myTotalTime = (static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(myCurrentTime - myStartTime).count())) / 1000000;
	myLastFrame = myCurrentTime;
}

float Timer::GetDeltaTime()
{
	return myDeltaTime;
}

double Timer::GetTotalTime()
{
	return myTotalTime;
}