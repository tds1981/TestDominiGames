#include "figure.h"

void Figure::setTypeFigure(bool typeF)
{
	player = typeF;
	if (typeF) TextureF.loadFromFile("Textures/w_pawn.png"); else TextureF.loadFromFile("Textures/b_pawn.png");
	spriteF.setTexture(TextureF);
    spriteF.setScale(sf::Vector2f(0.5f,0.5f));
}

void Figure::setPosition(int x, int y)
{
	pos.x = x; 
	pos.y = y; 
	spriteF.setPosition(sf::Vector2f(Board_x0 + x*SizeRect + SizeRect/8, Board_y0 + y * SizeRect + SizeRect/8));
		
}
void Figure::setTexture()
{
	if (player) TextureStop.loadFromFile("Textures/w_bishop.png"); else TextureStop.loadFromFile("Textures/b_bishop.png");
	if  (Stop) { spriteF.setTexture(TextureStop); spriteF.setScale(sf::Vector2f(0.5f,0.5f));}
}
/*
void Figure::FixFigures()
{
		int x = Figurs[fig].pos.x;
		int y = Figurs[fig].pos.y;
	
		if ((x>=5)&&(y>=5)&&(!player))
		{
			if (x*y == 49) Figurs[fig].Stop = true;
			if (((x*y == 42)||((x*y == 36)))&&(abs(board.state[7][7]) < 9)) Figurs[fig].Stop = true;
			if ((abs(board.state[6][6]) < 9)&&(abs(board.state[7][6]) < 9)&&(abs(board.state[6][7]) < 9)&&(abs(board.state[7][7]) < 9)) 
				Figurs[fig].Stop = true;
		}
		setTexture();
	}
}*/

