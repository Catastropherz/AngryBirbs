#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "box2d\box2D.h"
#include <vector>
#include "PhysicsObject.h"
#include <iostream>
#include "PhysicsLibrary.h"
#include "box2d\b2_joint.h"

enum BirdType
{
	BIRD_NORMAL = 1,
	BIRD_DROP = 2,
	BIRD_BIG = 3,
};

class Game
{
private:
	sf::RenderWindow* window;
	int windowWidth = 1280;
	int windowHeight = 720;

	sf::Font font;
	sf::Text* controlText = nullptr;
	sf::Text* birdNormalText = nullptr;
	sf::Text* birdDropText = nullptr;
	sf::Text* birdBigText = nullptr;
	sf::Text* descriptionText = nullptr;

	sf::RectangleShape retryButton;
	sf::Text* retryButtonText = nullptr;
	sf::RectangleShape nextButton;
	sf::Text* nextButtonText = nullptr;
	sf::Text* endingText = nullptr;

	sf::Sprite backgroundSprite;
	sf::Sprite pauseSprite;
	sf::Sprite chickSprite;
	sf::Sprite chickSpriteUI;
	sf::Sprite parrotSprite;
	sf::Sprite parrotSpriteUI;
	sf::Sprite owlSprite;
	sf::Sprite owlSpriteUI;
	sf::Sprite groundSprite;
	sf::Sprite pipeSprite;
	sf::Sprite duckSprite;
	sf::Sprite slingshotSprite;
	sf::Sprite boxSprite;
	sf::Sprite fenceSprite;

	sf::SoundBuffer birdShootBuffer;
	sf::Sound* birdShootSound;
	sf::SoundBuffer birdDropBuffer;
	sf::Sound* birdDropSound;
	sf::SoundBuffer birdBigBuffer;
	sf::Sound* birdBigSound;
	sf::SoundBuffer deadBuffer;
	sf::Sound* deadSound;

	sf::Music BGM;

	b2World* Box2dWorld;
	class MyContactList* Box2dContactListener = nullptr;
	b2MouseJoint* MouseJoint = nullptr;
	std::vector<PhysicsObject*> PhysicsObjects;
	std::vector<sf::Texture*> Textures;
	PhysicsObject* groundObject = nullptr;
	PhysicsObject* slingshotObject = nullptr;
	PhysicsObject* projectileObject = nullptr;
	PhysicsObject* backgroundObject = nullptr;

	b2DistanceJoint* slingshotJoint = nullptr;

	bool paused = false;
	bool victory = false;
	bool endGame = false;

	int birdMode = BIRD_NORMAL;
	int score = 0;
	int birdNormalAmmo = 4;
	int birdNormalLeft = birdNormalAmmo;
	int birdDropAmmo = 2;
	int birdDropLeft = birdDropAmmo;
	int birdBigAmmo = 1;
	int birdBigLeft = birdBigAmmo;
	int enemiesLeft = 5;
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
	void SwitchBird();

	std::vector<PhysicsObject*> GetPhysicsObjects();
};

