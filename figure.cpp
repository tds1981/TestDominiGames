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

