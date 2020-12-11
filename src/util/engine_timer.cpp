#include "Engine.h"

using namespace Engine;

using namespace std::chrono;

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Reset()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}