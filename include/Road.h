#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Vehicles.h>
#include <Frog.h>
#include <vector>

using namespace sf;
using namespace std;


class Road : public Drawable
{
public:
	vector<vehicle> cars;
	RectangleShape road;
	Sprite RoadSprite;
	Texture RoadTexture;
	bool bCurrentDirectionLeft;

	Road();
	Road(int fPosY, int iNumCars=3);

	void update();

	bool Road::collision( frog &frog );

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif