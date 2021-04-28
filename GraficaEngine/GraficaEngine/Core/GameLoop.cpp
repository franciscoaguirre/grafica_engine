#include "GameLoop.h"

namespace Engine
{
	GameLoop::GameLoop()
	{}

	void GameLoop::start()
	{
		Input& input = Input::getInstance();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		while (true)
		{
			Time::updateTime();
			input.update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (!_activeScene)
			{
				continue;
			}

			Camera* camera = _activeScene->getActiveCamera();

			if (input.getKey(KEY_ESCAPE))
				break;

			_shader->use();
			glm::mat4 projection = camera->getProjectionMatrix();
			glm::mat4 view = camera->getViewMatrix();
			_shader->setMat4("projection", projection);
			_shader->setMat4("view", view);

			_activeScene->update();
			_activeScene->draw();

			_window->swap();
		}

		for (GameObject* gameObject : _gameObjects)
		{
			delete gameObject;
		}

		delete _activeScene;
		delete _shader;
		delete _window;
		MediaLayer::exit();
	}

	void GameLoop::setActiveScene(Scene* scene)
	{
		if (_activeScene)
		{
			delete _activeScene;
		}

		_activeScene = scene;
	}

	void GameLoop::addWindow(Window* window)
	{
		_window = window;
	}

	void GameLoop::addShader(Shader *shader)
	{
		_shader = shader;
	}
}
