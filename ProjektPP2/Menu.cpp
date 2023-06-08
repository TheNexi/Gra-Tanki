#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		cout << "Blad w MENU przy zaladowaniu tekstury font";
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Graj");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wyjdz");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 2));

	selectedOptionIndex = 0;
}

Menu::~Menu()
{

}

void Menu::render(sf::RenderWindow& window)
{
	
	for (int i=0; i<MAX_NUMBER_OF_OPTIONS; i++)
	{
		window.draw(menu[i]);
	}

	window.display();
}

void Menu::MoveUp()
{
	if (selectedOptionIndex - 1 >= 0)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex--;
		menu[selectedOptionIndex].setFillColor(sf::Color::Red);
	}


}

void Menu::MoveDown()
{
	if (selectedOptionIndex + 1 < MAX_NUMBER_OF_OPTIONS)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex++;
		menu[selectedOptionIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::getPressedOption()
{
	return selectedOptionIndex;
}
/*
void Menu::pollEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				MoveUp();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				MoveDown();
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				// Jeœli naciœniêto Enter, zwracamy indeks aktualnie wybranego przycisku
				getPressedOption();
			}
		}
	}

}
*/
