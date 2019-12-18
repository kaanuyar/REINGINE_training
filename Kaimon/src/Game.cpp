#include "Game.h"

Game::Game()
	:
	m_frustum(800.0f, 450.0f, 60.0f, 0.1f, 100.0f),
	m_camera(Vector3f(0.0f, 21.0f, 7.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f)),
	m_rawEntity(OBJLoader::loadFile("res/models/wallCube2.obj")),
	m_rawEntity2(OBJLoader::loadFile("res/models/tree.obj")),
	m_rawTerrain(Terrain::createTerrain(10, 10)),
	m_terrain(m_rawTerrain, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_player(this, m_rawEntity, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_target(m_rawEntity, Vector3f(MathCalc::generateRandomFloat(-9.75f, 9.75f), 0.0f, MathCalc::generateRandomFloat(-9.75f, 9.75f)), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 3.0f, 0.25f)),
	m_wall_1(m_rawEntity, Vector3f(10.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 10.0f)),
	m_wall_2(m_rawEntity, Vector3f(-10.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 10.0f)),
	m_wall_3(m_rawEntity, Vector3f(0.0f, 0.0f, 10.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(10.0f, 1.0f, 0.25f)),
	m_wall_4(m_rawEntity, Vector3f(0.0f, 0.0f, -10.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(10.0f, 1.0f, 0.25f)),
	m_entityList{ &m_terrain, &m_player, &m_target, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4 },
	m_updatableList{ &m_camera, &m_frustum, &m_player },
	m_collideableList{  &m_target, &m_player, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4 },
	m_rayCaster(m_camera, m_frustum)
{
	m_player.addRayCaster(&m_rayCaster);
}

void Game::update(float deltaTime)
{
	if (m_timer.isDeltaTimeFromLastRestartClock(10.0f))
		this->onRestart(m_player, m_target);

	float angleInDegrees = m_pythonExtension.callPythonAI(m_player, m_target, false);
	m_player.getEventHandler().addEventToList(Event(Event::MOVE_TO_ANGLE, false, angleInDegrees));
	//uncomment previous line for AI to work

	//m_player.getEventHandler().addEventToList(Event(Event::MOVE_TO, false, m_target.getTranslationVector().x, m_target.getTranslationVector().y, m_target.getTranslationVector().z));


	for (IUpdatable* updatable : m_updatableList)
		updatable->update(deltaTime);

	CollisionManager::checkCollisions(m_collideableList);
}


void Game::onSuccess(Player& player, Target& target)
{
	m_pythonExtension.callPythonAI(m_player, m_target, true);
	this->onRestart(player, target);
}

void Game::onRestart(Player& player, Target& target)
{
	player.restartPosition();
	target.restartPosition();
	m_timer.setLastRestartTimeToCurrentTimeClock();
}