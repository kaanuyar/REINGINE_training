#include "Application.h"

Application::Application()
	: m_game(),  m_isProgramFinished(false)
{
}

void Application::runLoop()
{
	std::thread userInputThread(&Application::checkForUserInput, this,  std::ref(m_isProgramFinished));
	while (!m_isProgramFinished)
	{
		float deltaTime = m_timer.getDeltaTimeClock();
		m_timer.countDeltaTimeTowardsFPS(deltaTime);

		if (deltaTime > 0.2f)
			deltaTime = 0.2f;

		m_game.update(deltaTime);
	}

	userInputThread.join();
}

void Application::checkForUserInput(std::atomic<bool>& isProgramFinished)
{
	std::string s;
	s = std::cin.get();
	if (!s.empty())
		isProgramFinished = true;
}
