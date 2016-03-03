#include <HUD.h>

HUD::HUD()
{
	// Sets up font for heads up display
	if(!CooperFont.loadFromFile("..\\assets\\fonts\\COOPBL.TTF")) 
	{
		cout << "Error";
	}	
}

void HUD::SetHUD(int iLife, int iScore)
{
	// Lives text with appended number of lives remaining
	Lives.setFont(CooperFont);
	Lives.setString("Lives : " + to_string(iLife));
	Lives.setCharacterSize(20);

	FloatRect LivesTextBox; // Allows me to get origin in order to center text
	LivesTextBox = Lives.getLocalBounds();
	Lives.setOrigin(LivesTextBox.width / 2, LivesTextBox.height / 2);

	Lives.setPosition(50,10);
	Lives.setColor(Color::Black);

	// Scored points text with appended score
	ScoredPoints.setFont(CooperFont);
	ScoredPoints.setString("Score : " + to_string(iScore));
	ScoredPoints.setCharacterSize(20);

	FloatRect ScoredPointsBox; // Allows me to get origin in order to center text
	ScoredPointsBox = ScoredPoints.getLocalBounds();
	ScoredPoints.setOrigin(ScoredPointsBox.width / 2, ScoredPointsBox.height / 2);

	ScoredPoints.setPosition(400,10);
	ScoredPoints.setColor(Color::Black);
}