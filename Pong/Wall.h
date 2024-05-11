#pragma once
#include <SFML/Graphics.hpp>
#include"Ball.h"

class Wall{
private:
	sf::Vector2f position;
	sf::Vector2f size;
	std::string tag;
	sf::RectangleShape rect; 
	Ball* ball = nullptr;
	sf::Vector2f window_size;
	bool* isRoundStarted;
public:
	Wall(float xPos, float yPos, float width, float height, Ball* ball,sf::Vector2f window_sizes, bool& isRoundStarted, std::string wallTag){
		position = sf::Vector2f(xPos, yPos);
		size = sf::Vector2f(width, height);
		this->ball = ball;
		tag = wallTag;
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Cyan);
		window_size = window_sizes;
		this->isRoundStarted = &isRoundStarted;
	}
	void draw(sf::RenderWindow& window) {
		window.draw(rect);
	}
	void checkCollision(sf::Vector2f ballPos, float radius) {
		if (tag == "Top") {
			if (ball->getPosition().y <= position.y + size.y) ball->bounceOfTheWall();
		}
		if (tag == "Bottom") {
			if (ball->getPosition().y + radius >= position.y) ball->bounceOfTheWall();
		}
		if (tag == "Left") {
			if(ball->getPosition().x  - radius <= position.x + size.x) {
				ball->restartBall(window_size, *isRoundStarted);
				//point for P2
			}
		}
		if (tag == "Right") {
			if (ball->getPosition().x + radius >= position.x) {
				ball->restartBall(window_size, *isRoundStarted);
				
			}
		}
	}
};