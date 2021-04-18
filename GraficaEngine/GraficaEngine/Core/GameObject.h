#pragma once

#include <vector>

#include "../Renderer/Model.h"
#include "../Renderer/Material.h"
#include "Transform.h"
#include "Behaviour.h"
#include "../Physics/Collider.h"

namespace Engine
{
	class GameObject
	{
	private:
		Model _model;
		MaterialObject _material;
		std::vector<Behaviour*> _behaviours;
		SphereCollider _collider;
		// GameObject[] _children;
	public:
		GameObject(Model model, MaterialObject material);
		~GameObject();
		Transform transform;
		void update();
		void draw() const;
		void addBehaviour(Behaviour*);
		SphereCollider* getCollider();
		void onCollision(SphereCollider otherCollider);
		void onTrigger(SphereCollider otherCollider);
	};
}