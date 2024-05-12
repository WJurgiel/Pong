#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "GameManager.h"
#include "Text.h"

bool isGameStarted = false;
bool isRoundStarted = false;
sf::Font* font = new sf::Font;

void pollEvents(sf::RenderWindow& window, Ball& ball, GameManager& gm) {
	sf::Event ev;
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) window.close();
		if (ev.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (!gm.getIsMenuOnScreen() && !gm.getIsRoundStarted() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if(!gm.getHasPlayerWon()[0] && !gm.getHasPlayerWon()[1])
					ball.kickBall();
				gm.setIsRoundStarted(true);
			}
			if (!gm.getIsMenuOnScreen() && (gm.getHasPlayerWon()[0] || gm.getHasPlayerWon()[1]) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				std::cout << "Restarted\n";
				gm.restartGame();
			}
			if (gm.getIsMenuOnScreen() && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				gm.setIsMenuOnScreen(false);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				std::cout << "round started: " << gm.getRoundStarted() << "\n";
				std::cout << "P1 win: " << gm.getHasPlayerWon()[0] << "\n";
				std::cout << "P2 win: " << gm.getHasPlayerWon()[1] << "\n";
			}
		}
	}
}
int main() {
	
	/*
		Render window
	*/
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
	window.setVerticalSyncEnabled(true);
	
	/*
		Fonts
	*/
	if (!font->loadFromFile("8bit.ttf")) {
		std::cout << "can't read file";
		return EXIT_FAILURE;
	}
	sf::Text debugText("Debug", *font, 40);
	/*
		Classes 
	*/
	sf::Clock timer;
	std::vector<Text> playerScores = {
		Text(font, "0", sf::Vector2f{WINDOW_WIDTH / 4, 50}, 60, sf::Color::White),
		Text(font, "0", sf::Vector2f{3 * WINDOW_WIDTH / 4, 50}, 60, sf::Color::White)
	};
	std::vector<Text> otherText = {
		Text(font, "Player wins", sf::Vector2f(WINDOW_WIDTH / 3.5, WINDOW_HEIGHT / 2 - 25), 50, sf::Color::Yellow),
		Text(font, "PONG", sf::Vector2f(WINDOW_WIDTH / 5, 0 - WINDOW_HEIGHT/5), 230, sf::Color::Green),
		Text(font, "Press [Enter] to start", sf::Vector2f(WINDOW_WIDTH/3.5, WINDOW_HEIGHT/4), 30, sf::Color::White)
	};
	GameManager GM(&window, &playerScores[0], &playerScores[1], &otherText[0]);

	Ball ball(BALL_RADIUS, BALL_SPEED, MAX_BOUNCE_ANGLE, window, &GM);
	std::vector<Player> players = { 
		Player(PLAYER_WIDTH, PLAYER_HEIGHT, 0+20, WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2, PLAYER_SPEED, sf::Color::White, sf::Keyboard::W, sf::Keyboard::S, &ball, "P1"),
		Player(PLAYER_WIDTH, PLAYER_HEIGHT, WINDOW_WIDTH - PLAYER_WIDTH - 20,  WINDOW_HEIGHT / 2 - PLAYER_HEIGHT/2, PLAYER_SPEED, sf::Color::White, sf::Keyboard::Up, sf::Keyboard::Down, &ball, "P2")
	};
	std::vector<Wall> walls = {
		Wall(0, -WALL_HEIGHT -2.f, WINDOW_WIDTH, WALL_HEIGHT,&GM, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, "Top"),
		Wall(0,	WINDOW_HEIGHT, WINDOW_WIDTH, WALL_HEIGHT,&GM, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, "Bottom"),
		Wall(-WALL_WIDTH , 0, WALL_WIDTH, WINDOW_HEIGHT,&GM, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, "Left"),
		Wall(WINDOW_WIDTH, 0, WALL_WIDTH, WINDOW_HEIGHT,&GM, &ball,sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}, "Right")
	};

	/*DEBUG*/
	std::cout << players[0].getTag();
	std::cout << players[1].getTag();
	std::cout << "p1 address from main: " << playerScores[0].DB_getText() << "\n";
	std::cout << "p2 address from main: " << playerScores[1].DB_getText() << "\n";


	GM.setIsGameStarted(false);
	GM.setIsMenuOnScreen(true);
	while (window.isOpen()) {
		pollEvents(window, ball, GM);

		sf::Time deltaTime = timer.restart();
		window.clear(sf::Color::Black);
		if (GM.getIsMenuOnScreen()) {
			otherText[1].draw(window);
			otherText[2].draw(window);
		}
		else {
			/*Drawing*/
			for (auto& player : players) {
				player.move(deltaTime, window);
				player.draw(window);
				player.isColliding(ball.getPosition(), BALL_RADIUS, players[0], players[1]);
			}
			for (auto& wall : walls) {
				wall.draw(window);
				wall.checkCollision(ball.getPosition(), BALL_RADIUS);
			}
			for (auto& scoreText : playerScores) {
				scoreText.draw(window);
			}
			if (!GM.getHasPlayerWon()[0] && !GM.getHasPlayerWon()[1]) {
				ball.move(deltaTime);
				ball.draw(window);
			}
			if (GM.getHasPlayerWon()[0] || GM.getHasPlayerWon()[1]) {
				otherText[0].draw(window);
			}
		}
		
		

		window.display();
	}
	delete font;
	return EXIT_SUCCESS;
}