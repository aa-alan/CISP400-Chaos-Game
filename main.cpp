#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

	// Loading font to disk, exit program on failure to load font
	Font font;
	if (!font.loadFromFile("fonts/Roboto-Thin.ttf"))
	{
		exit(0);
	}
	
	// Declaring text object
	Text text;
	text.setFont(font);
	text.setString("Chaos Game");
	text.setCharacterSize(120);
	// Custom color setting
	Color color(225, 225, 225);
	text.setFillColor(color);
	
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Frame processing
		window.clear();
		window.draw(text);
		window.display();
	}

	return 0;
}