#include "Collider.h"

namespace Engine
{
	SphereCollider::SphereCollider(GameObject* owner, float radius)
	{
		_owner = owner;
		_radius = radius;
	}

	void SphereCollider::checkCollision(SphereCollider otherCollider)
	{
		glm::vec3 distanceVector = _owner->transform.position - otherCollider.getOwner()->transform.position;
		float distance = glm::length(distanceVector);

		if (distance <= _radius + otherCollider.getRadius())
		{
			otherCollider.triggerCollision(*this);
			triggerCollision(otherCollider);
		}
	}

	float SphereCollider::getRadius() const
	{
		return _radius;
	}

	GameObject* SphereCollider::getOwner() const
	{
		return _owner;
	}

	void SphereCollider::triggerCollision(SphereCollider otherCollider)
	{
		if (_isTrigger)
		{
			_owner->onTrigger(otherCollider);
			return;
		}
		_owner->onCollision(otherCollider);
	}
}
