#ifndef VEHICLES_H
#define VEHICLES_H

#include <iostream>
#include "Frog.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class vehicle : public RectangleShape
{
public:
	Sprite CarSprite;
	Texture CarTexture;

	int iMoveSpeed;
	bool bDirectionLeft;
	bool bCurrentDirectionLeft;
	vehicle(float PosX, float PosY);
	void SetStartingPos(float PosX, float PosY);
	virtual void MoveVehicle();

	bool collide(frog &frog);

};

#endif