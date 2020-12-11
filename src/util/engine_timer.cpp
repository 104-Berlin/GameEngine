#include "Engine.h"

using namespace Engine;

using namespace std::chrono;

ETimer::ETimer()
{
	last = steady_clock::now();
}

float ETimer::Reset()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}