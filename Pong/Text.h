#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Text {
private:
	sf::Vector2f position;
	sf::Color color;
	sf::Uint8 fontSize; // in pixels!; 
	std::string message;
	sf::Text textInstance;
	sf::Font* font = nullptr;
public:
	Text(sf::Font* font, std::string message, sf::Vector2f pos, sf::Uint8 size, sf::Color color) {
		//if (!textInstance) textInstance = new sf::Text;
		this->message = message;
		this->color = color;	
		this->font = font;
		textInstance.setFont(*(this->font));
		textInstance.setString(message);
		textInstance.setPosition(pos);
		textInstance.setCharacterSize(size);
		textInstance.setFillColor(color);
	}
	sf::Text* DB_getText() {
		return &textInstance;
	}
	void updateText(const std::string& newText) {
		textInstance.setString(newText);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(textInstance);
	}

};