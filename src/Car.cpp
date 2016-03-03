#include "Car.h"

car::car( float PosX, float PosY ) : vehicle( PosX, PosY )
{
	setSize(Vector2f(50,25));
	setOrigin(getSize().x / 2.0f, getSize().y / 2.0f);
	setFillColor(Color(255,0,0));
}
