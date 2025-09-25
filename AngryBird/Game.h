#pragma once
#include "SFML/Graphics.hpp"
#include "box2d\box2D.h"
#include <vector>
#include "PhysicsObject.h"
#include <iostream>
#include "PhysicsLibrary.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Sprite chickSprite;
	sf::Sprite groundSprite;
	sf::Sprite pipeSprite;
	sf::Sprite duckSprite;
	sf::Sprite slingshotSprite;

	b2World* Box2dWorld;
	class MyContactList* Box2dContactListener = nullptr;
	b2MouseJoint* MouseJoint = nullptr;
	std::vector<PhysicsObject*> PhysicsObjects;
	std::vector<sf::Texture*> Textures;
	PhysicsObject* groundObject = nullptr;
	PhysicsObject* slingshotObject = nullptr;
	PhysicsObject* projectileObject = nullptr;

	b2DistanceJoint* slingshotJoint = nullptr;

public:
	Game();
	~Game();

	void PlayGame();

	//Runs every frame
	void Process();

	PhysicsObject* CreatePipe(b2Vec2 _position, float _rotation);
	PhysicsObject* CreateSlingshot(b2Vec2 _position, float _rotation);

	std::vector<PhysicsObject*> GetPhysicsObjects();
};

