#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::W, Keyboard::S, Keyboard::Up, Keyboard::Down 
};
Vector2f ballVelocity;
bool server = false;
Font font;
Text text;
int p1s;
int p2s;
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
    // Load font-face from res dir
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    // Set text element to use font
    text.setFont(font);
    // set the character size to 24 pixels
    text.setCharacterSize(24);
    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition((gameWidth - 10) - paddleSize.x / 2, gameHeight / 2);
    ball.setPosition(gameWidth / 2, gameHeight / 2);
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}
void Reset(bool firstPoint) {
    if (firstPoint) {
        p1s++;
    }
    else {
        p2s++;
    }
    String scoreBoard = ("(" , p1s , ") : (" , p2s , ")");
    // Update Score Text
    text.setString(scoreBoard);
    // Keep Score Text Centered
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
    ball.setPosition(gameWidth / 2, gameHeight / 2);
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}
void Update(RenderWindow& window) {
    static Clock clock;

    bool score = false;
    const float dt = clock.restart().asSeconds();

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
    bool secondP = false;
    float direction1P = 0.0f;
    float direction2P = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction1P--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction1P++;
    }
    if (!secondP) {
        if (paddles[1].getPosition().y > ball.getPosition().y) {
            direction2P--;
        }
        else if (paddles[1].getPosition().y < ball.getPosition().y) {
            direction2P++;
        }
    }
    else {
        if (Keyboard::isKeyPressed(controls[2])) {
            direction1P--;
        }
        if (Keyboard::isKeyPressed(controls[3])) {
            direction1P++;
        }
    }
    paddles[0].move(0, direction1P * paddleSpeed * dt);
    paddles[1].move(0, direction2P * paddleSpeed * dt);
    ball.move(ballVelocity * dt);
    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
      // bottom wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    else if (by < 0) { //top wall
     // top wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    else if (bx > gameWidth) {
        // right wall
        server = true;
        Reset(server);
    }
    else if (bx < 0) {
        // left wall
        server = false;
        Reset(server);
    }
    else if (
        //ball is inline or behind paddle
        bx < paddleSize.x &&
        //AND ball is below top edge of paddle
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {
        // bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(10, 0);
    }
    else if (
        bx > (gameWidth - 10) - paddleSize.x &&
        //AND ball is below top edge of paddle
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
        // bounce off right paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(-10, 0);
    }
}

void Render(RenderWindow& window) {
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text);
}

int main(){
  RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML works!");
  Load();
  while (window.isOpen()){
    window.clear();
    Update(window);
    Render(window);
    window.display();
  }
  return 0;
}
