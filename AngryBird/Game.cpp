#include "Game.h"
#include "MyContactList.h"
#include <string>

Game::Game(int _width, int _height)
{
    //Creates an SFML window at a desired resolution.
	windowWidth = _width;
	windowHeight = _height;
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "SFML and Box2D");
    window->setFramerateLimit(60);

    //Load textures and create sprites.
	sf::Texture* backgroundTexture = new sf::Texture;
	backgroundTexture->loadFromFile("Sprites/background.png");
	backgroundSprite.setTexture(*backgroundTexture);
	Textures.push_back(backgroundTexture); //Store texture so it doesn't go out of scope

    sf::Texture* chickTexture = new sf::Texture;
    chickTexture->loadFromFile("Sprites/chick.png");
    chickSprite.setTexture(*chickTexture);
    chickSpriteUI.setTexture(*chickTexture);
	Textures.push_back(chickTexture); //Store texture so it doesn't go out of scope

    sf::Texture* parrotTexture = new sf::Texture;
    parrotTexture->loadFromFile("Sprites/parrot.png");
    parrotSprite.setTexture(*parrotTexture);
    parrotSpriteUI.setTexture(*parrotTexture);
    Textures.push_back(parrotTexture); //Store texture so it doesn't go out of scope

    sf::Texture* owlTexture = new sf::Texture;
    owlTexture->loadFromFile("Sprites/owl.png");
    owlSprite.setTexture(*owlTexture);
    owlSpriteUI.setTexture(*owlTexture);
    Textures.push_back(owlTexture); //Store texture so it doesn't go out of scope

    sf::Texture* duckTexture = new sf::Texture;
    duckTexture->loadFromFile("Sprites/duck.png");
    duckSprite.setTexture(*duckTexture);
    Textures.push_back(duckTexture); //Store texture so it doesn't go out of scope

    sf::Texture* groundTexture = new sf::Texture;
    groundTexture->loadFromFile("Sprites/ground.png");
    groundSprite.setTexture(*groundTexture);
	Textures.push_back(groundTexture); //Store texture so it doesn't go out of scope

	sf::Texture* boxTexture = new sf::Texture;
	boxTexture->loadFromFile("Sprites/box.png");
	boxSprite.setTexture(*boxTexture);
	Textures.push_back(boxTexture); //Store texture so it doesn't go out of scope

    sf::Texture* pipeTexture = new sf::Texture;
    pipeTexture->loadFromFile("Sprites/pipe.png");
    pipeSprite.setTexture(*pipeTexture);
	Textures.push_back(pipeTexture); //Store texture so it doesn't go out of scope

    sf::Texture* fenceTexture = new sf::Texture;
    fenceTexture->loadFromFile("Sprites/fence.png");
    fenceSprite.setTexture(*fenceTexture);
    Textures.push_back(fenceTexture); //Store texture so it doesn't go out of scope

    sf::Texture* slingshotTexture = new sf::Texture;
    slingshotTexture->loadFromFile("Sprites/SlingshotFinal.png");
    slingshotSprite.setTexture(*slingshotTexture);
    Textures.push_back(slingshotTexture); //Store texture so it doesn't go out of scope

    // Setup font and text
    if (font.loadFromFile("Fonts/MinecraftStandard.otf"))
    {
        controlText = new sf::Text("Spacebar - switch bird type", font, 20);
        controlText->setFillColor(sf::Color::White);
		controlText->setOutlineColor(sf::Color::Black);
		controlText->setOutlineThickness(2.0f);
		controlText->setPosition(200.0f, 30.0f);

		birdNormalText = new sf::Text(std::string(" x " + std::to_string(birdNormalLeft)), font, 20);
		birdNormalText->setFillColor(sf::Color::White);
		birdNormalText->setOutlineColor(sf::Color::Black);
		birdNormalText->setOutlineThickness(2.0f);
		birdNormalText->setPosition(100.0f, 30.0f);

        birdDropText = new sf::Text(std::string(" x " + std::to_string(birdDropLeft)), font, 20);
        birdDropText->setFillColor(sf::Color::White);
        birdDropText->setOutlineColor(sf::Color::Black);
        birdDropText->setOutlineThickness(2.0f);
        birdDropText->setPosition(100.0f, 80.0f);
    
        birdBigText = new sf::Text(std::string(" x " + std::to_string(birdBigLeft)), font, 20);
        birdBigText->setFillColor(sf::Color::White);
        birdBigText->setOutlineColor(sf::Color::Black);
        birdBigText->setOutlineThickness(2.0f);
        birdBigText->setPosition(100.0f, 130.0f);

        descriptionText = new sf::Text("Normal Bird: Just an ordinary bird.", font, 18);
		descriptionText->setFillColor(sf::Color::Yellow);
		descriptionText->setOutlineColor(sf::Color::Black);
		descriptionText->setOutlineThickness(2.0f);
        descriptionText->setPosition(200.0f, 80.0f);
    }
    else
    {
		std::cout << "Failed to load font!" << std::endl;
    }

    // Setup UI
	chickSpriteUI.setScale(0.25f, 0.25f);
	chickSpriteUI.setPosition(50.0f, 20.0f);
	parrotSpriteUI.setScale(0.25f, 0.25f);
	parrotSpriteUI.setPosition(50.0f, 70.0f);
	owlSpriteUI.setScale(0.25f, 0.25f);
	owlSpriteUI.setPosition(50.0f, 120.0f);

    //Create box2d world
    Box2dWorld = new b2World(g_gravity);

    // Create background
    backgroundSprite.setScale(
        windowWidth / backgroundSprite.getTexture()->getSize().x,
        windowHeight / backgroundSprite.getTexture()->getSize().y
    );
    backgroundSprite.setPosition(0.0f, 0.0f);
    backgroundObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &backgroundSprite,          // Sprite
        b2Vec2(25.6f, 14.4f),      // Size (in meters)
        b2Vec2(12.8f, 7.2f),       // Position (in meters)
        0.0f,                       // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                 // Pointer to the box2d world
        this						// Pointer to the game class
    );
    backgroundObject->SetCollisionCategory(CATEGORY_SPRITE);
}

