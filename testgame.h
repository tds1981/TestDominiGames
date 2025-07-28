#ifndef _TESTGAME_H
#define _TESTSGAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <deque>
#include "board.h"
#include "figure.h"

const struct {int x=5; int y=5; int S=3;} White;        // координаты зоны белых
const struct {int x=0; int y=0; int S=3;} Black; // координаты зоны черных

typedef  struct {int x1; int y1; int x2; int y2; int step;} TypeWay;

class TestGame: public sf::Drawable
{
public:
	TestGame(sf::Color bordCol1, sf::Color bordCol2);
	Board board;
	std::array<Figure, 18> Figurs;
	int selectedF=0;
	void MoveFigure(int fig, int x, int y);
	bool checkGoPlayer(int x, int y);
	void PCgo(int d);
	void PCgo111(int d);
	bool check(int fig, int x, int y);
	std::vector<TypeWay> Trace(int x1, int y1, int x2, int y2);
	void markerTrace(std::vector<TypeWay> trace);
private:
	std::vector<TypeWay> treks[9];
	sf::Font font;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void FixBlackFigures();
	void FixWhiteFigures(int fig);
	std::vector<TypeWay> NewTrace(int fig);
	int CalculateNewWays();
};

#endif