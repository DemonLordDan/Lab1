#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D
};

void Player::Update(double dt) {
    //Move in four directions based on keys
    

        Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}

int main() {
    RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML works!");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}