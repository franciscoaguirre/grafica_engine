#include "BaseGameObject.h"

#include "Scene.h"

#include <algorithm>

namespace Engine
{
	BaseGameObject::BaseGameObject() : _scene(nullptr), _parent(nullptr)
	{
	}

	BaseGameObject::BaseGameObject(const BaseGameObject *otherBaseGameObject)
	{
		setScene(otherBaseGameObject->getScene());
		setParent(otherBaseGameObject->getParent());
		transform = otherBaseGameObject->transform;
		
		for (Behaviour *otherBehaviour : otherBaseGameObject->_behaviours)
		{
			addBehaviour(otherBehaviour->clone());
		}

		for (std::string tag : otherBaseGameObject->_tags)
		{
			addTag(tag);
		}

		for (BaseGameObject *child : otherBaseGameObject->_children)
		{
			addChild(child->clone());
		}
	}

	BaseGameObject *BaseGameObject::clone() const
	{
		return new BaseGameObject(this);
	}

	BaseGameObject::~BaseGameObject()
	{
		for (BaseGameObject *child : _children)
		{
			delete child;
		}

		for (Behaviour *behaviour : _behaviours)
		{
			delete behaviour;
		}
	}

	void BaseGameObject::addBehaviour(Behaviour *behaviour)
	{
		behaviour->setGameObject(this);
		_behaviours.push_back(behaviour);
	}

	std::vector<Behaviour *> BaseGameObject::getBehaviours() const
	{
		return _behaviours;
	}

	void BaseGameObject::addChild(BaseGameObject *child)
	{
		child->setScene(_scene);
		if (child->getCollider() != nullptr)
		{
			_scene->addCollider(child->getCollider());
		}
		child->setParent(this);
		_children.push_back(child);
		child->start();
	}

	BaseGameObject *BaseGameObject::getParent() const
	{
		return _parent;
	}

	void BaseGameObject::setParent(BaseGameObject *parent)
	{
		_parent = parent;
	}

	bool BaseGameObject::hasParent() const
	{
		return _parent != nullptr;
	}

	void BaseGameObject::deleteChild(BaseGameObject *child)
	{
		_children.erase(
			std::remove(
				_children.begin(),
				_children.end(),
				child),
			_children.end());

		delete child;
	}

	void BaseGameObject::update()
	{
		for (Behaviour *behaviour : _behaviours)
		{
			behaviour->update();
		}

		for (BaseGameObject *child : _children)
		{
			child->update();
		}
	}

	void BaseGameObject::start()
	{
		for (Behaviour* behaviour : _behaviours)
		{
			behaviour->start();
		}

		for (BaseGameObject* child : _children)
		{
			child->start();
		}
	}

	void BaseGameObject::setScene(Scene *scene)
	{
		_scene = scene;
	}

	Collider *BaseGameObject::getCollider() const
	{
		return nullptr;
	}

	Scene *BaseGameObject::getScene() const
	{
		return _scene;
	}

	void BaseGameObject::draw() const
	{
		for (BaseGameObject *child : _children)
		{
			child->draw();
		}
	}

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

	BaseGameObject* BaseGameObject::getChildWithTag(std::string tag) const
	{
		for (BaseGameObject* child : _children)
		{
			if (child->hasTag(tag))
			{
				return child;
			}
		}
		return nullptr;
	}
}
