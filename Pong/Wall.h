#pragma once
#include <SFML/Graphics.hpp>
#include"Ball.h"
#include "GameManager.h"
class Wall{
private:
	sf::Vector2f position;
	sf::Vector2f size;
	std::string tag;
	sf::RectangleShape rect; 
	Ball* ball = nullptr;
	sf::Vector2f window_size;
	bool* isRoundStarted;
	GameManager* gm;
public:
	Wall(float xPos, float yPos, float width, float height, GameManager* gm, Ball* ball,sf::Vector2f window_sizes, std::string wallTag){
		position = sf::Vector2f(xPos, yPos);
		size = sf::Vector2f(width, height);
		this->ball = ball;
		tag = wallTag;
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Cyan);
		window_size = window_sizes;
		//this->isRoundStarted = &isRoundStarted;
		this->gm = gm;
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
				gm->addPoint("P2");
				ball->restartBall(window_size);
			}
		}
		if (tag == "Right") {
			if (ball->getPosition().x + radius >= position.x) {
				gm->addPoint("P1");
				ball->restartBall(window_size);
				
			}
		}
	}
};