#include "InteractableEntity.h"

#include <iostream>

InteractableEntity::InteractableEntity(RawEntity& rawEntity, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, worldTranslation, worldRotation, worldScale)
{
}
