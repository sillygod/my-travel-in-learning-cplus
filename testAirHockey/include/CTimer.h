//CTimer.h

#ifndef CTIMER_H
#define CTIMER_H

#include "main.h"


const ULONG MAX_SAMPLE_COUNT = 50; // Maximum frame time sample count


class CTimer
{
	public:
		CTimer();
		virtual ~CTimer();

		void	        Tick( float fLockFPS = 0.0f );
		unsigned long   GetFrameRate( LPTSTR lpszString = NULL ) const;
		float           GetTimeElapsed() const;

	private:

		bool            mPerfHardware;             // Has Performance Counter
		float           mTimeScale;                // Amount to scale counter
		float           mTimeElapsed;              // Time elapsed since previous frame
		__int64         mCurrentTime;              // Current Performance Counter
		__int64         mLastTime;                 // Performance Counter last frame
		__int64         mPerfFreq;                 // Performance Frequency

		float           mFrameTime[MAX_SAMPLE_COUNT];
		ULONG           mSampleCount;

		unsigned long   mFrameRate;                // Stores current framerate
		unsigned long   mFPSFrameCount;            // Elapsed frames in any given second
		float           mFPSTimeElapsed;           // How much time has passed during FPS sample

};



#endif //CTIMER_H
