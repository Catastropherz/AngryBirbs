#include "Game.h"
#include "MyContactList.h"

Game::Game()
{
    //Creates an SFML window at a desired resolution.
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML and Box2D");
    window->setFramerateLimit(60);

    //Load textures and create sprites.
    sf::Texture* chickTexture = new sf::Texture;
    chickTexture->loadFromFile("Sprites/chick.png");
    chickSprite.setTexture(*chickTexture);
	Textures.push_back(chickTexture); //Store texture so it doesn't go out of scope

    sf::Texture* duckTexture = new sf::Texture;
    duckTexture->loadFromFile("Sprites/duck.png");
    duckSprite.setTexture(*duckTexture);
    Textures.push_back(duckTexture); //Store texture so it doesn't go out of scope

    sf::Texture* groundTexture = new sf::Texture;
    groundTexture->loadFromFile("Sprites/ground.png");
    groundSprite.setTexture(*groundTexture);
	Textures.push_back(groundTexture); //Store texture so it doesn't go out of scope

    sf::Texture* pipeTexture = new sf::Texture;
    pipeTexture->loadFromFile("Sprites/pipe.png");
    pipeSprite.setTexture(*pipeTexture);
	Textures.push_back(pipeTexture); //Store texture so it doesn't go out of scope

    //Create box2d world
    Box2dWorld = new b2World(g_gravity);

	//Create contact listener
	Box2dContactListener = new MyContactList(Box2dWorld, this);
	Box2dWorld->SetContactListener(Box2dContactListener);

    //Create the chick object (box)
    PhysicsObject* chickObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &chickSprite,               // Sprite
        b2Vec2(1.0f, 1.0f),         // Size (in meters)
        b2Vec2(5.0f, 2.0f),         // Position (in meters)
        40.0f,                      // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                 // Pointer to the box2d world
		this						// Pointer to the game class
    );
	chickObject->SetHealth(100.0f, true); //Set invul
    PhysicsObjects.push_back(chickObject);

    //Create the duck object (circle)
    PhysicsObject* duckObject = new PhysicsObject(
        b2Shape::e_circle,         // Type (polygon = box, circle)
        &duckSprite,               // Sprite
        b2Vec2(1.0f, 1.0f),         // Size (in meters)
        b2Vec2(10.0f, 4.0f),         // Position (in meters)
        0.0f,                      // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
		this						// Pointer to the game class
    );
    duckObject->SetHealth(100.0f); //Set health
	duckObject->setIsEnemy(true); //Set as enemy
    PhysicsObjects.push_back(duckObject);

    //Create the ground object (static)
    groundObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &groundSprite,               // Sprite
        b2Vec2(13.0f, 1.0f),         // Size (in meters)
        b2Vec2(6.5f, 7.0f),         // Position (in meters)
        0.0f,                      // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld,                  // Pointer to the box2d world
		this						// Pointer to the game class
    );
	groundObject->SetHealth(1000.0f, true); //Make ground invulnerable
    PhysicsObjects.push_back(groundObject);

	//b2DistanceJointDef slingshotJointDef;
 //   //set up stuff here
	//b2DistanceJoint* slingshotJoint = (b2DistanceJoint*)Box2dWorld->CreateJoint(&slingshotJointDef);

    b2Vec2 impulse = { 30,50 };
    chickObject->GetBody()->ApplyLinearImpulse(impulse, chickObject->GetBody()->GetTransform().p, true);

	PhysicsObject* Pipe1 = CreatePipe(b2Vec2(7.0f, 3.0f), 0.0f);
    PhysicsObject* Pipe2 = CreatePipe(b2Vec2(7.0f, 1.0f), 0.0f);

	b2RevoluteJointDef RevoluteJointDef;
	RevoluteJointDef.bodyA = Pipe1->GetBody();
	RevoluteJointDef.bodyB = Pipe2->GetBody();
	RevoluteJointDef.localAnchorA = b2Vec2(0.0f, -1.5f);
	RevoluteJointDef.localAnchorB = b2Vec2(0.0f, 0.0f);
    RevoluteJointDef.upperAngle = DegreesToRadians(110);
	RevoluteJointDef.lowerAngle = DegreesToRadians(70);
	RevoluteJointDef.enableLimit = true;

	b2RevoluteJoint* RevoluteJoint = (b2RevoluteJoint*)Box2dWorld->CreateJoint(&RevoluteJointDef);

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

    for (int i = 0; i < PhysicsObjects.size(); i++)
    {
        // Maybe we could tick the object here?

		//Delete physics objects that are marked for destroy
        if (PhysicsObjects[i]->IsMarkedForDestroy())
        {
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

            // Iterate through all bodies
            for (b2Body* bodyIter = Box2dWorld->GetBodyList(); bodyIter != nullptr; bodyIter = bodyIter->GetNext())
            {
                if (bodyIter->GetType() != b2_dynamicBody) continue; // Don't try to grab non-dynamic body

                b2Transform transform = bodyIter->GetTransform();
                if (bodyIter->GetFixtureList()->GetShape()->TestPoint(transform, MousePoint))
                {
                    //Found a body, set up a mouse joint with the body
                    b2MouseJointDef mouseJointDef;
                    mouseJointDef.bodyA = groundObject->GetBody(); // Static body
                    mouseJointDef.bodyB = bodyIter; // The dynamic body we clicked on
                    mouseJointDef.target = MousePoint;
                    mouseJointDef.collideConnected = true;
                    mouseJointDef.maxForce = 1000.0f * bodyIter->GetMass();
                    mouseJointDef.damping = 10.0f;
                    mouseJointDef.stiffness = 500.0f;

                    MouseJoint = (b2MouseJoint*)Box2dWorld->CreateJoint(&mouseJointDef);
                    MouseJoint->SetTarget(MousePoint);
                    break;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            //Destroy the mouse joint
            if (MouseJoint)
            {
                Box2dWorld->DestroyJoint(MouseJoint);
                MouseJoint = nullptr;
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
    PhysicsObjects.push_back(pipeObject);

	return pipeObject;
}

std::vector<PhysicsObject*> Game::GetPhysicsObjects()
{
    return PhysicsObjects;
}
