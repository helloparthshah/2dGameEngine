/* #include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
} */
#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {
  // Declare an instance of Engine
  Engine engine;

  // Start the engine
  engine.start();

  // Quit in the usual way when the engine is stopped
  return 0;
}