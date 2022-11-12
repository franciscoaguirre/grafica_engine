#include "GameLoop.h"

#include "Light.h"
#include "SceneManager.h"
#include "Settings.h"
#include <stdlib.h>
#include <time.h>

namespace Engine
{
	GameLoop::GameLoop() :
		_window(nullptr),
		_gamePaused(false),
		_renderer(RenderPipeline())
	{
	}

	void GameLoop::_handleDayTime() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_O))
		{
			switch (settings.getDayTime())
			{
			case DayTime::MORNING:
				settings.setDayTime(DayTime::MIDDAY);
				break;
			case DayTime::MIDDAY:
				settings.setDayTime(DayTime::AFTERNOON);
				break;
			case DayTime::AFTERNOON:
				settings.setDayTime(DayTime::NIGHT);
				break;
			case DayTime::NIGHT:
				settings.setDayTime(DayTime::MORNING);
				break;
			}
		}
	}

	void GameLoop::_handleGameSpeed() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_1))
		{
			settings.setGameSpeed(GameSpeed::SLOW);
		}
		else if (input.getKeyDown(KEY_2))
		{
			settings.setGameSpeed(GameSpeed::NORMAL);
		}
		else if (input.getKeyDown(KEY_3))
		{
			settings.setGameSpeed(GameSpeed::FAST);
		}
	}

	void GameLoop::_handleTexturesToggle() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_T))
		{
			bool showingTextures = settings.getShowTextures();
			settings.setShowTextures(!showingTextures);
		}
	}

	void GameLoop::_handleShowCollidersToggle() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_C))
		{
			bool showingColliders = settings.getShowColliders();
			settings.setShowColliders(!showingColliders);
		}
	}

	void GameLoop::_handleInterpolationToggle() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_U))
		{
			bool useInterpolation = settings.getUseInterpolation();
			settings.setUseInterpolation(!useInterpolation);
		}
	}

	void GameLoop::_handleWireframeToggle() const
	{
		Input &input = Input::getInstance();
		Settings &settings = Settings::getInstance();

		if (input.getKeyDown(KEY_Y))
		{
			bool wireframeOn = settings.getIsWireframe();
			settings.setIsWireframe(!wireframeOn);
		}
	}

	void GameLoop::start()
	{
		srand((unsigned)time(0));

		Input &input = Input::getInstance();
		SceneManager &sceneManager = SceneManager::getInstance();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_CULL_FACE);

		Scene *activeScene = sceneManager.getActiveScene();
		activeScene->start();

		while (true)
		{
			Time::updateTime();
			input.update();
			
			if (input.getKeyDown(KEY_Q))
				break;

			if (input.getKeyDown(PAUSE_KEY))
			{
				_gamePaused = !_gamePaused;
			}

			if (_gamePaused || !activeScene)
			{
				continue;
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glPolygonMode(GL_FRONT_AND_BACK, Settings::getInstance().getIsWireframe() ? GL_LINE : GL_FILL);

			_handleGameSpeed();
			_handleTexturesToggle();
			_handleShowCollidersToggle();
			_handleWireframeToggle();
			_handleInterpolationToggle();
			_handleDayTime();

			if (sceneManager.getShouldRestart())
			{
				sceneManager.loadScene("main");
				sceneManager.setShouldRestart(false);
				activeScene = sceneManager.getActiveScene();
			}

			activeScene->physicsUpdate();
			activeScene->update();
			activeScene->flushQueuedGameObjects();

			_renderer.draw(activeScene);

			_window->swap();
		}

		for (GameObject *gameObject : _gameObjects)
		{
			delete gameObject;
		}

		// delete sceneManager;
		delete _window;
		FontManager *fm = FontManager::getInstance();
		delete fm;
		MediaLayer::exit();
	}

	void GameLoop::addWindow(Window *window)
	{
		_window = window;
		// After creating the window we can setup the renderer since gl has loaded
		_renderer.setup();
	}
}
