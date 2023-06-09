#include "Menu.h"

Menu::Menu(float width, float height)
{
	initBackground();
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		cout << "Blad w MENU przy zaladowaniu tekstury font";
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(52);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("Gracz vs Komputer");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 1));
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setOutlineColor(sf::Color::Black);
	menu[0].setOutlineThickness(2.5f);

	menu[1].setFont(font);
	menu[1].setCharacterSize(52);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Gracz vs Gracz");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 2));
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2); 
	menu[1].setOutlineColor(sf::Color::Black);
	menu[1].setOutlineThickness(2.5f);

	menu[2].setFont(font);
	menu[2].setCharacterSize(52);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjdz");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 3));
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2); 
	menu[2].setOutlineColor(sf::Color::Black);
	menu[2].setOutlineThickness(2.5f);

	selectedOptionIndex = 0;

}

Menu::~Menu()
{

}

void Menu::initBackground()
{
	background.setSize(sf::Vector2f(800.f, 600.f));
	
	if (!background_texture.loadFromFile("Textures/tlo2.png"))
	{
		std::cout << "Blad zaladowania tekstury tla!\n";
	}
	background.setTexture(&background_texture);

}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(background);

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
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}


}

void Menu::MoveDown()
{
	if (selectedOptionIndex + 1 < MAX_NUMBER_OF_OPTIONS)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex++;
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}
}

int Menu::getPressedOption()
{
	return selectedOptionIndex;
}

