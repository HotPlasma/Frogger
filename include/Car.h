#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vehicles.h"

using namespace sf;
using namespace std;


class car : public vehicle
{
public:
	car( float PosX, float PosY );


};

#endif