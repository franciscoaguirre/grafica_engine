#include "GameObject.h"

#include "../Renderer/Shadow.h"

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:
			error = "INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			error = "INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			error = "INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			error = "STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			error = "STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			error = "OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			error = "INVALID_FRAMEBUFFER_OPERATION";
			break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace Engine
{
	GameObject::GameObject(Model *model, MaterialObject material) : _model(model), _material(material), _collider(nullptr)
	{
	}

	void GameObject::setCollider(Collider *collider)
	{
		collider->setGameObject(this);
		_collider = collider;
	}

	Collider *GameObject::getCollider() const
	{
		return _collider;
	}

	GameObject::GameObject(const GameObject *otherGameObject):
		BaseGameObject::BaseGameObject(otherGameObject)
	{
		Model *modelCopy = new Model(otherGameObject->getModel());
		_model = modelCopy;
		_material = MaterialObject(otherGameObject->_material.getShader());
		Collider* otherCollider = otherGameObject->getCollider();
		if (otherCollider != nullptr)
		{
			setCollider(new Collider(otherGameObject->getCollider()));
		}
	}

	GameObject *GameObject::clone() const
	{
		return new GameObject(this);
	}

	void GameObject::draw() const
	{
		if (_model == nullptr)
		{
			return;
		}
		Shader *shader = _material.getShader();

		shader->use();
		_material.applyTextureOffset();
		transform.apply(*shader);
		std::vector<Light *> lights = _scene->getLights();

		std::cout << "HOLA" << std::endl;
		glCheckError();

		for (Light *light : lights)
		{
			light->apply(*shader);
		}

		Camera *camera = _scene->getActiveCamera();
		camera->apply(*shader);

		Shadow::getInstance().use(*shader);
		_model->draw(*shader);

		BaseGameObject::draw();
	}

	void GameObject::shadowDraw(Shader* shader) const
	{
		if (_model == nullptr)
		{
			return;
		}

		transform.apply(*shader);

		std::vector<Light*> lights = _scene->getLights();

		for (Light* light : lights)
		{
			light->shadowApply(*shader);
		}

		_model->draw(*shader);

		BaseGameObject::draw();
	}

	GameObject::~GameObject()
	{

		BaseGameObject::~BaseGameObject();

		if (_collider != nullptr)
		{
			_scene->removeCollider(_collider);
			delete _collider;
		}
		
		delete _model;
	}

	Model *GameObject::getModel() const
	{
		return _model;
	}

	MaterialObject &GameObject::getMaterial()
	{
		return _material;
	}
}
