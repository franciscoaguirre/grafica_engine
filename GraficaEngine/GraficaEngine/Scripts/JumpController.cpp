#include "JumpController.h"

#include "../Core/Input.h"
#include "../Core/Time.h"
#include "../Core/GameObject.h"
#include "../Physics/Collider.h"

#include "../Utils/DebugLog.h"

#include <stdio.h>

JumpController::JumpController() : _gravity(-9.8f),
								   _velocity(0.f),
								   _mass(1.f),
								   _jumpStrength(1.f),
								   _grounded(false)
{
}

void JumpController::update()
{
	Engine::Transform &transform = gameObject->transform;

	if (_shouldJump())
	{
		glm::vec3 jumpDirection = glm::normalize(transform.getForward() + transform.getUp());
		_velocity = _jumpStrength * jumpDirection;
	}

	if (_grounded)
	{
		_velocity = glm::vec3(0.f);
	}
	else
	{
		_updateVelocity();
	}

	//std::cout << _grounded << std::endl;

	_updatePosition();
}

bool JumpController::_shouldJump()
{
	_grounded = false;
	for (Engine::Collider *collision : gameObject->getCollider()->getCollisions())
	{
		Engine::GameObject *other = collision->getGameObject();

		if (other->hasTag("ground"))
		{
			_grounded = true;
			break;
		}
	}

	Engine::Input &input = Engine::Input::getInstance();

	return _grounded && input.getKeyDown(Engine::KEY_SPACE);
}

void JumpController::_updatePosition()
{
	Engine::Transform &transform = gameObject->transform;
	transform.position += _velocity * Engine::Time::getDeltaTime();
}

void JumpController::_updateVelocity()
{
	_velocity = _gravity * Engine::Time::getDeltaTime() * glm::vec3(0.f, 1.f, 0.f) + _velocity;
}
