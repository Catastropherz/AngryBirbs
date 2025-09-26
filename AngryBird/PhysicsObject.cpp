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

	spawnPosition = _position;

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
	fixtureDef.filter.categoryBits = CATEGORY_DEFAULT;
	//fixtureDef.filter.maskBits = CATEGORY_DEFAULT | CATEGORY_PHYSICSOBJECT;
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
	if (gracePeriod > 0.0f) return;

	health -= pow(_approachSpeed, 2);
	if (health <= 0.0f)
	{
		markedForDestroy = true;

		if (isEnemy)
		{
			//gameClass->EnemyDied();
		}
	}
}

void PhysicsObject::SetSprite(sf::Sprite* _sprite)
{
	Sprite = _sprite;
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

PhysicsObject* PhysicsObject::SetFilterGroup(int16 _filterGroup)
{

	//b2Filter FilterData;
	//FilterData.categoryBits = CATEGORY_PLAYER;
	//FilterData.maskBits = CATEGORY_ENEMY | CATEGORY_WALL;

	//if (FilterData.maskBits && CATEGORY_ENEMY)
	//{

	//}

	b2Filter FilterData;
	FilterData.groupIndex = _filterGroup;

	Body->GetFixtureList()->SetFilterData(FilterData);
	
	return this;
}

void PhysicsObject::SetCollisionCategory(const unsigned int _category)
{
	b2Filter FilterData = Body->GetFixtureList()->GetFilterData();
	FilterData.categoryBits = _category;

	Body->GetFixtureList()->SetFilterData(FilterData);
}

void PhysicsObject::AddCollisionMask(const unsigned int _mask)
{
	b2Filter FilterData = Body->GetFixtureList()->GetFilterData();

	if (!CustomMaskBits)
	{
		FilterData.maskBits = 0;
		CustomMaskBits = true;
	}

	FilterData.maskBits = FilterData.maskBits|_mask;

	Body->GetFixtureList()->SetFilterData(FilterData);

}

void PhysicsObject::RemoveCollisionMask(unsigned int _mask)
{
	b2Filter FilterData = Body->GetFixtureList()->GetFilterData();
	
	FilterData.maskBits = FilterData.maskBits & (~_mask);
	Body->GetFixtureList()->SetFilterData(FilterData);
}

void PhysicsObject::StarRespawnTimer()
{
	isRespawn = true;
	respawnCountdown = respawnTimer;
}

bool PhysicsObject::Update(float _deltaTime)
{
	gracePeriod -= _deltaTime;
	if (!isRespawn) return false;
	respawnCountdown -= _deltaTime;

	bool almostStill = (Body->GetLinearVelocity().x < 0.1f && Body->GetLinearVelocity().x > -0.1f) &&
		(Body->GetLinearVelocity().y < 0.1f && Body->GetLinearVelocity().y > -0.1f) &&
		(Body->GetAngularVelocity() < 0.1f && Body->GetAngularVelocity() > -0.1f);

	if (respawnCountdown <= 0.0f || almostStill)
	{
		Body->SetTransform(spawnPosition, 0.0f);
		Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		Body->SetAngularVelocity(0.0f);
		isRespawn = false;
		return true;
	}

	return false;
}