Game::~Game()
{
    // Cleanup
    for (auto obj : PhysicsObjects)
    {
        delete obj;
    }

    for (auto tex : Textures)
    {
        delete tex;
	}

    delete Box2dWorld;
    Box2dWorld = nullptr;
    delete Box2dContactListener;
	Box2dContactListener = nullptr;
}

void Game::PlayGame()
{
	CreateLevel(level);
    //Draw our physics objects.
    for (auto obj : PhysicsObjects)
    {
        obj->Draw(*window);
    }
    //Finally, display the window.
    window->display();
	
    // Press any button to start the game
	std::cin.get();

    //This is the window process section for SFML.
    while (window->isOpen())
    {
        Process();
    }
}

//Runs every frame
void Game::Process()
{
    //Step the world physics forward
    Box2dWorld->Step(g_timeStep, 8, 3);

	// Check win condition
    if (enemiesLeft <= 0)
    {
		// TODO LEVEL COMPLETE and NEXT LEVEL

		level++;
		CreateLevel(level);
    }
    // Check lose condition
    if (birdNormalLeft + birdDropLeft + birdBigLeft <= 0)
    {
		//TODO GAME OVER and RESTART
    }

    for (int i = 0; i < PhysicsObjects.size(); i++)
    {
		// Tick down respawn timers and reset projectile location
        if (PhysicsObjects[i]->Update(g_timeStep) && PhysicsObjects[i] == projectileObject)
        {
            // Setup Slingshot Joint
            b2DistanceJointDef slingshotJointDef;
            slingshotJointDef.bodyA = projectileObject->GetBody();
            slingshotJointDef.bodyB = slingshotObject->GetBody();
            slingshotJointDef.collideConnected = false;
            slingshotJointDef.maxLength = 2.0f;
            slingshotJointDef.minLength = 0.0f;
            slingshotJointDef.stiffness = 100.0f;
            slingshotJointDef.damping = 0.0f;
            slingshotJointDef.length = 1.0f;
            slingshotJointDef.localAnchorB = b2Vec2(0.0f, -0.9f);
            slingshotJointDef.type = e_distanceJoint;
            slingshotJoint = (b2DistanceJoint*)Box2dWorld->CreateJoint(&slingshotJointDef);

            // Reduce bird count
            if (birdNormalLeft + birdDropLeft + birdBigLeft > 0)
            {
                switch (birdMode)
                {
                case BIRD_NORMAL:
                    if (birdNormalLeft > 1) birdNormalLeft--;
                    else if (birdNormalLeft == 1)
                    {
                        birdNormalLeft--;
                        SwitchBird();
                    }
                    else SwitchBird();
                    break;
                case BIRD_DROP:
                    if (birdDropLeft > 1) birdDropLeft--;
                    else if (birdDropLeft == 1)
                    {
                        birdDropLeft--;
                        SwitchBird();
                    }
                    else SwitchBird();
                    break;
                case BIRD_BIG:
                    if (birdBigLeft > 1) birdBigLeft--;
                    else if (birdBigLeft == 1)
                    {
                        birdBigLeft--;
                        SwitchBird();
                    }
                    else SwitchBird();
                    break;
                default:
                    break;
                }

				// Update UI
				birdNormalText->setString(std::string(" x " + std::to_string(birdNormalLeft)));
				birdDropText->setString(std::string(" x " + std::to_string(birdDropLeft)));
				birdBigText->setString(std::string(" x " + std::to_string(birdBigLeft)));
            }
        }

		//Delete physics objects that are marked for destroy
        if (PhysicsObjects[i]->IsMarkedForDestroy())
        {
            if (MouseJoint && MouseJoint->GetBodyB() == PhysicsObjects[i]->GetBody())
            {
                Box2dWorld->DestroyJoint(MouseJoint);
                MouseJoint = nullptr;
			}

            if (PhysicsObjects[i]->GetIsEnemy())
            {
                enemiesLeft--;
            }

            delete PhysicsObjects[i];
			PhysicsObjects.erase(PhysicsObjects.begin() + i);
            // when removing an item from a vector,
            // the next item will shift into the current index, 
            // so we need to decrement i to avoid skipping it
            i--;
        }
    }

    //Clear the previous window. If we don't do this, we will draw on top of previous stuff.
    window->clear();

    // Draw the background
	backgroundObject->Draw(*window);

    //Window events:
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            //Check if a mouse location is inside a body after converting location to meters
            sf::Vector2i MousePos = sf::Mouse::getPosition(*window);
            b2Vec2 MousePoint(MousePos.x / g_sizeScale, MousePos.y / g_sizeScale);
            if(projectileObject)
            {
				// If the projectile is not fired yet, allow clicking on it
                if (projectileObject->GetIsRespawn() == false)
                {
                    b2Transform transform = projectileObject->GetBody()->GetTransform();
                    if (projectileObject->GetBody()->GetFixtureList()->GetShape()->TestPoint(transform, MousePoint))
                    {
                        //Found a body, set up a mouse joint with the body
                        b2MouseJointDef mouseJointDef;
                        mouseJointDef.bodyA = groundObject->GetBody(); // Static body
                        mouseJointDef.bodyB = projectileObject->GetBody(); // The projectile body
                        mouseJointDef.target = MousePoint;
                        mouseJointDef.collideConnected = true;
                        mouseJointDef.maxForce = 1000.0f * projectileObject->GetBody()->GetMass();
                        mouseJointDef.damping = 10.0f;
                        mouseJointDef.stiffness = 500.0f;

                        MouseJoint = (b2MouseJoint*)Box2dWorld->CreateJoint(&mouseJointDef);
                        MouseJoint->SetTarget(MousePoint);
                        break;
                    }
                }
                else // If the porojectile is already fired, clicking will activate its effect
                {
					projectileObject->ActivateBirdEffect(birdMode);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            //Destroy the mouse joint
            if (MouseJoint)
            {
                b2Vec2 mousePos = MouseJoint->GetTarget();
                //destroy mouse joint
                Box2dWorld->DestroyJoint(MouseJoint);
                MouseJoint = nullptr;

				
                //Add a deadzone to prevent firing backwards
				bool deadzone = false;
                if (slingshotJoint)
                {
					b2Vec2 slingshotPos = slingshotJoint->GetAnchorB();
                    if (mousePos.x > slingshotPos.x - 0.5f)
                    {
						deadzone = true;
                    }
                }
                //Destroy slingshot joint so the projectile can fly
                if (slingshotJoint && !deadzone)
                {
					b2Vec2 slingshotPos = slingshotJoint->GetAnchorB();

                    Box2dWorld->DestroyJoint(slingshotJoint);
                    slingshotJoint = nullptr;

                    // Shoot projectile
                    if (projectileObject)
                    {
						b2Vec2 impulse = slingshotPos - projectileObject->GetBody()->GetPosition();
						float originalLength = impulse.Length();
						impulse.Normalize();
                        float maxForce = 6.0f; // Tweak multiplier for more/less power
						impulse *= (originalLength / 2.0f) * maxForce; 
                        projectileObject->GetBody()->ApplyLinearImpulse(impulse, projectileObject->GetBody()->GetTransform().p, true);
						projectileObject->StarRespawnTimer();
                    }
				}
            }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
			// Switch bird type
            if (projectileObject && slingshotJoint)
            {
                SwitchBird();
            }
        }
    }


    // Updating the mouse joint location every frame if it's active
    if (MouseJoint)
    {
        sf::Vector2i MousePos = sf::Mouse::getPosition(*window);
        b2Vec2 MousePoint(MousePos.x / g_sizeScale, MousePos.y / g_sizeScale);
        MouseJoint->SetTarget(MousePoint);
    }



    //Draw our physics objects.
    for (auto obj : PhysicsObjects)
    {
        obj->Draw(*window);
    }

    // Draw UI
	window->draw(*controlText);
	window->draw(*birdNormalText);
	window->draw(*birdDropText);
	window->draw(*birdBigText);
	window->draw(*descriptionText);
	window->draw(chickSpriteUI);
	window->draw(parrotSpriteUI);
	window->draw(owlSpriteUI);


    //Finally, display the window.
    window->display();
}

