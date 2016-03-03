/* 
Programmer: Jegor Kharlamov - P14148686
Project: Frogger
*/

#include "Frog.h"
#include "Road.h"
#include "HUD.H"

void MainMenu(Font& CooperFont,Font& BritanicFont);
void Game(Font& CooperFont,Font& BritanicFont, frog& Player);
void EndGame(Font& CooperFont,Font& BritanicFont, frog& Player);
void ResetGame(); 


RenderWindow window(VideoMode(800, 600), "Frogger"); // Global window for drawing to

int main()
{
	Font CooperFont; // Font for title screen
	Font BritanicFont; // Font instructions on title screen
	if(!CooperFont.loadFromFile("..\\assets\\fonts\\COOPBL.TTF")) {}
	if(!BritanicFont.loadFromFile("..\\assets\\fonts\\BRITANIC.TTF")) {}

	frog Player;
	// Game Loop
	while (window.isOpen())
	{
		MainMenu(CooperFont,BritanicFont);
		Game(CooperFont,BritanicFont, Player);
		EndGame(CooperFont,BritanicFont, Player);
	}
}

void MainMenu(Font& CooperFont,Font& BritanicFont) // Draws the main menu
{
	window.setFramerateLimit(60); // Frame Limit

	Text FroggerText; // Text that says "Frogger" on the start screen.
	
	FroggerText.setFont(CooperFont);
	FroggerText.setString("Frogger");
	FroggerText.setCharacterSize(50);

	FloatRect FroggerTitleBox; // Allows me to get origin in order to center text properly
	FroggerTitleBox = FroggerText.getLocalBounds();
	FroggerText.setOrigin(FroggerTitleBox.width / 2, FroggerTitleBox.height / 2);

	FroggerText.setPosition(400,200);
	FroggerText.setColor(Color::Green);

	Text InstructionText; // Text that tells player to press enter

	InstructionText.setFont(CooperFont);
	InstructionText.setString("Press Enter to Start");
	InstructionText.setCharacterSize(50);

	FloatRect InstructionTextBox; // Allows me to get origin in order to center text text properly
	InstructionTextBox = InstructionText.getLocalBounds();
	InstructionText.setOrigin(InstructionTextBox.width / 2, InstructionTextBox.height / 2);

	InstructionText.setPosition(400,300);
	InstructionText.setColor(Color::Red);


	while (window.isOpen())
	{
		Event MenuEvent;
		while (window.pollEvent(MenuEvent))
		{
			if (MenuEvent.type == Event::Closed)
			{
				window.close(); // Allows window to close during main menu
			}
			else if (MenuEvent.type == Event::KeyPressed) // Player movement
			{
				if (MenuEvent.key.code == Keyboard::Return) // Waits for enter to be pressed before continuing the game
				{
					return; // Continues game loop
				}
			}
		}

		window.clear(Color(9,110,34)); //Background colour
		// Draws required text
		window.draw(FroggerText);
		window.draw(InstructionText);

		window.display();
	}	
}

