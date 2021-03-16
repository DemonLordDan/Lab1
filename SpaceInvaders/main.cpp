//Main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"


using namespace std;
using namespace sf;


std::vector<Ship*> ships;

sf::Texture spritesheet;
//sf::Sprite invader;

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
    ships.push_back(inv);
};

void Render(RenderWindow& window) {
    for (int i = 0; i < ships.size(); i++) {
    ships[i];
    }
};


int main() {
    Clock clock;
    float dt = clock.restart().asSeconds();
    RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML works!");
    Load();
    while (window.isOpen()) {
        window.clear();
        //Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

