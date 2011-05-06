
#ifndef FRAMEWORK_TIMER_H
#define FRAMEWORK_TIMER_H

namespace Framework
{
	class Timer
	{
	public:
		enum Type
		{
			TT_LOOP,
			TT_SINGLE,
			TT_INFINITE,

			NUM_TIMER_TYPES,
		};

		/**
		Creates a timer with the given type.

		LOOP and SINGLE timers need an explicit duration. This represents the time in seconds
		through a loop, or the time in seconds until the timer expires.

		INFINITE timers ignore the duration.

		It is legal to create these statically.
		**/
		Timer(Type eType = TT_INFINITE, float fDuration = 1.0f);

		//Resets the timer, as though the user just created the object with the original parameters.
		void Reset();

		//Pauses/unpauses. Returns true if the timer is paused after the toggling.
		bool TogglePause();

		//Sets the pause state to the given value.
		void SetPause(bool pause = true);

		//Returns true if the timer is paused.
		bool IsPaused() const;

		//Updates the time for the timer. Returns true if the timer has reached the end.
		//Will only return true for SINGLE timers that have reached their duration.
		bool Update();

		//Subtracts secRewind from the current time and continues from there.
		void Rewind(float secRewind);

		//Adds secRewind to the current time and continues from there.
		void Fastforward(float secFF);

		//Returns a number [0, 1], representing progress through the duration. Only used
		//for SINGLE and LOOP timers.
		float GetAlpha() const;

		//Returns a number [0, duration], representing the progress through the timer in 
		//seconds. Only for SINGLE and LOOP timers.
		float GetProgression() const;

		//Returns the time in seconds since the timer was started, excluding
		//time for pausing.
		float GetTimeSinceStart() const;

		//Returns the timer's duration that was passed in.
		float GetDuration() const {return m_secDuration;}

	private:
		Type m_eType;
		float m_secDuration;

		bool m_hasUpdated;
		bool m_isPaused;

		float m_absPrevTime;
		float m_secAccumTime;
	};
}


#endif //FRAMEWORK_TIMER_H
