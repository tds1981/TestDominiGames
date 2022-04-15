#include "board.h"


Board::Board(sf::Color col1, sf::Color col2){
	font.loadFromFile("Textures/arial.ttf");
    load(col1,col2);
}

void Board::load(sf::Color col1, sf::Color col2){
    for(int i=0; i<8;i++)
        for(int j=0; j<8;j++)
            state[j][i]=255;

	drawBoard(col1, col2);
	char ch1='a';
	char ch2='8';
	for(int i=0; i<16;i++) 
	{	
		simvols[i].setFont(font);
		simvols[i].setCharacterSize(30);
		if (i<8) {simvols[i].setPosition(Board_x0+SizeRect/2+i*SizeRect, 10); simvols[i].setString(ch1++); }
		else {simvols[i].setPosition(10, SizeRect + (i-8)*SizeRect);	simvols[i].setString(ch2--); }		
		simvols[i].setFillColor(sf::Color::Red); 
		simvols[i].setStyle(sf::Text::Bold);
	}
	rect.setPosition(Board_x0, Board_y0);
	rect.setSize(Vector2f(SizeRect*8, SizeRect*8));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(3);
}
void Board::drawBoard(sf::Color col1, sf::Color col2)
{
	for(int i=0; i<8;i++){
        bool tmpColor = ((i % 2)==0)?true:false;
        for(int j=0; j<8;j++){
            m_boardSquares[j + (i * 8)].setPosition(sf::Vector2f( j*SizeRect+Board_x0 , i*SizeRect+Board_y0));
            m_boardSquares[j + (i * 8)].setSize(sf::Vector2f(SizeRect, SizeRect));
            m_boardSquares[j + (i * 8)].setFillColor(tmpColor ? col1 : col2);
            tmpColor = !tmpColor;
        }
    }
}

void Board::clearSelected()
{
	for(int i=0; i<8;i++)
		for(int j=0; j<8;j++) 
			if (state[i][j] < 0)  state[i][j] *= -1; 
	selectRect.setOutlineThickness(0);
}

int Board::selected(int x, int y, sf::Color Col)
{
	if (state[x][y]>=9)
	{	
		clearSelected();
		state[x][y] *= -1;
		marker(x, y, Col);
	}
	return 0;
}

void Board::marker(int x, int y, sf::Color Col)
{
	selectRect.setPosition(sf::Vector2f( x*SizeRect+Board_x0 , y*SizeRect+Board_y0));
    selectRect.setSize(sf::Vector2f(SizeRect, SizeRect));
    selectRect.setFillColor(sf::Color::Transparent);
	selectRect.setOutlineColor(Col);
	selectRect.setOutlineThickness(5);

}


// Draw class on SFML Window
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(rect);
    for(int i=0;i<64;i++){
        target.draw(m_boardSquares[i]);
    }
	for(int i=0; i<16;i++) target.draw(simvols[i]);
	target.draw(selectRect);
}