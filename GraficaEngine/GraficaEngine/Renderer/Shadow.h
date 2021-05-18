#pragma once

constexpr auto SHADOW_WIDTH = 1042, SHADOW_HEIGHT = 1024;

namespace Engine
{
	class Shader;

	class Shadow
	{
	private:
		unsigned int _depthMap;
		unsigned int _depthMapFBO;
		Shader* _shader;
		Shadow();

	public:
		static Shadow& getInstance()
		{
			static Shadow _instance;
			return _instance;
		}
		void startGeneration() const;
		void finishGeneration() const;
		Shader* getShader();
		void use(Shader& shader) const;
	};
}
