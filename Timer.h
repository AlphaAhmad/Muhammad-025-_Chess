#pragma once




#include<chrono>


namespace EngineUtils
{
	class timer
	{
	private:
		static timer* sInstance;
		std::chrono::system_clock::time_point mStartTiMe;
		std::chrono::duration<float> mDeltaTime;
		float mTimeScale;
	public:
		static timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();
		void TimeScale(float t = 1.0f);
		float TimeScale();

		void tick();

	private:
		timer();
		~timer();
	}; 
}



