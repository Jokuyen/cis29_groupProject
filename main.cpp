///////
/////// WORKS JUST FINE
///////
//
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include "Coins.h"
//
//int main() {
//
//    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Welcome!", sf::Style::Close | sf::Style::Default);
//    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
//    sf::SoundBuffer buffer;
//
//    if (!buffer.loadFromFile("1_Coins.wav")) {
//        std::cout << "Error " << std:: endl;
//    }
//
//    sf::Sound sound;
//
//    sound.setBuffer(buffer);
//    Coins gameCoins(sound);
//
//    player.setFillColor(sf::Color::Red);
//
//
//    while (window.isOpen()) {
//        sf::Event evnt;
//        while (window.pollEvent(evnt)) {
//
//            switch (evnt.type) {
//                case sf::Event::Closed:
//                    window.close();
//                    break;
//                case sf::Event::Resized:
//                    std::cout << "New window: " << evnt.size.width << "\t" << evnt.size.height <<std::endl;
//                    break;
//                case sf::Event::TextEntered:
//                    if (evnt.text.unicode < 128) {
//                        std::cout << evnt.text.unicode << std::endl;
//                    }
//                    break;
//                case sf::Event::KeyPressed: {
//
//                    if (evnt.type == sf::Event::MouseButtonPressed) {
//                        if (evnt.mouseButton.button == sf::Mouse::Right)
//                        {
//                            std::cout << "the right button was pressed" << std::endl;
//                            std::cout << "mouse x: " << evnt.mouseButton.x << std::endl;
//                            std::cout << "mouse y: " << evnt.mouseButton.y << std::endl;
//                        }
//                    }
//                }
//            }
//
//        }
//
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//            player.setPosition( static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
//            gameCoins.playsound();
//            std::cout << "fuck\n";
//        }
//
//
//        window.clear();
//        window.draw(player);
//        window.display();
//
//    }
//
//
//    return 0;
//}






////
//// GROUP ALGORITHM
////


/*
 DOCUMENTATION
 ----------------------------------------------------------------------------
 Screen 0: Introduction Screen (This is where the name of the game should be)
 Screen 1: Gameplay Screen
 Screen 2: Help/Controls Screen
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "cScreen.h"
#include "screen_0.h"
#include "screen_1.h"
#include "screen_2.h"
#include "screen_3.h"
#include "screen_4.h"
#include "screen_5.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
using namespace std;


int main(int argc, char** argv)
{
    const int SCREENWIDTH = 2048;
    const int SCREENHEIGHT = 1536;
    srand(static_cast<unsigned int>(time(NULL))); // To randomize the rand() function within Monster::randomNumber()

    cout << "just fine.\n";

    // Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;

    // Window creation
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "CIS 29 Game Project");
    App.setFramerateLimit(60);

    // Screens preparation
    screen_0 s0;
    Screens.push_back(&s0);
    screen_1 s1;
    Screens.push_back(&s1);
    screen_2 s2;
    Screens.push_back(&s2);
    screen_3 s3;
    Screens.push_back(&s3);
    screen_4 s4;
    Screens.push_back(&s4);
    screen_5 s5;
    Screens.push_back(&s5);

    // Main loop
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App, SCREENWIDTH, SCREENHEIGHT);
        cout << screen << '\n';
    }


    return 0;
}

/*
 jscreens mihika$ g++ -Wall -std=c++11 *.cpp -Iinclude -I/usr/local/include -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o main
 */
