#include "SFML/Graphics.hpp"
#include "box2d\box2D.h"
#include <iostream>
#include <vector>
#include "PhysicsLibrary.h"
#include "PhysicsObject.h"

using namespace std;

int main()
{
    //Creates an SFML window at a desired resolution.
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML and Box2D");
    window.setFramerateLimit(60);     

	//Load textures and create sprites.
    sf::Texture chickTexture;
	chickTexture.loadFromFile("Sprites/chick.png");
	sf::Sprite chickSprite(chickTexture);

    sf::Texture groundTexture;
    groundTexture.loadFromFile("Sprites/ground.png");
    sf::Sprite groundSprite(groundTexture);

    //Create box2d world
    b2World* Box2dWorld = new b2World(g_gravity);

    vector<PhysicsObject*> PhysicsObjects;

    //Create the chick object (box)
    PhysicsObject* chickObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
		&chickSprite,               // Sprite
        b2Vec2(1.0f, 1.0f),         // Size (in meters)
        b2Vec2(5.0f, 2.0f),         // Position (in meters)
        40.0f,                      // Rotation (in degrees)
        b2_dynamicBody,             // Body type (static, kinematic, dynamic)
		Box2dWorld                  // Pointer to the box2d world
    );       
	PhysicsObjects.push_back(chickObject);

    PhysicsObject* groundObject = new PhysicsObject(
        b2Shape::e_polygon,         // Type (polygon = box, circle)
        &groundSprite,               // Sprite
        b2Vec2(13.0f, 1.0f),         // Size (in meters)
        b2Vec2(6.5f, 7.0f),         // Position (in meters)
        0.0f,                      // Rotation (in degrees)
        b2_staticBody,             // Body type (static, kinematic, dynamic)
        Box2dWorld                  // Pointer to the box2d world
    );
    PhysicsObjects.push_back(groundObject);

	b2MouseJoint* MouseJoint = nullptr;

    //This is the drawing section for SFML.
    while (window.isOpen())
    {
        //Step the world physics forward
		Box2dWorld->Step(g_timeStep, 8, 3);

        //Clear the previous window. If we don't do this, we will draw on top of previous stuff.
        window.clear();

        //Window events:
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                //Check if a mouse location is inside a body after converting location to meters
				sf::Vector2i MousePos = sf::Mouse::getPosition(window);
				b2Vec2 MousePoint(MousePos.x / g_sizeScale, MousePos.y / g_sizeScale);
                
                // Iterate through all bodies
                for (b2Body* bodyIter = Box2dWorld->GetBodyList(); bodyIter != nullptr; bodyIter = bodyIter->GetNext())
                {
                    if(bodyIter->GetType() != b2_dynamicBody) continue; // Don't try to grab non-dynamic body

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
            sf::Vector2i MousePos = sf::Mouse::getPosition(window);
            b2Vec2 MousePoint(MousePos.x / g_sizeScale, MousePos.y / g_sizeScale);
			MouseJoint->SetTarget(MousePoint);
        }

		//Draw our physics objects.
        for (auto obj : PhysicsObjects)
        {
			obj->Draw(window);
        }


        //Finally, display the window.
        window.display();
    }


    // Cleanup
    for(auto obj : PhysicsObjects)
    {
        delete obj;
	}

	delete Box2dWorld;
	Box2dWorld = nullptr;
    return 0;
}