#include "Mover.h"

#include "../Core/Time.h"
#include "../Core/GameObject.h"

Mover::Mover()
{}

void Mover::update()
{
	Engine::Transform& transform = gameObject->transform;
	transform.position += transform.getForward() * _speed * Engine::Time::getDeltaTime();
	if (transform.position.x >= 10.f)
	{
		transform.position.x = -10.f;
	}
}