/**
 * @file Menu.cpp
 * @brief Plik Ÿród³owy klasy Menu
 */

#include "Menu.h"


/**
 * @brief Konstruktor klasy Menu.
 * Ten konstruktor wywoluje funkcje "initBackground()" oraz wczytuje czcionke dla tekstu.
 * Nastepnie dla ka¿dego elementu menu ustawia wlasciwiosci takie jak czcionka, rozmiar znakow, kolor wypelnienia, tekst, pozycje, punkt odniesienia, kolor obrysu i grubosc obrysu
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
	menu[0].setCharacterSize(52); // Ustawienie rozmiaru znaków dla pierwszego elementu menu.
	menu[0].setFillColor(sf::Color::Blue); // Ustawienie koloru wype³nienia dla pierwszego elementu menu.
	menu[0].setString("Gracz vs Komputer"); // Ustawienie tekstu dla pierwszego elementu menu.
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 1)); // Ustawienie pozycji dla pierwszego elementu menu.
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla pierwszego elementu menu.
	menu[0].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla pierwszego elementu menu.
	menu[0].setOutlineThickness(2.5f); // Ustawienie gruboœci obrysu dla pierwszego elementu menu.


	menu[1].setFont(font); // Ustawienie czcionki dla drugiego elementu menu.
	menu[1].setCharacterSize(52); // Ustawienie rozmiaru znaków dla drugiego elementu menu.
	menu[1].setFillColor(sf::Color::White); // Ustawienie koloru wype³nienia dla drugiego elementu menu.
	menu[1].setString("Gracz vs Gracz"); // Ustawienie tekstu dla drugiego elementu menu.
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 2)); // Ustawienie pozycji dla drugiego elementu menu.
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla drugiego elementu menu.
	menu[1].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla drugiego elementu menu.
	menu[1].setOutlineThickness(2.5f); // Ustawienie gruboœci obrysu dla drugiego elementu menu.


	menu[2].setFont(font); // Ustawienie czcionki dla trzeciego elementu menu.
	menu[2].setCharacterSize(52); // Ustawienie rozmiaru znaków dla trzeciego elementu menu.
	menu[2].setFillColor(sf::Color::White); // Ustawienie koloru wype³nienia dla trzeciego elementu menu.
	menu[2].setString("Wyjdz"); // Ustawienie tekstu dla trzeciego elementu menu.
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 3)); // Ustawienie pozycji dla trzeciego elementu menu.
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2); // Ustawienie punktu odniesienia (origin) dla trzeciego elementu menu.
	menu[2].setOutlineColor(sf::Color::Black); // Ustawienie koloru obrysu dla trzeciego elementu menu.
	menu[2].setOutlineThickness(2.5f); // Ustawienie gruboœci obrysu dla trzeciego elementu menu.

	selectedOptionIndex = 0;
}

/**
 * @brief Destruktor klasy Menu.
 * 
 * Destruktor jest odpowiedzialny za zwolnienie zasobów przydzielonych w trakcie dzia³ania obiektu Menu.
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
 * Na koñcu ustawia teksture t³a za pomoc¹ funkcji setTexture()
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
 * Najpierw rysuje t³o, a nastêpnie iteruje przez wszystkie opcje menu i rysuje je na oknie.
 * Po zakoñczeniu rysowania wyœwietla zmiany na ekranie.
 *
 * @param window Okno renderowania, na którym ma byæ wyrenderowane menu.
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
 * @brief Przesuwa zaznaczenie opcji menu w górê.
 *
 * Funkcja przesuwa zaznaczenie aktualnej opcji menu w górê. Sprawdza, czy istnieje
 * poprzednia opcja do zaznaczenia, i jeœli tak, zmienia kolor aktualnie zaznaczonej
 * opcji na bia³y, zmniejsza indeks zaznaczonej opcji o 1 i zmienia kolor nowej
 * zaznaczonej opcji na niebieski.
 *
 * Zaznaczanie opcji odbywa siê na podstawie indeksu wybranej opcji (selectedOptionIndex).
 *
 * @note Jeœli aktualnie zaznaczona opcja jest pierwsz¹ opcj¹, nie zostanie wykonana ¿adna zmiana.
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
 * @brief Przesuwa zaznaczenie opcji menu w dó³.
 *
 * Funkcja przesuwa zaznaczenie aktualnej opcji menu w dó³. Sprawdza, czy istnieje
 * nastêpna opcja do zaznaczenia, i jeœli tak, zmienia kolor aktualnie zaznaczonej
 * opcji na bia³y, zwiêksza indeks zaznaczonej opcji o 1 i zmienia kolor nowej
 * zaznaczonej opcji na niebieski.
 *
 * Zaznaczanie opcji odbywa siê na podstawie indeksu wybranej opcji (selectedOptionIndex).
 *
 * @note Jeœli aktualnie zaznaczona opcja jest ostatni¹ opcj¹, nie zostanie wykonana ¿adna zmiana.
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