void Game(Font& CooperFont,Font& BritanicFont, frog& Player) // Actual gameplay
{
	vehicle Cars(0, 425); // Initialise games vehicles
	HUD ScreenDisplay; // Initialise HUD

	const int kiNumRoads = 4; // 4 roads per array
	Road Roads[kiNumRoads]; // Array holding roads to be drawn
	Road Roads2[kiNumRoads];
	Road Roads3[kiNumRoads];

	for(int i=0; i < kiNumRoads; ++i) // For every road
	{
		Roads[i] = Road((i+17)*25); // Position the roads and put them apart
		Roads2[i] = Road((i+11)*25);
		Roads3[i] = Road((i+5)*25);
	}

	Player.setPosition(425, 575); // Sets starting positions of frog
	Player.SpawnFrog(); // Spawns frog
	
	ScreenDisplay.SetHUD(Player.iFrogLives,Player.iFrogScore); // Sets up HUD

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close during gameplay
			}
			else if (event.type == Event::KeyPressed) // Player movement
			{
				if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up)
				{
					Player.MoveUp();
					ScreenDisplay.SetHUD(Player.iFrogLives,Player.iFrogScore); // Updates score if end of the screen is reached
				}
				else if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left)
				{
					Player.MoveLeft();
				}
				else if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) 
				{
					Player.MoveDown();
				}
				else if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right) 
				{
					Player.MoveRight();
				}
			}
		}

		window.clear(Color(9,110,34)); // Dark green background

		for(int i=0; i < kiNumRoads; ++i) // For the number of roads
		{
			Roads[i].update(); // Move cars on each set of roads
			Roads2[i].update();
			Roads3[i].update();

			if (Roads[i].collision(Player)) // If player collides with car on road
			{
				if (Player.iFrogLives > 0) // If player has more than zero lives
				{
					Player.Respawn(); // Respawn player
					ScreenDisplay.SetHUD(Player.iFrogLives,Player.iFrogScore); // Updates lives in HUD
				}
				else
				{
					return; // Return to end game screen
				}
			}
			if (Roads2[i].collision(Player)) // Collision for road set 2
			{
				if (Player.iFrogLives > 0)
				{
					Player.Respawn();
					ScreenDisplay.SetHUD(Player.iFrogLives,Player.iFrogScore); // Updates lives in HUD
				}
				else
				{
					return;
				}
			}
			if (Roads3[i].collision(Player)) // Collision for road set 3
			{
				if (Player.iFrogLives > 0)
				{
					Player.Respawn();
					ScreenDisplay.SetHUD(Player.iFrogLives,Player.iFrogScore); // Updates lives in HUD
				}
				else
				{
					return;
				}
			}
			
			//Draw all 3 sets of roads
			window.draw(Roads[i]);
			window.draw(Roads2[i]);
			window.draw(Roads3[i]);
		}
		
		Player.FrogSprite.setPosition(Player.getPosition().x, Player.getPosition().y); // Sets position of the player sprite after the player is killed
		window.draw(Player.FrogSprite); // Sets frogger sprite position
		// Draws HUD
		window.draw(ScreenDisplay.Lives); 
		window.draw(ScreenDisplay.ScoredPoints);

		window.display();
	}
}

void EndGame(Font& CooperFont,Font& BritanicFont, frog& Player)
{
	// Creates Game Over text
	Text GameOverText;
	GameOverText.setFont(CooperFont);
	GameOverText.setString("Game Over!");
	GameOverText.setCharacterSize(100);

	FloatRect GameOverTextBox; // Allows me to get origin in order to center text
	GameOverTextBox = GameOverText.getLocalBounds();
	GameOverText.setOrigin(GameOverTextBox.width / 2, GameOverTextBox.height / 2);

	GameOverText.setPosition(400,200);
	GameOverText.setColor(Color::Red);

	// Displays final score message with the actual final player score appended
	Text FinalScore;
	FinalScore.setFont(CooperFont);
	FinalScore.setString("Final Score: " + to_string(Player.iFrogScore));
	FinalScore.setCharacterSize(50);

	FloatRect FinalScoreTextBox; // Allows me to get origin in order to center text
	FinalScoreTextBox = FinalScore.getLocalBounds();
	FinalScore.setOrigin(FinalScoreTextBox.width / 2, FinalScoreTextBox.height / 2);

	FinalScore.setPosition(400,300);
	FinalScore.setColor(Color::Yellow);
	
	// Initialises the text which tells the player how to restart the game
	Text RestartText;
	RestartText.setFont(CooperFont);
	RestartText.setString("Press enter to play again!");
	RestartText.setCharacterSize(25);

	FloatRect RestartTextTextBox; // Allows me to get origin in order to center text
	RestartTextTextBox = RestartText.getLocalBounds();
	RestartText.setOrigin(RestartTextTextBox.width / 2, RestartTextTextBox.height / 2);

	RestartText.setPosition(400,450);
	RestartText.setColor(Color::White);

	while (window.isOpen())
	{
		Event EndGameEvent;
		while (window.pollEvent(EndGameEvent))
		{
			if (EndGameEvent.type == Event::Closed)
			{
				window.close(); // Allows window to close during endgame screen
			}
			else if (EndGameEvent.type == Event::KeyPressed) // Player movement
			{
				if (EndGameEvent.key.code == Keyboard::Return) // Waits for enter to be pressed before continuing the game
				{
					// Resets lives and score and then returns to loop which restarts the game
					Player.iFrogLives = 3;
					Player.iFrogScore = 0;
					return;
				}
			}
		}
		window.clear(Color(9,110,34)); //Background

		//Draws above text
		window.draw(GameOverText); 
		window.draw(FinalScore);
		window.draw(RestartText);

		window.display();
	}
}
