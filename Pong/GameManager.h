#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"
#include<sstream>
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
#define MAX_POINTS 3
/*Handles scene changing, counting and displaying points, and game states*/
class GameManager {
private:
	int p1_points, p2_points,
	const max_points = MAX_POINTS;
	Text* p1_points_text = nullptr;
	Text* p2_points_text = nullptr;
	Text* player_win_text = nullptr;
	bool isGameStarted, isRoundStarted, isMenuOnScreen;
	std::vector<bool> hasPlayerWon = {false, false};
	sf::RenderWindow* window;
	
	void checkIfWin() {
		if (p1_points >= max_points) {
			hasPlayerWon[0] = true;
			player_win_text->updateText("!Player 1 wins!");
		}
		if (p2_points >= max_points){
			hasPlayerWon[1] = true;
			player_win_text->updateText("!Player 2 wins!");
		}
	}
public:
	bool getIsGameStarted() { return isGameStarted; }
	void setIsGameStarted(bool val) { isGameStarted = val; }

	bool getIsRoundStarted() { return isRoundStarted; }
	void setIsRoundStarted(bool val) { isRoundStarted = val; }

	bool getIsMenuOnScreen() { return isMenuOnScreen; }
	void setIsMenuOnScreen(bool val) { isMenuOnScreen = val; }
	
	std::vector<bool> getHasPlayerWon() { return hasPlayerWon; }
	
	GameManager(sf::RenderWindow* window, Text* p1, Text* p2, Text* pWins) {
		this->window = window;
		if (!p1_points_text) p1_points_text = p1;
		if (!p2_points_text) p2_points_text = p2;
		if (!player_win_text) player_win_text = pWins;

		restartGame();
		isMenuOnScreen = false; // not for now S
		std::cout << "p1 addres from GM: " << p1_points_text->DB_getText() << "\n";
		std::cout << "p2 addres from GM: " << p2_points_text->DB_getText() << "\n";
	}
	void restartGame() {
		//values and parameters
		p1_points = 0;
		p2_points = 0;
		hasPlayerWon[0] = false;
		hasPlayerWon[1] = false;
		setGameStarted(false);
		setRoundStarted(false);

		//text segment
		std::stringstream points_ss;
		points_ss << p1_points;
		p1_points_text->updateText(points_ss.str());
		points_ss.str("");
		points_ss << p2_points;
		p2_points_text->updateText(points_ss.str());
	}
	void setGameStarted(bool isStarted) {
		isGameStarted = isStarted;
	} 
	bool getGameStarted() {
		return isGameStarted;
	}
	void setRoundStarted(bool isStarted) {
		isRoundStarted = isStarted;
	}
	bool getRoundStarted() {
		return isRoundStarted;
	}
	int getPlayerPoints(std::string tag) {
		if(tag == "P1") return p1_points;
		if (tag == "P2") return p2_points;
		return 0;
	}
	
	void addPoint(std::string tag) {
		//update value and update text on screen;
		if (tag == "P1") {
			std::stringstream ss;
			ss << ++p1_points;
			std::cout << "addPoint P1: " << ss.str();
			p1_points_text->updateText(ss.str());
		}
		if (tag == "P2") {
			std::stringstream ss;
			ss << ++p2_points;
			std::cout << "addPoint P2: " << ss.str();
			p2_points_text->updateText(ss.str());
		}
		checkIfWin();
	}
};