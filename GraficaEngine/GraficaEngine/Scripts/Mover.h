#pragma once

#include "../Core/Behaviour.h"

class Mover : public Engine::Behaviour
{
private:
	float _speed = 10.f;
public:
	Mover();
	void update();
};
