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

public:
	PhysicsObject(b2Shape::Type _shapeType, sf::Sprite* _sprite, b2Vec2 _size, b2Vec2 _position,
		float _rotationDegrees, b2BodyType _bodyType, b2World* _world);

	~PhysicsObject();

	b2Body* GetBody();

	void Draw(sf::RenderWindow& _window);
};

