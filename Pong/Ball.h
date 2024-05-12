#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
class Ball
{
private:
	float radius;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	float maxBounceAngle;
	sf::CircleShape ball;
	GameManager* gm;
public:
	Ball(float radius, float speed, float maxBounceAngle, sf::RenderWindow& window, GameManager* gm)
	{
		this->radius = radius;
		this->speed = speed;
		this->maxBounceAngle = maxBounceAngle;
		position = sf::Vector2f(window.getSize().x/2- radius, window.getSize().y/2-radius);
		velocity = sf::Vector2f(0.f, 0.f);
		ball.setPosition(position);
		ball.setFillColor(sf::Color::White);
		ball.setRadius(radius);
		ball.setOrigin(0, 0);

		this->gm = gm;
	}
	sf::Vector2f getPosition() {
		return position;
	}
	sf::Vector2f getVelocity() {
		return velocity;
	}
	void kickBall() {
		velocity = sf::Vector2f(speed, 0);
	}
	void restartBall(sf::Vector2f window_size) {
		position = sf::Vector2f(window_size.x / 2 - radius, window_size.y / 2 - radius);
		velocity = sf::Vector2f(0.f, 0.f);
		gm->setIsRoundStarted(false);
	}
	void hitBall(float paddleHeight, float paddleY, std::string tag) {
		float relativeY = (paddleY + paddleHeight / 2) - this->position.y;
		float normalized = (relativeY / (paddleHeight / 2));
		float bounceAngle = normalized * maxBounceAngle * 3.14f/180.f;

		float factor = 1;
		if (tag == "P1") factor = 1;
		else if (tag == "P2") factor = -1;
		velocity = sf::Vector2f(factor * speed * cos(bounceAngle), -speed*sin(bounceAngle));
	}
	void bounceOfTheWall() {
		velocity = sf::Vector2f(velocity.x, -velocity.y);
	}
	void DBbounceOfTheWall() {
		velocity = sf::Vector2f(-velocity.x, velocity.y);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(ball);
	}
	void move(sf::Time deltaTime) {
		position.x += velocity.x * deltaTime.asSeconds();
		position.y += velocity.y * deltaTime.asSeconds();
		ball.setPosition(position);
	}
};

