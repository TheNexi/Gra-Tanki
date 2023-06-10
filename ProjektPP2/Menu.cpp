/**
 * @file Menu.cpp
 * @brief Plik �r�d�owy klasy Menu
 */

#include "Menu.h"


/**
 * @brief Konstruktor klasy Menu.
 * Ten konstruktor wywoluje funkcje "initBackground()" oraz wczytuje czcionke dla tekstu.
 * Nastepnie dla ka�dego elementu menu ustawia wlasciwiosci takie jak czcionka, rozmiar znakow, kolor wypelnienia, tekst, pozycje, punkt odniesienia, kolor obrysu i grubosc obrysu
 * 
 * @param width Szerokosc okna, na ktorym ma byc wyrenderowane menu.
 * @param height Wysokosc okna, na ktorym ma byc wyrenderowane menu.
 */
Menu::Menu(float width, float height)
{
	// Wczytanie czczcionki dla tekstu
	initBackground();
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		cout << "Blad w MENU przy zaladowaniu tekstury font";
	}

	menu[0].setFont(font); // Ustawienie czcionki dla pierwszego elementu menu.
	menu[0].setCharacterSize(52); // Ustawienie rozmiaru znak�w dla pierwszego elementu menu.
	menu[0].setFillColor(sf::Color::Blue); // Ustawienie koloru wype�nienia dla pierwszego elementu menu.
	menu[0].setString("Gracz vs Komputer"); // Ustawienie tekstu dla pierwszego elementu menu.
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 1)); // Ustawienie pozycji dla pierwszego elementu menu.
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla pierwszego elementu menu.
	menu[0].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla pierwszego elementu menu.
	menu[0].setOutlineThickness(2.5f); // Ustawienie grubo�ci obrysu dla pierwszego elementu menu.


	menu[1].setFont(font); // Ustawienie czcionki dla drugiego elementu menu.
	menu[1].setCharacterSize(52); // Ustawienie rozmiaru znak�w dla drugiego elementu menu.
	menu[1].setFillColor(sf::Color::White); // Ustawienie koloru wype�nienia dla drugiego elementu menu.
	menu[1].setString("Gracz vs Gracz"); // Ustawienie tekstu dla drugiego elementu menu.
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 2)); // Ustawienie pozycji dla drugiego elementu menu.
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla drugiego elementu menu.
	menu[1].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla drugiego elementu menu.
	menu[1].setOutlineThickness(2.5f); // Ustawienie grubo�ci obrysu dla drugiego elementu menu.


	menu[2].setFont(font); // Ustawienie czcionki dla trzeciego elementu menu.
	menu[2].setCharacterSize(52); // Ustawienie rozmiaru znak�w dla trzeciego elementu menu.
	menu[2].setFillColor(sf::Color::White); // Ustawienie koloru wype�nienia dla trzeciego elementu menu.
	menu[2].setString("Wyjdz"); // Ustawienie tekstu dla trzeciego elementu menu.
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 3)); // Ustawienie pozycji dla trzeciego elementu menu.
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla trzeciego elementu menu.
	menu[2].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla trzeciego elementu menu.
	menu[2].setOutlineThickness(2.5f); // Ustawienie grubo�ci obrysu dla trzeciego elementu menu.

	selectedOptionIndex = 0;
}

/**
 * @brief Destruktor klasy Menu.
 * 
 * Destruktor jest odpowiedzialny za zwolnienie zasob�w przydzielonych w trakcie dzia�ania obiektu Menu.
 */
Menu::~Menu()
{

}

/**
 * @brief Inicjalizuje tlo menu.
 *
 * Funkcja ustawia rozmiar tla na szerokosc 800 pikseli i wysokosc 600 pikseli.
 * Nastepnie wczytuje teksture tla z pliku "Textures/tlo2.png" i przypisuje ja do tla.
 * W przypadku niepowodzenia wczytania tekstury, wyswietla komunikat o bledzie na standardowym wyjsciu.
 * Na ko�cu ustawia teksture t�a za pomoc� funkcji setTexture()
 */
void Menu::initBackground()
{
	background.setSize(sf::Vector2f(800.f, 600.f));
	
	if (!background_texture.loadFromFile("Textures/tlo2.png"))
	{
		std::cout << "Blad zaladowania tekstury tla!\n";
	}
	background.setTexture(&background_texture);

}

/**
 * @brief Renderuje menu na oknie renderowania.
 *
 * Najpierw rysuje t�o, a nast�pnie iteruje przez wszystkie opcje menu i rysuje je na oknie.
 * Po zako�czeniu rysowania wy�wietla zmiany na ekranie.
 *
 * @param window Okno renderowania, na kt�rym ma by� wyrenderowane menu.
 */
void Menu::render(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i=0; i<MAX_NUMBER_OF_OPTIONS; i++)
	{
		window.draw(menu[i]);
	}

	window.display();
}

/**
 * @brief Przesuwa zaznaczenie opcji menu w g�r�.
 *
 * Funkcja przesuwa zaznaczenie aktualnej opcji menu w g�r�. Sprawdza, czy istnieje
 * poprzednia opcja do zaznaczenia, i je�li tak, zmienia kolor aktualnie zaznaczonej
 * opcji na bia�y, zmniejsza indeks zaznaczonej opcji o 1 i zmienia kolor nowej
 * zaznaczonej opcji na niebieski.
 *
 * Zaznaczanie opcji odbywa si� na podstawie indeksu wybranej opcji (selectedOptionIndex).
 *
 * @note Je�li aktualnie zaznaczona opcja jest pierwsz� opcj�, nie zostanie wykonana �adna zmiana.
 */
void Menu::MoveUp()
{
	if (selectedOptionIndex - 1 >= 0)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex--;
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}


}

/**
 * @brief Przesuwa zaznaczenie opcji menu w d�.
 *
 * Funkcja przesuwa zaznaczenie aktualnej opcji menu w d�. Sprawdza, czy istnieje
 * nast�pna opcja do zaznaczenia, i je�li tak, zmienia kolor aktualnie zaznaczonej
 * opcji na bia�y, zwi�ksza indeks zaznaczonej opcji o 1 i zmienia kolor nowej
 * zaznaczonej opcji na niebieski.
 *
 * Zaznaczanie opcji odbywa si� na podstawie indeksu wybranej opcji (selectedOptionIndex).
 *
 * @note Je�li aktualnie zaznaczona opcja jest ostatni� opcj�, nie zostanie wykonana �adna zmiana.
 */
void Menu::MoveDown()
{
	if (selectedOptionIndex + 1 < MAX_NUMBER_OF_OPTIONS)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex++;
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}
}

/**
 * @brief Zwraca indeks zaznaczonej opcji menu.
 *
 * Funkcja zwraca indeks zaznaczonej opcji menu. Indeks zaznaczonej opcji
 * jest przechowywany w zmiennej selectedOptionIndex.
 *
 * @return Indeks zaznaczonej opcji menu.
 */
int Menu::getPressedOption()
{
	return selectedOptionIndex;
}

