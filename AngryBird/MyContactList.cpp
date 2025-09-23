#include "MyContactList.h"
#include "Game.h"

MyContactList::MyContactList(b2World* _world, Game* _game)
{
	Box2dWorld = _world;
	gameClass = _game;
}

void MyContactList::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
	b2WorldManifold worldManifold;
	_contact->GetWorldManifold(&worldManifold);

	b2PointState prevState[2], currentState[2];

	b2GetPointStates(prevState, currentState, _oldManifold, _contact->GetManifold());

	if (currentState[0] == b2_addState)
	{
		b2Body* bodyA = _contact->GetFixtureA()->GetBody();
		b2Body* bodyB = _contact->GetFixtureB()->GetBody();
		b2Vec2 point = worldManifold.points[0];
		b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
		b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);

		float approachSpeed = b2Dot(vB - vA, -worldManifold.normal);
	
		for (auto iter : gameClass->GetPhysicsObjects())
		{
			if (iter->GetBody() == bodyA || iter->GetBody() == bodyB)
			{
				iter->ReceiveImpact(approachSpeed);
			}
		}
	}
}
