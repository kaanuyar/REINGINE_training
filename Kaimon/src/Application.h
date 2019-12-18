#pragma once

#include "Timer.h"
#include "Game.h"
#include <thread>
#include <atomic>
#include <iostream>

class Application
{
public:
	Application();
	void runLoop();
	void checkForUserInput(std::atomic<bool>& isProgramFinished);

private:
	Game m_game;
	Timer m_timer;
	std::atomic<bool> m_isProgramFinished;
};