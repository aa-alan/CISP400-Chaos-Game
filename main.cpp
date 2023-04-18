#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

using namespace sf;
using namespace std;

int main()
{
	// Seeding rand()
	srand(time(0));
	const int MAX_VERTICES = 2; // For rand(); for vector indexes 0-2

	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

	// For handling mouse-related events
	sf::Event event;

	// Loading font to disk, exit program on failure to load font
	Font titleFont;
	if (!titleFont.loadFromFile("fonts/Roboto-BoldItalic.ttf"))
	{
		window.close();
	}
	
	// Declaring text object
	Text title; // Chaos Game title
	Text instruct; // lets user know what to do
	Text mousePos;

	mousePos.setFont(titleFont);
	mousePos.setFillColor(sf::Color::White);
	mousePos.setCharacterSize(24);

	// Title processing
	title.setFont(titleFont);
	title.setString("Chaos Game!");
	title.setCharacterSize(80);
	// Custom color setting
	Color color(225, 225, 225);
	title.setFillColor(color);

	// To center title at top of screen
	FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0, 0);
	title.setPosition(window.getSize().x / 2.0, 0);

	// Instruct processing
	Font instructFont;
	if (!instructFont.loadFromFile("fonts/Roboto-Thin.ttf"))
	{
		window.close();
	}
	instruct.setFont(instructFont);
	instruct.setString("Click three times on the screen to set triangle vertices");
	instruct.setCharacterSize(60);

	// To center instructions at bottom of screen
	textRect = instruct.getLocalBounds();
	instruct.setOrigin(textRect.left + textRect.width / 2.0, 0);
	instruct.setPosition(window.getSize().x / 2.0, window.getSize().y / 1.2);
	
	// Setting up mouse click tracking
	int mouseClick = 0;
	vector<int> mousePosX;
	vector<int> mousePosY;

	// Chaos Game algorithm starts when 4 clicks have been registered
	bool algorithmStart = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event) && mouseClick != 4)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left 
					|| event.mouseButton.button == sf::Mouse::Right)
				{
					mouseClick++;
					mousePosX.push_back(event.mouseButton.x);
					mousePosY.push_back(event.mouseButton.y);
					// Mouse click text decisions
					if (mouseClick == 3)
					{
						instruct.setString("Click once more to ready the program");
						textRect = instruct.getLocalBounds();
						instruct.setOrigin(textRect.left + textRect.width / 2.0, 0);
						instruct.setPosition(window.getSize().x / 2.0, window.getSize().y / 1.2);
					}
					if (mouseClick > 3)
					{
						// Remove text from screen
						title.setFillColor(sf::Color::Black);
						instruct.setFillColor(sf::Color::Black);
						algorithmStart = true;
					}
				}
			}
		}

		// After 4 clicks, generate new points
		if (algorithmStart)
		{
			// Generate midpoints
			int vertex = rand() % (MAX_VERTICES + 1);
			float midpointX = (mousePosX[vertex] + mousePosX.back()) / 2.0;
			float midpointY = (mousePosY[vertex] + mousePosY.back()) / 2.0;

			// Add midpoint values to the back of the coordinate vectors
			mousePosX.push_back(midpointX);
			mousePosY.push_back(midpointY);
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Frame processing
		window.clear();
		window.draw(title);
		window.draw(instruct);

		// Display points
		for (int i = 0; i < mousePosX.size(); i++)
		{
			
		}
		window.display();
	}

	return 0;
}