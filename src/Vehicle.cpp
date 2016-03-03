#include "Vehicles.h"
#include <random>

vehicle::vehicle(float PosX, float PosY) // Cars
{
	SetStartingPos(PosX, PosY);
	setSize(Vector2f(50,25));
	setOrigin(getSize().x / 2.0f, getSize().y / 2.0f);
	setFillColor(Color(255,0,0));
	iMoveSpeed = 1;
	bDirectionLeft = true;
	Vector2f pos = getPosition(); // A vector holding the X and Y positions of the player frog

	// Set up the cars sprites
	if (!CarTexture.loadFromFile("..\\assets\\sprites\\Car.png", sf::IntRect(0,0 , 50, 25)))
	{
    // error...
	}
	
	CarSprite.setTexture(CarTexture);
	CarSprite.setScale(1,1);
	CarSprite.setOrigin(getSize().x / 2.0f, getSize().y / 2.0f);
	CarSprite.setPosition(getPosition().x, getPosition().y);
}

void vehicle::SetStartingPos(float PosX, float PosY) // Sets a vehicles starting point
{
	setPosition(PosX,PosY);
}

void vehicle::MoveVehicle()
{
	Vector2f pos = getPosition();
	if (bDirectionLeft) // If the direction is left 
	{
		pos.x += iMoveSpeed; // Sets movement speed to the right
		setPosition(pos.x,pos.y); // Sets position for vehicle

		if (getPosition().x > 800) // If car has hit screen
		{
			setPosition(0 - getSize().x, getPosition().y); // Spawn car on left side of screen
		}
	}
	else if (!bDirectionLeft) // If the direction is right
	{
		pos.x -= iMoveSpeed; // Movement speed set towards left
		setPosition(pos.x,pos.y);

		if (getPosition().x < 0) // if car has hit the screen
		{
			setPosition(800 + getSize().x, getPosition().y);
		}
	}
	// Refreshes textures
	CarSprite.setTexture(CarTexture);
	CarSprite.setPosition(getPosition().x, getPosition().y);
}

bool vehicle::collide(frog &frog) // if a vehicle collides with frog
{
	FloatRect CarBoundingBox = getGlobalBounds();
	FloatRect FrogBoundingBox = frog.getGlobalBounds();
	if (FrogBoundingBox.intersects(CarBoundingBox))
	{
		return true;
	}

	else
	{
		return false;
	}
}