//Main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

sf::Texture spritesheet;
sf::Sprite invader;

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
};

void Render(RenderWindow& window) {
    window.draw(invader);
};

int main() {
    RenderWindow window(sf::VideoMode(128, 128), "SFML works!");
    Load();
    while (window.isOpen()) {
        window.clear();
        //Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

