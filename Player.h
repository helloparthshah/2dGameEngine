#pragma once
#include <SFML/Graphics.hpp>

// #include "Engine.h"

using namespace sf;

class Player {
  // All the private variables can only be accessed internally
 private:
  // Where is Player
  Vector2f m_Position;
  Vector2u size;

  // Of course we will need a sprite
  Sprite m_Sprite;

  // And a texture
  // Player has been working out and he is now a bit more muscular than before
  // Furthermore, he fancies himself in lumberjack attire
  Texture m_Texture;

  // Which direction(s) is the player currently moving in
  bool m_LeftPressed;
  bool m_RightPressed;
  bool m_UpPressed;
  bool m_DownPressed;
  bool m_JumpPressed;

  // Player's speed in pixels per second
  float m_Speed;
  Vector2f velocity;
  Vector2f MaxV = Vector2f(1250, 1250);

  // Public functions
 public:
  // We will set Player up in the constructor
  Player();

  void setSize(Vector2u s) { size = s; }

  // Send a copy of the sprite to main
  Sprite getSprite();

  // Move Player in a specific direction
  void moveLeft();

  void moveRight();

  void moveUp();

  void moveDown();

  void Jump();

  void moveXY(Vector2f Force, float time) {
    Vector2f gravity(0, 2000);
    velocity += (Force + gravity) * time;
    m_Position += velocity * time;

    if (velocity.x > MaxV.x) velocity.x = MaxV.x;
    if (velocity.y > MaxV.y) velocity.y = MaxV.y;
  }

  // Stop Player moving in a specific direction
  void stopLeft();

  void stopRight();

  void stopUp();

  void stopDown();

  void stopJump();

  // We will call this function once every frame
  void update(float elapsedTime);
};

Player::Player() {
  // How fast does Player move?
  m_Speed = 800;

  // Associate a texture with the sprite
  m_Texture.loadFromFile("player.png");
  m_Sprite.setTexture(m_Texture);
  m_Sprite.setOrigin({m_Sprite.getLocalBounds().width / 2, 0});

  // Set the Player's starting position
  m_Position.x = 500;
  m_Position.y = 500;
}

// Make the private spite available to the draw() function
Sprite Player::getSprite() { return m_Sprite; }

void Player::moveLeft() { m_LeftPressed = true; }

void Player::moveRight() { m_RightPressed = true; }

void Player::moveUp() { m_UpPressed = true; }

void Player::moveDown() { m_DownPressed = true; }

void Player::Jump() { m_JumpPressed = true; }

void Player::stopJump() { m_JumpPressed = false; }

void Player::stopLeft() { m_LeftPressed = false; }

void Player::stopRight() { m_RightPressed = false; }

void Player::stopUp() { m_UpPressed = false; }

void Player::stopDown() { m_DownPressed = false; }

// Move Player based on the input this frame,
// the time elapsed, and the speed
void Player::update(float elapsedTime) {
  moveXY(Vector2f(0, 0), elapsedTime);

  if (m_JumpPressed) {
    m_Sprite.scale(-1, 1);
    // moveXY(Vector2f(0, -9.8 * 500), elapsedTime);
  }

  if (m_RightPressed) {
    m_Position.x += m_Speed * elapsedTime;
  }

  if (m_LeftPressed) {
    m_Position.x -= m_Speed * elapsedTime;
  }

  if (m_UpPressed && m_Position.y >= size.y - m_Texture.getSize().y) {
    velocity.y *= -1;
    // m_Position.y -= m_Speed * elapsedTime;
  }

  if (m_DownPressed) {
    m_Position.y += m_Speed * elapsedTime;
  }

  if (m_Position.x <= m_Texture.getSize().x / 2)
    m_Position.x = m_Texture.getSize().x / 2;

  if (m_Position.x + m_Texture.getSize().x / 2 >= size.x)
    m_Position.x = size.x - m_Texture.getSize().x / 2;

  if (m_Position.y <= 0) m_Position.y = 0;

  if (m_Position.y + m_Texture.getSize().y >= size.y)
    m_Position.y = size.y - m_Texture.getSize().y;

  // Now move the sprite to its new position
  m_Sprite.setPosition(m_Position);
}