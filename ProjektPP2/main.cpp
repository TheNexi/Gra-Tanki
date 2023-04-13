#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
    //Okno gry
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gra Tanki", sf::Style::Close); //Style button close
    sf::Event ev;
    //Okno gry koniec

    //Petla gry

    while (window.isOpen())
    {
        //Podczas otwartego okna
        while (window.pollEvent(ev))
        {
            //Zmiana dzialania
            switch (ev.type)
            {
            //zamykanie gry
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            //zamykanie gry koniec
            
            //poruszanie sie obiektu

              


            //poruszanie sie obiektu koniec
            }
        





        }
        //Update




        //Render
        window.clear(); // (sf::Color::Green)

        //Stworz gre

        window.display();


    }
    
    //Petla gry koniec



  
    return 0;
}
/*
//sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

*/