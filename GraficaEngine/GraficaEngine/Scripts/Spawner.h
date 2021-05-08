#pragma once

#include <vector>

#include "../Core/Behaviour.h"
#include "../Core/GameObject.h"
#include "../Utils/CircularBuffer.h"

constexpr float FIRST_ROW = -18.f;
constexpr float SPACE_BETWEEN_ROWS = 3.f;
constexpr float RADIUS_TO_PLAYER = 15.f;

class Spawner : public Engine::Behaviour
{
private:
	std::vector<Engine::GameObject*> _hazards;
	std::vector<Engine::GameObject*> _environments;
	CircularBuffer<Engine::GameObject*> *_rows;
	int _currentRow;
	Engine::Scene* _scene = nullptr;
	Engine::BaseGameObject* _player = nullptr;
	float _getZCoordinateRow() const;
	bool _nearPlayer() const;
public:
	Spawner(std::vector<Engine::GameObject*> hazards, std::vector<Engine::GameObject*> environments);
	~Spawner();
	void update();
};