PhysicsObject* Game::CreatePipe(b2Vec2 _position, float _rotation)
{
    //Create a few pipe objects (static)
    PhysicsObject* pipeObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &pipeSprite,                // Sprite
        b2Vec2(0.5f, 3.0f),         // Size (in meters)
        _position,                  // Position (in meters)
        _rotation,                  // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
		this						// Pointer to the game class
    );
	pipeObject->SetHealth(100.0f, true); //Set invul
	pipeObject->SetCollisionCategory(CATEGORY_PHYSICSOBJECT);
	pipeObject->AddCollisionMask(CATEGORY_BIRD | CATEGORY_PHYSICSOBJECT | CATEGORY_DEFAULT);
    PhysicsObjects.push_back(pipeObject);

	return pipeObject;
}

PhysicsObject* Game::CreateSlingshot(b2Vec2 _position, float _rotation)
{
    slingshotObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &slingshotSprite,                // Sprite
        b2Vec2(2.5f, 3.0f),         // Size (in meters)
        _position,                  // Position (in meters)
        _rotation,                  // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
        this						// Pointer to the game class
    );
	slingshotObject->SetHealth(100.0f, true); //Set invul
	slingshotObject->setIsEnemy(false);
    PhysicsObjects.push_back(slingshotObject);
    
    return slingshotObject;
}

