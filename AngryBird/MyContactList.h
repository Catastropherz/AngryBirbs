#pragma once
#include "box2d/b2_world_callbacks.h"
#include "box2d/box2d.h"

class MyContactList : public b2ContactListener
{
private:
    b2World* Box2dWorld = nullptr;
	class Game* gameClass = nullptr;

public:
    MyContactList(b2World* _world, Game* _game);

    void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;
};

