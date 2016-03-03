#include "Frog.h"

frog::frog()
{
	iFrogLives = 3;
	iFrogScore = 0;
	fDestinationX = 425; // X destination player will move to
	fDestinationY = 575; // X destination player will move to
	Vector2f pos = getPosition(); // A vector holding the X and Y positions of the player frog

	// Loads and sets frog texture
	if (!FrogTexture.loadFromFile("..\\assets\\sprites\\Frog.png", sf::IntRect(getPosition().x, getPosition().y, 24, 24)))
	{
    // error...
	}
	FrogSprite.setTexture(FrogTexture);
	FrogSprite.setScale(1,1);
	FrogSprite.setPosition(getPosition().x, getPosition().y);

}
void frog::SpawnFrog() // Sets frog's attributes
{
	setSize(Vector2f(23,23));
	setOrigin(getSize().x / 2.0f, getSize().y / 2.0f); // Sets origin to centre
	setFillColor(Color(0,255,0)); // Green
	setPosition(getPosition().x, getPosition().y);
	FrogSprite.setOrigin((getSize().x / 2.0f) + 2, getSize().y / 2.0f);
	FrogSprite.setPosition(getPosition().x, getPosition().y);
	setOutlineThickness(1);
	setOutlineColor((Color(0,0,0)));
}

void frog::MoveUp() // Moves player up
{
	Vector2f pos = getPosition();

	fDestinationY = getPosition().y - 25; // Moves desitination 25px forward
	while (getPosition().y != fDestinationY) // While the position of the frog doesn't equal the destination
	{
		if (fDestinationY > 0) // Let the player move
		{
			pos.y -= 25;
			setPosition(pos);
		}
		else // If the player reaches the end of the screens
		{

			iFrogScore += 100; // Increase score
			// Return destinations to default
			fDestinationX = 425;
			fDestinationY = 575;
			// Reset positions
			pos.x = 425;
			pos.y = 575;
			setPosition(pos);
		}
	}
	//Sets frog facing up
	FrogSprite.setRotation(0.0f);
}

void frog::MoveDown()
{
	Vector2f pos = getPosition();

	fDestinationY = getPosition().y + 25; // Moves desitination 25px down
	while (getPosition().y != fDestinationY) // While the position of the frog doesn't equal the destination
	{
		if (fDestinationY < 600)  //Let the player move
		{
			pos.y += 25;
			setPosition(pos);
		}
		else // Unless the player about to leave the screen
		{
			fDestinationY = getPosition().y;
		}
	}
	FrogSprite.setRotation(180.0f); // Set frog facing down
}

void frog::MoveLeft()
{
	Vector2f pos = getPosition();

	fDestinationX = getPosition().x - 25; // Moves desitination 25px left
	while (getPosition().x != fDestinationX) // While the position of the frog doesn't equal the destination
	{
		if (fDestinationX > 0)
		{
			pos.x -= 25;
			setPosition(pos);
		}
		else // Don't let the player about to leave the screen
		{
			fDestinationX = getPosition().x;
		}
	}
	FrogSprite.setRotation(270.0f); // Position facing left
}

void frog::MoveRight() 
{
	Vector2f pos = getPosition();

	fDestinationX = getPosition().x + 25; // Moves desitination 25px right
	while (getPosition().x != fDestinationX) // While the position of the frog doesn't equal the destination
	{
		if (fDestinationX < 800)
		{
			pos.x += 25;
			setPosition(pos);
		}
		else // Don't let the player about to leave the screen
		{
			fDestinationX = getPosition().x;
		}
	}
	FrogSprite.setRotation(90.0f); // Positions facing right
}

void frog::Respawn() // Resets frogs position to starting position and takes a life
{
	Vector2f pos = getPosition();
	pos.x = 425;
	pos.y = 575;
	setPosition(pos);
	iFrogLives--;
}

