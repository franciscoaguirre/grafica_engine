#include "Spawner.h"

#include <stdlib.h>
#include <time.h>

#include "../Core/Scene.h"
#include "Mover.h"

Spawner::Spawner(std::vector<Engine::GameObject*> hazards, std::vector<Engine::GameObject*> environments) :
	_hazards(hazards), _environments(environments), _rows(new CircularBuffer<Engine::GameObject*>(10)), _currentRow(0)
{}

Spawner::~Spawner()
{
	delete _rows;
}

float Spawner::_getZCoordinateRow() const
{
	return FIRST_ROW - (_currentRow * SPACE_BETWEEN_ROWS);
}

bool Spawner::_nearPlayer() const
{
	float zCoordinateRow = _getZCoordinateRow();
	return (
		glm::abs(_player->transform.position.z - zCoordinateRow) <= RADIUS_TO_PLAYER
	);
}

void Spawner::update()
{
	_scene = gameObject->getScene();
	_player = _scene->getGameObjectWithTag("player");
	
	if (_nearPlayer())
	{
		srand(time(nullptr));
		int randomEnvironment = rand() % _environments.size();
		
		Engine::GameObject* referenceEnvironment = _environments[randomEnvironment];
		Engine::GameObject* environmentToSpawn = new Engine::GameObject(referenceEnvironment);
		environmentToSpawn->transform.position = glm::vec3(0.f, 0.f, _getZCoordinateRow());
		environmentToSpawn->transform.scale = glm::vec3(.5f);
		_scene->addGameObject(environmentToSpawn);
		
		Engine::GameObject* referenceHazard = _hazards[randomEnvironment];
		Engine::GameObject* hazardToSpawn = new Engine::GameObject(referenceHazard);
		
		float randomHazardSpawnPointX = -10.f - (rand() % 10);
		
		hazardToSpawn->transform.position = glm::vec3(randomHazardSpawnPointX, 0.f, _getZCoordinateRow());
		hazardToSpawn->addBehaviour(new Mover());
		environmentToSpawn->addChild(hazardToSpawn);

		_rows->put(environmentToSpawn);
		if (_rows->full())
		{
			_scene->deleteGameObject(_rows->get());
		}
		_currentRow++;
	}
}