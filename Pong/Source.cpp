#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define PLAYER_WIDTH 15
#define PLAYER_HEIGHT 70
#define PLAYER_SPEED 500
#define BALL_RADIUS 10
#define BALL_SPEED 600
#define MAX_BOUNCE_ANGLE 75
#define WALL_WIDTH 10
#define WALL_HEIGHT 10
bool isGameStarted = false;
bool isRoundStarted = false;
int main() {
	isGameStarted = false;
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
	window.setVerticalSyncEnabled(true);
	
	sf::Clock timer;
	Ball ball(BALL_RADIUS, BALL_SPEED, MAX_BOUNCE_ANGLE, window);
	std::vector<Player> players = { 
		Player(PLAYER_WIDTH, PLAYER_HEIGHT, 0+20, WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2, PLAYER_SPEED, sf::Color::White, sf::Keyboard::W, sf::Keyboard::S, &ball, "P1"),
		Player(PLAYER_WIDTH, PLAYER_HEIGHT, WINDOW_WIDTH - PLAYER_WIDTH - 20,  WINDOW_HEIGHT / 2 - PLAYER_HEIGHT/2, PLAYER_SPEED, sf::Color::White, sf::Keyboard::Up, sf::Keyboard::Down, &ball, "P2")
	};
	std::vector<Wall> walls = {
		Wall(0, -WALL_HEIGHT -2.f, WINDOW_WIDTH, WALL_HEIGHT, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, isRoundStarted, "Top"),
		Wall(0,	WINDOW_HEIGHT, WINDOW_WIDTH, WALL_HEIGHT, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, isRoundStarted, "Bottom"),
		Wall(-WALL_WIDTH , 0, WALL_WIDTH, WINDOW_HEIGHT, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, isRoundStarted, "Left"),
		Wall(WINDOW_WIDTH, 0, WALL_WIDTH, WINDOW_HEIGHT, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, isRoundStarted, "Right")
	};

	std::cout << players[0].getTag();
	std::cout << players[1].getTag();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (!isRoundStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					ball.kickBall();
					//isGameStarted = true;
					isRoundStarted = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					std::cout << "RS: " << isRoundStarted << "\n";
					std::cout << "GS: " << isGameStarted << "\n";
				}
			}
		}
		sf::Time deltaTime = timer.restart();
		window.clear(sf::Color::Black);
		for (auto& player : players) {
			player.move(deltaTime, window);
			player.draw(window);
			player.isColliding(ball.getPosition(), BALL_RADIUS, players[0], players[1]);
		}
		for (auto& wall : walls) {
			wall.draw(window);
			wall.checkCollision(ball.getPosition(), BALL_RADIUS);
		}
		ball.move(deltaTime);
		ball.draw(window);

		window.display();
	}

	return EXIT_SUCCESS;
}