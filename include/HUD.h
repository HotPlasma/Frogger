#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HUD
{
public:
	HUD();
	Font CooperFont;

	Text Lives;
	Text ScoredPoints;

	void SetHUD(int Life, int Score);
};

#endif