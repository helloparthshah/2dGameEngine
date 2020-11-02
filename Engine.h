#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

#include "Player.h"

using namespace sf;

class Engine {
 private:
  // A regular RenderWindow
  RenderWindow m_Window;

  // Declare a sprite and a Texture for the background
  Sprite m_BackgroundSprite;
  Texture m_BackgroundTexture;
  Font font;
  float fps;

  Player m_Player;

  // Private functions for internal use only
  void input();
  void update(float dt);
  void draw();
  void drawText(String s, float x, float y, float size, sf::Color c);

 public:
  // The Engine constructor
  Engine();

  // RenderWindow getRenderWindow() { return m_Window; }

  Vector2u getSize() { return m_Window.getSize(); }

  // start will call all the private functions
  void start();
};

Engine::Engine() {
  // Get the screen resolution and create an SFML window and View
  Vector2f resolution;
  resolution.x = VideoMode::getDesktopMode().width / 2;
  resolution.y = VideoMode::getDesktopMode().height / 2;

  m_Window.create(VideoMode(resolution.x, resolution.y), "Test");

  // Load the background into the texture
  // Be sure to scale this image to your screen size
  m_BackgroundTexture.loadFromFile("bg.jpg");

  auto TextureSize = m_BackgroundTexture.getSize();  // Get size of texture.
  auto WindowSize = m_Window.getSize();              // Get size of window.

  m_Player.setSize(WindowSize);

  float ScaleX = (float)WindowSize.x / TextureSize.x;
  float ScaleY = (float)WindowSize.y / TextureSize.y;  // Calculate scale.

  // Associate the sprite with the texture
  m_BackgroundSprite.setTexture(m_BackgroundTexture);

  m_BackgroundSprite.setScale(ScaleX, ScaleY);  // Set scale

  // Load the fonts
  if (!font.loadFromFile("arial.ttf")) {
    throw "Could not Access Fonts";
  }
}

void Engine::start() {
  // Timing
  Clock clock;

  // m_Window.setFramerateLimit(30);

  while (m_Window.isOpen()) {
    sf::Event event;

    while (m_Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_Window.close();
    }

    /* if (event.type == sf::Event::Resized) {
      // update the view to the new size of the window
      sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
      m_Window.setView(sf::View(visibleArea));
    } */
    // Restart the clock and save the elapsed time into dt
    float dt = clock.restart().asSeconds();

    // Make a fraction from the delta time
    input();
    update(dt);
    draw();
  }
}

void Engine::input() {
  // Handle the player quitting
  if (Keyboard::isKeyPressed(Keyboard::Escape)) {
    m_Window.close();
  }

  if (Keyboard::isKeyPressed(Keyboard::Space)) {
    m_Player.Jump();
    // std::cout << "Right" << std::endl;
  } else {
    m_Player.stopJump();
  }

  // Handle the player moving
  if (Keyboard::isKeyPressed(Keyboard::A)) {
    m_Player.moveLeft();
    // std::cout << "Left" << std::endl;
  } else {
    m_Player.stopLeft();
  }

  if (Keyboard::isKeyPressed(Keyboard::W)) {
    m_Player.moveUp();
    // std::cout << "Up" << std::endl;
  } else {
    m_Player.stopUp();
  }

  if (Keyboard::isKeyPressed(Keyboard::S)) {
    m_Player.moveDown();
    // std::cout << "Down" << std::endl;
  } else {
    m_Player.stopDown();
  }

  if (Keyboard::isKeyPressed(Keyboard::D)) {
    m_Player.moveRight();
    // std::cout << "Right" << std::endl;
  } else {
    m_Player.stopRight();
  }

  /* if (m_Player.getSprite().getPosition().x < 0)
    m_Player.getSprite().setPosition(0, m_Player.getSprite().getPosition().y);

  if (m_Player.getSprite().getPosition().x > m_Window.getSize().x)
    m_Player.getSprite().setPosition(m_Window.getSize().x,
                                     m_Player.getSprite().getPosition().y);

  if (m_Player.getSprite().getPosition().y < 0)
    m_Player.getSprite().setPosition(m_Player.getSprite().getPosition().x, 0);

  if (m_Player.getSprite().getPosition().y > m_Window.getSize().y)
    m_Player.getSprite().setPosition(m_Player.getSprite().getPosition().x,
                                     m_Window.getSize().x); */
}

void Engine::update(float dt) {
  m_Player.update(dt);
  fps = 1.f / (dt);
}

void Engine::drawText(String s, float x, float y, float size, sf::Color c) {
  sf::Text text(s, font);
  text.setFillColor(c);
  text.setCharacterSize(size);
  text.setPosition(x, y);
  m_Window.draw(text);
}

void Engine::draw() {
  // Rub out the last frame
  m_Window.clear(Color::Black);

  // Draw the background
  m_Window.draw(m_BackgroundSprite);
  m_Window.draw(m_Player.getSprite());

  // Drawing the text
  drawText("FrameRate: " + std::to_string((int)std::ceil(fps)), 20, 20, 40,
           sf::Color::Red);

  // Show everything we have just drawn
  m_Window.display();
}