PhysicsObject* Game::CreateBox(b2Vec2 _position, float _rotation)
{
    //Create a few box objects (static)
    PhysicsObject* boxObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &boxSprite,                // Sprite
        b2Vec2(1.0f, 1.0f),         // Size (in meters)
        _position,                  // Position (in meters)
        _rotation,                  // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
        this						// Pointer to the game class
    );
    boxObject->SetHealth(10.0f, false); //Set health
    boxObject->SetCollisionCategory(CATEGORY_PHYSICSOBJECT);
    boxObject->AddCollisionMask(CATEGORY_BIRD | CATEGORY_PHYSICSOBJECT | CATEGORY_DEFAULT);
    PhysicsObjects.push_back(boxObject);

    return boxObject;
}

PhysicsObject* Game::CreateEnemy(b2Vec2 _position, float _rotation)
{
    // Enemies
    //Create the duck object (circle)
    PhysicsObject* duckObject = new PhysicsObject(
        b2Shape::e_polygon,          // Type (polygon = box, circle)
        &duckSprite,                // Sprite
        b2Vec2(1.0f, 1.0f),         // Size (in meters)
        _position,                  // Position (in meters)
        _rotation,                  // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                 // Pointer to the box2d world
        this						// Pointer to the game class
    );
    duckObject->SetHealth(35.0f); //Set health
    duckObject->setIsEnemy(true); //Set as enemy
    duckObject->SetCollisionCategory(CATEGORY_PHYSICSOBJECT);
    duckObject->AddCollisionMask(CATEGORY_PHYSICSOBJECT | CATEGORY_DEFAULT | CATEGORY_BIRD);
    PhysicsObjects.push_back(duckObject);

	return duckObject;
}

