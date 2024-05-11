#pragma once
#include <SFML/Graphics.hpp>
/*
	
*/
class GameManager {
private:
	int p1_points = 0;
	int p2_points = 0;
	bool gameStarted;
	bool roundStarted;
public:
	GameManager() {
		p1_points = 0;
		p2_points = 0;
		gameStarted = false;
		roundStarted = false;
	}
	int getP1Points() {
		return p1_points;
	}
	int getP2Points() {
		return p2_points;
	}
	void addPoint(std::string tag) {
		if (tag == "P1") p1_points++;
		if (tag == "P2") p2_points;
	}
};