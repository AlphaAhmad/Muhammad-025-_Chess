#include"Timer.h"

namespace EngineUtils
{
	timer* timer::sInstance = nullptr;

	timer* timer::Instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new timer();
		}
		return 0; // Check this return value its not this;
	}

	void timer::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	timer::timer()
	{
		Reset();
		mTimeScale = 1.0f;
		mDeltaTime = std::chrono::duration<float>(0.0f);


	}
	timer::~timer()
	{

	}

	void timer::Reset()
	{
		mStartTiMe = std::chrono::system_clock::now();
	}

	float timer::DeltaTime()
	{
		return mDeltaTime.count();
	}

	void timer::TimeScale(float t)
	{
		mTimeScale = t;
	}

	float timer::TimeScale()
	{
		return mTimeScale;
	}

	void timer:: tick()
	{
		mDeltaTime = std::chrono::system_clock::now() - mStartTiMe;
	}
	
		
}