void Game::CreateLevel(int _level)
{
	//Clear everything and start fresh
    if (MouseJoint)
    {
        Box2dWorld->DestroyJoint(MouseJoint);
        MouseJoint = nullptr;
    }
    if (slingshotJoint)
    {
        Box2dWorld->DestroyJoint(slingshotJoint);
        slingshotJoint = nullptr;
    }
    projectileObject = nullptr;
    
    for (auto obj : PhysicsObjects)
    {
        delete obj;
	}
	PhysicsObjects.clear();
	// Reset variables
    birdMode = BIRD_NORMAL;
    birdNormalLeft = birdNormalAmmo;
    birdDropLeft = birdDropAmmo;
    birdBigLeft = birdBigAmmo;
    enemiesLeft = 5;
	// Update UI
    birdNormalText->setString(std::string(" x " + std::to_string(birdNormalLeft)));
    birdDropText->setString(std::string(" x " + std::to_string(birdDropLeft)));
    birdBigText->setString(std::string(" x " + std::to_string(birdBigLeft)));

    //Create contact listener
    Box2dContactListener = new MyContactList(Box2dWorld, this);
    Box2dWorld->SetContactListener(Box2dContactListener);

    //Create slingshot object
    CreateSlingshot(b2Vec2(4.0f, 12.0f), 0.0f);
    if (slingshotObject)
    {
        slingshotObject->SetCollisionCategory(CATEGORY_SPRITE);
    }

    //Create fence object (static)
    PhysicsObject* fenceObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &fenceSprite,          // Sprite
        b2Vec2(1.0f, 1.0f),      // Size (in meters)
        b2Vec2(5.0f, 13.0f),       // Position (in meters)
        0.0f,                       // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                 // Pointer to the box2d world
        this						// Pointer to the game class
    );
    fenceObject->SetHealth(100.0f, true); //Set invul
    PhysicsObjects.push_back(fenceObject);

    //Create the chick object (box)
    PhysicsObject* chickObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &chickSprite,               // Sprite
        b2Vec2(0.6f, 0.6f),         // Size (in meters)
        b2Vec2(3.0f, 12.0f),         // Position (in meters)
        40.0f,                      // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                 // Pointer to the box2d world
        this						// Pointer to the game class
    );
    chickObject->SetHealth(100.0f, true); //Set invul
    chickObject->SetCollisionCategory(CATEGORY_BIRD);
    chickObject->AddCollisionMask(CATEGORY_PHYSICSOBJECT | CATEGORY_DEFAULT);
    PhysicsObjects.push_back(chickObject);
    projectileObject = chickObject; //Set as projectile

    //Create the ground object (static)
    groundObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &groundSprite,               // Sprite
        b2Vec2(26.0f, 1.0f),         // Size (in meters)
        b2Vec2(13.0f, 14.0f),         // Position (in meters)
        0.0f,                      // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
        this						// Pointer to the game class
    );
    groundObject->SetHealth(1000.0f, true); //Make ground invulnerable
    PhysicsObjects.push_back(groundObject);

    // Setup Slingshot Joint
    b2DistanceJointDef slingshotJointDef;
    slingshotJointDef.bodyA = chickObject->GetBody();
    slingshotJointDef.bodyB = slingshotObject->GetBody();
    slingshotJointDef.collideConnected = false;
    slingshotJointDef.maxLength = 2.0f;
    slingshotJointDef.minLength = 0.0f;
    slingshotJointDef.stiffness = 100.0f;
    slingshotJointDef.damping = 0.0f;
    slingshotJointDef.length = 1.0f;
    slingshotJointDef.localAnchorB = b2Vec2(0.0f, -0.9f);
    slingshotJointDef.type = e_distanceJoint;
    slingshotJoint = (b2DistanceJoint*)Box2dWorld->CreateJoint(&slingshotJointDef);

    switch (_level)
    {
        case 1:
        {
            //Environments
            PhysicsObject* Pipe1 = CreatePipe(b2Vec2(17.0f, 11.0f), 0.0f);
            PhysicsObject* Pipe3 = CreatePipe(b2Vec2(17.0f, 9.0f), 90.0f);

            b2RevoluteJointDef RevoluteJointDef;
            RevoluteJointDef.bodyA = Pipe1->GetBody();
            RevoluteJointDef.bodyB = Pipe3->GetBody();
            RevoluteJointDef.localAnchorA = b2Vec2(0.0f, -1.8f);
            RevoluteJointDef.localAnchorB = b2Vec2(0.0f, 0.0f);
            RevoluteJointDef.upperAngle = DegreesToRadians(100);
            RevoluteJointDef.lowerAngle = DegreesToRadians(70);
            RevoluteJointDef.enableLimit = true;
            b2RevoluteJoint* RevoluteJoint = (b2RevoluteJoint*)Box2dWorld->CreateJoint(&RevoluteJointDef);

			PhysicsObject* Box1 = CreateBox(b2Vec2(14.0f, 13.0f), 0.0f);
            PhysicsObject* Box2 = CreateBox(b2Vec2(14.0f, 12.0f), 0.0f);
            PhysicsObject* Box3 = CreateBox(b2Vec2(13.0f, 13.0f), 0.0f);
            PhysicsObject* Box4 = CreateBox(b2Vec2(12.0f, 13.0f), 0.0f);
            PhysicsObject* Box5 = CreateBox(b2Vec2(11.0f, 13.0f), 0.0f);
            PhysicsObject* Box6 = CreateBox(b2Vec2(15.95f, 8.5f), 0.0f);
            PhysicsObject* Box7 = CreateBox(b2Vec2(18.05f, 8.5f), 0.0f);
            PhysicsObject* Box8 = CreateBox(b2Vec2(17.05f, 8.5f), 0.0f);
            //PhysicsObject* Box9 = CreateBox(b2Vec2(16.95f, 7.5f), 0.0f);
            PhysicsObject* Box10 = CreateBox(b2Vec2(15.0f, 13.0f), 0.0f);
            PhysicsObject* Box11 = CreateBox(b2Vec2(17.0f, 13.0f), 0.0f);
            PhysicsObject* Box12 = CreateBox(b2Vec2(19.0f, 13.0f), 0.0f);
            PhysicsObject* Box13 = CreateBox(b2Vec2(19.0f, 12.0f), 0.0f);

			//Enemies
			PhysicsObject* Duck1 = CreateEnemy(b2Vec2(13.0f, 12.0f), 0.0f);
            PhysicsObject* Duck2 = CreateEnemy(b2Vec2(14.0f, 11.0f), 0.0f);
            PhysicsObject* Duck3 = CreateEnemy(b2Vec2(16.95f, 7.5f), 0.0f);
            PhysicsObject* Duck4 = CreateEnemy(b2Vec2(16.0f, 13.0f), 0.0f);
            PhysicsObject* Duck5 = CreateEnemy(b2Vec2(18.0f, 13.0f), 0.0f);

		    break;
        }
        case 2:
        {
			PhysicsObject* Box1 = CreateBox(b2Vec2(19.0f, 13.0f), 0.0f);
			PhysicsObject* Box2 = CreateBox(b2Vec2(19.0f, 12.0f), 0.0f);
			PhysicsObject* Box3 = CreateBox(b2Vec2(19.0f, 11.0f), 0.0f);
			PhysicsObject* Box4 = CreateBox(b2Vec2(16.0f, 13.0f), 0.0f);
			PhysicsObject* Box5 = CreateBox(b2Vec2(16.0f, 12.0f), 0.0f);
			PhysicsObject* Box6 = CreateBox(b2Vec2(16.0f, 11.0f), 0.0f);
			PhysicsObject* Box7 = CreateBox(b2Vec2(17.0f, 9.0f), 0.0f);
			PhysicsObject* Box8 = CreateBox(b2Vec2(18.0f, 9.0f), 0.0f);
            PhysicsObject* Box9 = CreateBox(b2Vec2(17.5f, 5.0f), 0.0f);
            PhysicsObject* Box10 = CreateBox(b2Vec2(12.0f, 13.0f), 0.0f);
            PhysicsObject* Box11 = CreateBox(b2Vec2(12.0f, 12.0f), 0.0f);
			PhysicsObject* Box12 = CreateBox(b2Vec2(12.0f, 11.0f), 0.0f);
            PhysicsObject* Box13 = CreateBox(b2Vec2(12.0f, 10.0f), 0.0f);
            PhysicsObject* Box14 = CreateBox(b2Vec2(12.0f, 9.0f), 0.0f);
            PhysicsObject* Box15 = CreateBox(b2Vec2(12.0f, 8.0f), 0.0f);
            PhysicsObject* Box16 = CreateBox(b2Vec2(12.0f, 7.0f), 0.0f);
            PhysicsObject* Box17 = CreateBox(b2Vec2(8.0f, 11.0f), 0.0f);
            PhysicsObject* Box18 = CreateBox(b2Vec2(9.0f, 11.0f), 0.0f);

			PhysicsObject* Pipe1 = CreatePipe(b2Vec2(17.5f, 10.0f), 90.0f);
			PhysicsObject* Pipe2 = CreatePipe(b2Vec2(17.0f, 7.0f), 0.0f);
            PhysicsObject* Pipe3 = CreatePipe(b2Vec2(18.0f, 7.0f), 0.0f);
			PhysicsObject* Pipe4 = CreatePipe(b2Vec2(7.0f, 12.0f), 180.0f);
            PhysicsObject* Pipe5 = CreatePipe(b2Vec2(10.0f, 12.0f), 180.0f);
			PhysicsObject* Pipe6 = CreatePipe(b2Vec2(8.5f, 12.0f), 90.0f);
            PhysicsObject* Pipe7 = CreatePipe(b2Vec2(9.2f, 9.0f), 150.0f);
            PhysicsObject* Pipe8 = CreatePipe(b2Vec2(24.0f, 12.0f), 0.0f);
            

			//Joints
            b2RevoluteJointDef RevoluteJointDef;
            RevoluteJointDef.bodyA = Pipe6->GetBody();
            RevoluteJointDef.bodyB = Pipe4->GetBody();
            RevoluteJointDef.localAnchorA = b2Vec2(0.0f, 1.5f);
            RevoluteJointDef.localAnchorB = b2Vec2(0.0f, 0.0f);
            RevoluteJointDef.upperAngle = DegreesToRadians(90);
            RevoluteJointDef.lowerAngle = DegreesToRadians(90);
            RevoluteJointDef.enableLimit = true;
            b2RevoluteJoint* RevoluteJoint = (b2RevoluteJoint*)Box2dWorld->CreateJoint(&RevoluteJointDef);

            RevoluteJointDef.bodyA = Pipe6->GetBody();
            RevoluteJointDef.bodyB = Pipe5->GetBody();
            RevoluteJointDef.localAnchorA = b2Vec2(0.0f, -1.5f);
            RevoluteJointDef.localAnchorB = b2Vec2(0.0f, 0.0f);
            RevoluteJointDef.upperAngle = DegreesToRadians(90);
            RevoluteJointDef.lowerAngle = DegreesToRadians(90);
            RevoluteJointDef.enableLimit = true;
            b2RevoluteJoint* RevoluteJoint2 = (b2RevoluteJoint*)Box2dWorld->CreateJoint(&RevoluteJointDef);

            RevoluteJointDef.bodyA = Pipe5->GetBody();
            RevoluteJointDef.bodyB = Pipe7->GetBody();
            RevoluteJointDef.localAnchorA = b2Vec2(0.0f, 1.5f);
            RevoluteJointDef.localAnchorB = b2Vec2(0.0f, -1.7f);
            RevoluteJointDef.upperAngle = DegreesToRadians(70);
            RevoluteJointDef.lowerAngle = DegreesToRadians(-40);
            RevoluteJointDef.enableLimit = true;
            b2RevoluteJoint* RevoluteJoint3 = (b2RevoluteJoint*)Box2dWorld->CreateJoint(&RevoluteJointDef);


			//Enemies
			PhysicsObject* Duck1 = CreateEnemy(b2Vec2(17.5f, 4.0f), 0.0f);
            PhysicsObject* Duck2 = CreateEnemy(b2Vec2(17.5f, 13.0f), 0.0f);
			PhysicsObject* Duck3 = CreateEnemy(b2Vec2(12.0f, 6.0f), 0.0f);
            PhysicsObject* Duck4 = CreateEnemy(b2Vec2(8.5f, 10.0f), 0.0f);
            PhysicsObject* Duck5 = CreateEnemy(b2Vec2(24.0f, 10.0f), 0.0f);

            break;
		}
        case 3:
        {
			break;
        }
        default:
			break;
    }
}

