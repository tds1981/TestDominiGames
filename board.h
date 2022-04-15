
#ifndef _BOARD_H
#define _BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <array>

using namespace std;
using namespace sf;

//основные параметры доски
const float SizeRect = 80.f;
const float Board_x0 = 50.f;
const float Board_y0 = 50.f;

class Board : public sf::Drawable{

public:

    Board(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);
	std::array<std::array<int, 8>, 8> state;
	   
    void load(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);
	int  selected(int x, int y, sf::Color Col);
	void marker(int x, int y, sf::Color Col);
	void drawBoard(sf::Color col1, sf::Color col2);
	void clearSelected();
    std::array<sf::RectangleShape, 64> m_boardSquares;
private:

	sf::RectangleShape selectRect;
	sf::Font font;
	std::array<sf::Text, 16> simvols;

	sf::RectangleShape rect;
    
    // Draw class on SFML Window
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif