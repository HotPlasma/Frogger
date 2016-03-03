
#ifndef FROG_H
#define FROG_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class frog : public RectangleShape
{	
public:
	frog();
	
	int iFrogLives;
	int iFrogScore;

	float fDestinationX;
	float fDestinationY;
	Sprite FrogSprite;
	Texture FrogTexture;

	void SpawnFrog();
	
	void MoveUp();

	void MoveDown();
	
	void MoveLeft();
	
	void MoveRight();

	void Respawn();

};

#endif