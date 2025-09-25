#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class PhysicsObject
{
private:
	sf::Sprite* Sprite = nullptr;
	b2Body* Body = nullptr;
	b2World* Box2dWorld = nullptr;

	//The size of the object in meters
	b2Vec2 Size;

	float health = 100.0f;
	bool invul = false;

	bool markedForDestroy = false;
	bool isEnemy = false;

	class Game* gameClass = nullptr;

public:
	PhysicsObject(b2Shape::Type _shapeType, sf::Sprite* _sprite, b2Vec2 _size, b2Vec2 _position,
		float _rotationDegrees, b2BodyType _bodyType, b2World* _world, Game* _gameClass);

	~PhysicsObject();

	b2Body* GetBody();

	void Draw(sf::RenderWindow& _window);

	void ReceiveImpact(float _approachSpeed);

	void SetHealth(float _health, bool _invul = false);
	void setIsEnemy(bool _isEnemy);

	inline bool IsMarkedForDestroy() { return markedForDestroy; }

	PhysicsObject* SetFilterGroup(int16 _filterGroup);

	bool CustomMaskBits = false;

	void SetCollisionCategory(const unsigned int _category);
	void AddCollisionMask(const unsigned int _mask);

	void RemoveCollisionMask(unsigned int _mask);
};

