#pragma once

#include "../Core/GameObject.h"

namespace Engine {
	class SphereCollider
	{
	private:
		GameObject* _owner;
		float _radius;
		bool _isTrigger;
	public:
		SphereCollider(GameObject* owner, float radius);
		GameObject* getOwner() const;
		float getRadius() const;
		void checkCollision(SphereCollider otherCollider);
		void triggerCollision(SphereCollider otherCollider);
	};
}
