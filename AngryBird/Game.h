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
	int windowWidth = 1280;
	int windowHeight = 720;

	sf::Sprite backgroundSprite;
	sf::Sprite chickSprite;
	sf::Sprite groundSprite;
	sf::Sprite pipeSprite;
	sf::Sprite duckSprite;
	sf::Sprite slingshotSprite;
	sf::Sprite boxSprite;
	sf::Sprite fenceSprite;

	b2World* Box2dWorld;
	class MyContactList* Box2dContactListener = nullptr;
	b2MouseJoint* MouseJoint = nullptr;
	std::vector<PhysicsObject*> PhysicsObjects;
	std::vector<sf::Texture*> Textures;
	PhysicsObject* groundObject = nullptr;
	PhysicsObject* slingshotObject = nullptr;
	PhysicsObject* projectileObject = nullptr;

	b2DistanceJoint* slingshotJoint = nullptr;

	int score = 0;
	int birdsLeft = 5;
	int enemiesLeft = 3;
	int level = 1;

public:
	Game(int _width = 1280, int _height = 720);
	~Game();

	void PlayGame();

	//Runs every frame
	void Process();

	PhysicsObject* CreatePipe(b2Vec2 _position, float _rotation);
	PhysicsObject* CreateSlingshot(b2Vec2 _position, float _rotation);
	PhysicsObject* CreateBox(b2Vec2 _position, float _rotation);
	PhysicsObject* CreateEnemy(b2Vec2 _position, float _rotation);
	void CreateLevel(int _level);

	std::vector<PhysicsObject*> GetPhysicsObjects();
};

