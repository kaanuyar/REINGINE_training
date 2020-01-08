#pragma once
#include <vector>
#include "Entity.h"
#include "RawEntity.h"
#include "Vector3f.h"
#include "OBJLoader.h"
#include "Terrain.h"
#include "Camera.h"
#include "InteractableEntity.h"
#include "ViewFrustum.h"
#include "IUpdatable.h"
#include "RayCaster.h"
#include "CollideableEntity.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Player.h"
#include "PythonExtension.h"
#include "Target.h"
#include "Timer.h"
#include "MathCalc.h"

class Game
{
public:
	Game();
	void update(float deltaTime);
	
	void onSuccess();
	void onFailure();
	void onRestart();
private:
	ViewFrustum m_frustum;
	Camera m_camera;

	RawEntity m_rawEntity, m_rawEntity2, m_rawTerrain;

	Entity m_terrain;
	Player m_player;
	Obstacle m_wall_1, m_wall_2, m_wall_3, m_wall_4;
	Obstacle m_barrier;
	Target m_target;

	std::vector<Entity*> m_entityList;
	std::vector<IUpdatable*> m_updatableList;
	std::vector<ICollideable*> m_collideableList;

	RayCaster m_rayCaster;
	PythonExtension m_pythonExtension;
	Timer m_timer;
};
