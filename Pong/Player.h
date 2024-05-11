#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
class Player
{
private:
	sf::Vector2f rect_size;
	sf::Vector2f rect_position;
	sf::Color rect_color;
	sf::Keyboard::Key keyUp;
	sf::Keyboard::Key keyDown;
	sf::Uint8 points;
	float speed;
	sf::RectangleShape player;
	Ball* ball = nullptr;
	std::string tag;
	bool canCollide;
public:
	Player(float width, float height, float x, float y, float speed, sf::Color color, sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown, Ball* ball, std::string playerTag):
	rect_size(width, height), rect_position(x,y), rect_color(color)
	{
		this->keyUp = keyUp;
		this->keyDown = keyDown;
		this->speed = speed;
		points = 0;
		player.setFillColor(color);
		player.setSize(rect_size);
		player.setPosition(rect_position);
		this->ball = ball;
		tag = playerTag;
		canCollide = true;
	}
	std::string getTag() {
		return tag;
	}
	void draw(sf::RenderWindow& window) {
		window.draw(player);
	}
	void move(sf::Time deltaTime, sf::RenderWindow& window) {
		
		if (sf::Keyboard::isKeyPressed(keyUp) && rect_position.y >= 0 ) {
			rect_position.y -= speed * deltaTime.asSeconds();
			player.setPosition(rect_position);
		}
		if (sf::Keyboard::isKeyPressed(keyDown) && rect_position.y + rect_size.y <= window.getSize().y) {
			rect_position.y += speed * deltaTime.asSeconds();
			player.setPosition(rect_position);
		}
	}
	
	void isColliding(sf::Vector2f ballPos, float radius, Player& playerOne, Player& playerTwo) {
		//I think it works - update: it doesn't at least the left paddle
		//right paddle collision
		if (tag == "P2") {
			if (ballPos.x + radius >= rect_position.x && ballPos.y + radius >= rect_position.y && ballPos.y - radius <= rect_position.y + rect_size.y) {
					ball->hitBall(rect_size.y, rect_position.y,tag);
					std::cout << "Collision right\n";
						
			}
		}
		//left paddle collision
		if (tag == "P1") {
			if (ballPos.x <= rect_position.x + rect_size.x && ballPos.y >= rect_position.y && ballPos.y - radius <= rect_position.y + rect_size.y) {
				
					ball->hitBall(rect_size.y, rect_position.y,tag);
					std::cout << "Collision left\n";
					
			}
		}
	}
};

