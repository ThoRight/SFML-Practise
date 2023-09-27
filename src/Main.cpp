#include <time.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
    //srand(time(NULL));
    Game game(1024,768);
    game.run();
    /*while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
        }
        else
        {
        }

        window.clear();
       // window.draw();
        window.display();

    }*/

    return 0;
}