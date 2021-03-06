#pragma once

#include "AABB.h"
#include "CollideableEntity.h"
#include "Player.h"
#include "CollisionManager.h"

class Target : public CollideableEntity
{
public:
	Target(RawEntity& rawEntity, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	virtual ICollider* getCollider();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

	void restartPosition(Vector3f terrainMinVec, Vector3f terrainMaxVec);

	// for testing
	AABB& getAABB();

private:
	AABB m_aabb;
	Vector3f m_edgeLengthVec;
};