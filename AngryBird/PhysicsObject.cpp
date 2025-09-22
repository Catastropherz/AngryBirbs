#include "PhysicsObject.h"
#include "PhysicsLibrary.h"

PhysicsObject::PhysicsObject(b2Shape::Type _shapeType, sf::Sprite* _sprite, b2Vec2 _size, b2Vec2 _position,
	float _rotationDegrees, b2BodyType _bodyType, b2World* _world)
{
	Size = _size;
	Sprite = _sprite;
	Box2dWorld = _world;

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