#include "PhysicsObject.h"
#include "PhysicsLibrary.h"
#include "Game.h"
#include <iostream>

PhysicsObject::PhysicsObject(b2Shape::Type _shapeType, sf::Sprite* _sprite, b2Vec2 _size, b2Vec2 _position,
	float _rotationDegrees, b2BodyType _bodyType, b2World* _world, Game* _gameClass)
{
	Size = _size;
	Sprite = _sprite;
	Box2dWorld = _world;
	gameClass = _gameClass;

	b2BodyDef bodyDef;
	bodyDef.position = _position;
	bodyDef.type = _bodyType;
	bodyDef.angle = DegreesToRadians(_rotationDegrees);
	Body = Box2dWorld->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	b2CircleShape circleShape;
		
	switch (_shapeType)
	{
	case b2Shape::e_polygon:
		polyShape.SetAsBox(Size.x * 0.5f, Size.y * 0.5f);
		fixtureDef.shape = &polyShape;
		break;
	case b2Shape::e_circle:
		circleShape.m_radius = Size.x * 0.5f;
		fixtureDef.shape = &circleShape;
		break;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.3f;
	Body->CreateFixture(&fixtureDef);
}

PhysicsObject::~PhysicsObject()
{
	Box2dWorld->DestroyBody(Body);
}

b2Body* PhysicsObject::GetBody()
{
	return Body;
}

void PhysicsObject::Draw(sf::RenderWindow& _window)
{
	sf::Vector2f SpriteScale(
		Size.x / Sprite->getTexture()->getSize().x * g_sizeScale,
		Size.y / Sprite->getTexture()->getSize().y * g_sizeScale
	);

	Sprite->setScale(SpriteScale);

	Sprite->setOrigin(
		Sprite->getTexture()->getSize().x * 0.5f,
		Sprite->getTexture()->getSize().y * 0.5f
	);

	Sprite->setPosition(
		Body->GetPosition().x * g_sizeScale,
		Body->GetPosition().y * g_sizeScale
	);

	Sprite->setRotation(RadiansToDegrees(Body->GetAngle()));

	_window.draw(*Sprite);
}

void PhysicsObject::ReceiveImpact(float _approachSpeed)
{
	if (invul) return;
	if (_approachSpeed < 1.0f) return;
	
	// TODO : Give everything 1s invulnerability after spawning

	health -= pow(_approachSpeed, 2);
	std::cout << "Health: " << health << std::endl;
	if (health <= 0.0f)
	{
		markedForDestroy = true;

		if (isEnemy)
		{
			//gameClass->EnemyDied();
		}
	}
}

void PhysicsObject::SetHealth(float _health, bool _invul)
{
	health = _health;
	invul = _invul;
}

void PhysicsObject::setIsEnemy(bool _isEnemy)
{
	isEnemy = _isEnemy;
}
