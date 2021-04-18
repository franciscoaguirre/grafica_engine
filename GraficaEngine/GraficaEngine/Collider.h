#pragma once

#include <glm/vec3.hpp>

#include "Core/GameObject.h"

// TODO: This should not always be a sphere
class SphereCollider
{
private:
	float _radius;
	GameObject _owner;
public:
	void checkCollision(SphereCollider otherCollider);
	GameObject getOwner() const;
	float getRadius() const;
};
