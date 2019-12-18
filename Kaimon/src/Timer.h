#pragma once
#include <thread>
#include <chrono>
#include <iostream>

class Timer
{
public:
	void countDeltaTimeTowardsFPS(float deltaTime)
	{
		m_frameCounter++;
		m_frameCounterTime += deltaTime;
		if (m_frameCounterTime > 1.0f)
		{
			m_currentFPS = m_frameCounter;
			m_frameCounter = 0;
			m_frameCounterTime = 0.0f;

			std::cout << "FPS: " << m_currentFPS << std::endl;
			// comment previous line if you dont want to see FPS count spammed
		}
	}

	float getDeltaTimeClock()
	{
		clock_t currentFrameTime = clock();
		clock_t deltaTime = currentFrameTime - m_lastFrameClock;
		m_lastFrameClock = currentFrameTime;
		return (float)clockToSeconds(deltaTime);
	}

	float getDeltaTimeClock(float deltaTimeLimit)
	{
		clock_t currentFrameTime = clock();
		clock_t deltaTime = currentFrameTime - m_lastFrameClock;

		while ((float) clockToSeconds(deltaTime) < deltaTimeLimit)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			currentFrameTime = clock();
			deltaTime = currentFrameTime - m_lastFrameClock;
		}

		m_lastFrameClock = currentFrameTime;
		return (float) clockToSeconds(deltaTime);
	}

	bool isDeltaTimeFromLastRestartClock(float timeLimit)
	{
		clock_t currentFrameTime = clock();
		clock_t deltaTime = currentFrameTime - m_lastRestartTimeClock;
		float deltaTimeFloat = (float)clockToSeconds(deltaTime);
		if (deltaTimeFloat > timeLimit)
		{
			m_lastRestartTimeClock = currentFrameTime;
			return true;
		}
		return false;
	}

	double clockToSeconds(clock_t ticks) { return (ticks / (double)CLOCKS_PER_SEC)*1.0; }
	void setLastRestartTimeToCurrentTimeClock() { m_lastRestartTimeClock = clock(); }

private:
	float m_frameCounterTime = 0.0f;
	int m_frameCounter = 0;
	int m_currentFPS = 0;

	clock_t m_lastFrameClock = clock();
	clock_t m_lastRestartTimeClock = clock();
};