void Game::SwitchBird()
{
    birdMode++;
    if (birdMode > BIRD_BIG) birdMode = BIRD_NORMAL;

	// Check if we have birds of that type left
    switch (birdMode)
    {
        case BIRD_NORMAL:
        if (birdNormalLeft <= 0)
        {
            birdMode++;
            if (birdMode > BIRD_BIG) birdMode = BIRD_NORMAL;
        }
		break;
        case BIRD_DROP:
        if (birdDropLeft <= 0)
        {
            birdMode++;
            if (birdMode > BIRD_BIG) birdMode = BIRD_NORMAL;
		}
        break;
        case BIRD_BIG:
        if (birdBigLeft <= 0)
        {
            birdMode++;
            if (birdMode > BIRD_BIG) birdMode = BIRD_NORMAL;
        }
        break;
    }

    switch (birdMode)
    {
    case BIRD_NORMAL:
        projectileObject->SetSprite(&chickSprite);
		descriptionText->setString("Normal Bird: Just an ordinary bird.");
		descriptionText->setFillColor(sf::Color::Yellow);
        break;
    case BIRD_DROP:
        projectileObject->SetSprite(&parrotSprite);
        descriptionText->setString("Drop Bird: Left click while in the air to drop to the ground.");
		descriptionText->setFillColor(sf::Color::Red);
        break;
    case BIRD_BIG:
        projectileObject->SetSprite(&owlSprite);
		descriptionText->setString("Growth Bird: Left click while in the air to increase size.");
		descriptionText->setFillColor(sf::Color::Cyan);
        break;
    default:
        projectileObject->SetSprite(&chickSprite);
        break;
    }
}

std::vector<PhysicsObject*> Game::GetPhysicsObjects()
{
    return PhysicsObjects;
}
