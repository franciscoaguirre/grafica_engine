#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject(Model* model, MaterialObject material) : _model(model), _material(material)
	{}

	GameObject::GameObject(GameObject* otherGameObject)
	{
		Model* modelCopy = new Model(otherGameObject->getModel());
		_model = modelCopy;
		_material = MaterialObject(otherGameObject->getMaterial().getShader());
	}

	void GameObject::draw() const
	{
		if (_model == nullptr)
		{
			return;
		}
		Shader* shader = _material.getShader();
		shader->use();
		transform.apply(*shader);
		std::vector<Light*> lights = _scene->getLights();

		for (Light* light : lights)
		{
			light->apply(*shader);
		}

		Camera* camera = _scene->getActiveCamera();
		camera->apply(*shader);

		_model->draw(*shader);

		for (BaseGameObject* child : _children)
		{
			if (child->isDrawable())
			{
				GameObject* drawableChild = dynamic_cast<GameObject*>(child);
				drawableChild->draw();
			}
		}
	}

	GameObject::~GameObject()
	{
		BaseGameObject::~BaseGameObject();

		delete _model;
	}

	bool GameObject::isDrawable() const
	{
		return true;
	}

	Model* GameObject::getModel() const
	{
		return _model;
	}
	
	MaterialObject GameObject::getMaterial() const
	{
		return _material;
	}
}
