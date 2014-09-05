//CTimer.cpp

#include "CTimer.h"

//-----------------------------------------------------------------------------
// Name : CTimer () (Constructor)
// Desc : CTimer Class Constructor
//-----------------------------------------------------------------------------

CTimer::CTimer()
{
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&mPerfFreq)) //QueryPer...Frequency is definition timer
	{
		mPerfHardware=true;
		QueryPerformanceCounter((LARGE_INTEGER *) &mLastTime);
		mTimeScale= 1.0f / mPerfFreq;
	}
	else
	{
		// no performance counter, read in using timeGetTime
		mPerfHardware		= FALSE;
		mLastTime			= timeGetTime();
		mTimeScale			= 0.001f;
	}

	// Clear any needed values
    mSampleCount       = 0;
	mFrameRate			= 0;
	mFPSFrameCount		= 0;
	mFPSTimeElapsed	= 0.0f;

}

//-----------------------------------------------------------------------------
// Name : CTimer () (Destructor)
// Desc : CTimer Class Destructor
//-----------------------------------------------------------------------------
CTimer::~CTimer()
{
}

//-----------------------------------------------------------------------------
// Name : Tick ()
// Desc : Function which signals that frame has advanced
// Note : You can specify a number of frames per second to lock the frame rate
//        to. This will simply soak up the remaining time to hit that target.
//-----------------------------------------------------------------------------
void CTimer::Tick(float fLockFPS)
{
	float fTimeElapsed;

    // Is performance hardware available?
	if ( mPerfHardware )
    {
        // Query high-resolution performance hardware
		QueryPerformanceCounter((LARGE_INTEGER *)&mCurrentTime);
	}
	else
	{
		mCurrentTime=timeGetTime();
	}

	// Calculate elapsed time in seconds
	fTimeElapsed = (mCurrentTime - mLastTime) * mTimeScale;

	// Should we lock the frame rate ?
    if ( fLockFPS > 0.0f )
    {
        while ( fTimeElapsed < (1.0f / fLockFPS))
        {
            // Is performance hardware available?
	        if ( mPerfHardware )
            {
                // Query high-resolution performance hardware
		        QueryPerformanceCounter((LARGE_INTEGER*)&mCurrentTime);
	        }
            else
            {
                // Fall back to less accurate timer
		        mCurrentTime = timeGetTime();

	        } // End If no hardware available

	        // Calculate elapsed time in seconds
	        fTimeElapsed = (mCurrentTime - mLastTime) * mTimeScale;

        } // End While
    } // End If

	// Save current frame time
	mLastTime = mCurrentTime;

	// Filter out values wildly different from current average
    if ( fabsf(fTimeElapsed - mTimeElapsed) < 1.0f  )
    {
        // Wrap FIFO frame time buffer.
        memmove( &mFrameTime[1], mFrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float) );
        mFrameTime[ 0 ] = fTimeElapsed;
        if ( mSampleCount < MAX_SAMPLE_COUNT ) mSampleCount++;

    } // End if


	// Calculate Frame Rate
	mFPSFrameCount++;
	mFPSTimeElapsed += mTimeElapsed;
	if ( mFPSTimeElapsed > 1.0f)
    {
		mFrameRate			= mFPSFrameCount;
		mFPSFrameCount		= 0;
		mFPSTimeElapsed	= 0.0f;
	} // End If Second Elapsed

    // Count up the new average elapsed time
    mTimeElapsed = 0.0f;
    for ( ULONG i = 0; i < mSampleCount; i++ ) mTimeElapsed += mFrameTime[ i ];
    if ( mSampleCount > 0 ) mTimeElapsed /= mSampleCount;

}

//-----------------------------------------------------------------------------
// Name : GetFrameRate ()
// Desc : Returns the frame rate, sampled over the last second or so.
//-----------------------------------------------------------------------------
unsigned long CTimer::GetFrameRate( LPTSTR lpszString ) const
{
    // Fill string buffer ?
    if ( lpszString )
    {
        // Copy frame rate value into string
        //_itot( mFrameRate, lpszString, 10 );
		sprintf(lpszString,"%u FPS",mFrameRate);
        // Append with FPS
        //strcat( lpszString, _T(" FPS") );

    } // End if build FPS string

    return mFrameRate;
}

//-----------------------------------------------------------------------------
// Name : GetTimeElapsed ()
// Desc : Returns the amount of time elapsed since the last frame (Seconds)
//-----------------------------------------------------------------------------
float CTimer::GetTimeElapsed() const
{
    return mTimeElapsed;

}
