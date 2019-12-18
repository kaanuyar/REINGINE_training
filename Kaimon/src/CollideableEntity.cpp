#include "CollideableEntity.h"

CollideableEntity::CollideableEntity(RawEntity& rawEntity, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: Entity(rawEntity, worldTranslation, worldRotation, worldScale)
{
}


