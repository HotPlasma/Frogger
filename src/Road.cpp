#include "Road.h"
#include <vector>

Road::Road() 
{
	bool bCurrentDirectionLeft = true; // Cars on a road go left if true and right if false
} 

Road::Road(int iPosY, int iNumCars) // Positions road and spawns cars on roads.
{
	// Generates randomised speed for the set of cars
	int iMinSpeed = 1; 
	int iMaxSpeed = 5;
	int range = iMaxSpeed - iMinSpeed; // Creates a range
	int iRandSpeed = iMinSpeed + (rand() % range); // Creates acceptable range for randomised number

	if (bCurrentDirectionLeft) // If cars need to go left
	{
		int iXPos = 800; // X position for cars
		for(int i=0; i < iNumCars; ++i) // For the number of cars
		{
			// Generate random x distance away from the end of the screen
			int iMinDist = 100; 
			int iMaxDist = 600;
			int range = iMaxDist - iMinDist; // Creates a range
			int iRandX = iMinDist + (rand() % range); // Creates acceptable range for randomised number

		
			iXPos = iXPos - iRandX; // Subtracts random distance from starting location 

			cars.push_back(vehicle(iXPos, iPosY)); // Creates a car with a randomised X positon on each road
			cars[i].iMoveSpeed = iRandSpeed; // Pass iMove speed to cars on this road
			cars[i].bDirectionLeft = true; // Set direction to direction to left
			cars[i].CarSprite.setRotation(0.0f); // Cars pointing right
			bCurrentDirectionLeft = false; // Switch next road to opposite
		}
	}
	else if (!bCurrentDirectionLeft) //If cars need to go right
	{
		int iXPos = 100; // X position for cars
		for(int i=0; i < iNumCars; ++i)
		{
			int iMinDist = 100; 
			int iMaxDist = 600;
			int range = iMaxDist - iMinDist; // Creates a range
			int iRandX = iMinDist + (rand() % range); // Creates acceptable range for randomised number

			iXPos = iXPos + iRandX; // Adds random distance from starting location  

			cars.push_back(vehicle(iXPos, iPosY)); // Creates a car with a randomised X positon on each road
			cars[i].iMoveSpeed = iRandSpeed;
			cars[i].bDirectionLeft = false; // Set direction to direction to left
			cars[i].CarSprite.setRotation(180.0f); // Rotate cars to face left
			bCurrentDirectionLeft = true; // Switch next road to face left
		}
	}

	// Sets size of roads
	road.setSize(Vector2f(800,24));

	// Road sprite setup
	if (!RoadTexture.loadFromFile("..\\assets\\sprites\\Road.png", sf::IntRect(0, 0, 800, 24)))
	{
    // error...
	}
	RoadSprite.setOrigin(road.getSize().x / 2.0f, road.getSize().y / 2.0f);
	RoadSprite.setTexture(RoadTexture);
	RoadSprite.setScale(1,1);
	RoadSprite.setPosition(400, iPosY);
}


bool Road::collision(frog &frog) // If cars on the road collide with frog
{
	for(int i=0; i < cars.size(); ++i) // For the number of cars in the vector
	{
		if(cars[i].collide(frog)) // If any car collides with the frog
			{
				return true; // Collsion
			}
	}

	return false; // No collision
}

void Road::update() // Moves each vehicle and sets each texture
{
	for(int i=0; i < cars.size(); ++i) // For the length of the vector holding cars
	{
		cars[i].MoveVehicle(); // Move each vehicle
		cars[i].CarSprite.setTexture(cars[i].CarTexture);
		cars[i].CarSprite.setPosition(cars[i].getPosition().x, cars[i].getPosition().y);
	}
	RoadSprite.setTexture(RoadTexture);
}


void Road::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(RoadSprite); // Draw roads to window
	for(int i=0; i < cars.size(); ++i) // For every car in vector
	{
		target.draw(cars[i].CarSprite); // Draw cars sprites to window
	}
}
