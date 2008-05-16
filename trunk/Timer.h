#ifndef TIMER_H
#define TIMER_H

class Timer 
{
public:

	Timer(float timeInterval, bool tickImmediately = false)
		: m_fTimeInterval(timeInterval),
		  m_fCurrentTime(timeInterval)
	{
		if (tickImmediately)
			m_fCurrentTime = 0.0f;
	}

	~Timer()
	{

	}

	void Update(float dt)
	{
		m_fCurrentTime -= dt;
		
	}

	void SetTickInterval(float interval)
	{
		m_fTimeInterval = interval;
		Reset();

	}

	void Reset()
	{
		m_fCurrentTime = m_fTimeInterval;
	
	}

	bool Tick() 
	{
		if (m_fCurrentTime <= 0.0f)
		{
			Reset();
			return true;
		}

		return false;
	}

private:

	float m_fTimeInterval;
	float m_fCurrentTime;

};

#endif