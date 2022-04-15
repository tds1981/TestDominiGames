#ifndef _FIGURE_H
#define _FIGURE_H

#include <iostream>
#include <SFML/Graphics.hpp>
//#include <string>
#include <vector>
#include "board.h"


class Figure : public sf::Drawable{
public:
	Figure(){}
	void setPosition(int x, int y);
	void setTypeFigure(bool typeF);
	void setTexture();
	
	bool player; // true == White , false == Black
	int N;
	struct {int x; int y;} pos; // местонахождение фигуры
	//struct {int x; int y;} target_pos;
	int CountSteps=0;
	bool Stop=false;

private:
	sf::Texture TextureF;
	sf::Texture TextureStop;
    sf::Sprite spriteF;
	
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {   target.draw(spriteF);  }
};

#endif