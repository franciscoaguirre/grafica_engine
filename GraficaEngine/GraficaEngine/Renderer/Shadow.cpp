#include "Shadow.h"

#include <GL/glew.h>
#include <SDL/SDL_opengl.h>

#include "Shader.h"

#include <iostream>

namespace Engine
{
	Shadow::Shadow()
	{
		_shader = new Shader("Assets/Shaders/shadow.vs", "Assets/Shaders/shadow.fs");
		glGenFramebuffers(1, &_depthMapFBO);
		glGenTextures(1, &_depthMap);

		glBindTexture(GL_TEXTURE_2D, _depthMap);

		// Configure depthMap texture
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT,
			GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Configure frame buffer map
		glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Shadow::startGeneration() const
	{
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);

		_shader->use();
	}

	void Shadow::finishGeneration() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		constexpr int WINDOW_WIDTH = 800;
		constexpr int WINDOW_HEIGTH = 600;

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	Shader *Shadow::getShader()
	{
		return _shader;
	}

	void Shadow::use(Shader &shader) const
	{
		glActiveTexture(GL_TEXTURE5);
		shader.setInt("shadowMap", 5);
		glBindTexture(GL_TEXTURE_2D, _depthMap);
		glActiveTexture(GL_TEXTURE0);
	}
}
