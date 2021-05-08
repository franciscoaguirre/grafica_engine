#include "BaseGameObject.h"

namespace Engine
{
	BaseGameObject::BaseGameObject() : _scene(nullptr)
	{}

	BaseGameObject::~BaseGameObject()
	{
		for (BaseGameObject* child : _children)
		{
			delete child;
		}

		for (Behaviour* behaviour : _behaviours)
		{
			delete behaviour;
		}
	}

	void BaseGameObject::addBehaviour(Behaviour* behaviour)
	{
		behaviour->setGameObject(this);
		_behaviours.push_back(behaviour);
	}

	void BaseGameObject::addChild(BaseGameObject* child)
	{
		child->setScene(_scene);
		_children.push_back(child);
	}

	void BaseGameObject::update()
	{
		for (Behaviour* behaviour : _behaviours)
		{
			behaviour->update();
		}

		for (BaseGameObject* child : _children)
		{
			child->update();
		}
	}

	void BaseGameObject::setScene(Scene* scene)
	{
		_scene = scene;
	}

	Scene* BaseGameObject::getScene() const
	{
		return _scene;
	}

	void BaseGameObject::draw() const
	{}

	void BaseGameObject::addTag(std::string tag)
	{
		_tags.push_back(tag);
	}

	bool BaseGameObject::hasTag(std::string tagToFind) const
	{
		for (std::string tag : _tags)
		{
			if (tag == tagToFind)
			{
				return true;
			}
		}
		return false;
	}
}
