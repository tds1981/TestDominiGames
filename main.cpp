#include <iostream>
#include <SFML/Graphics.hpp>
#include "testgame.h"

using namespace std;
using namespace sf;

const float SiseXWindow=750;
const float SiseYWindow=750;

int main() 
{
	TestGame Game(sf::Color::White, sf::Color::Blue);
	
    sf::RenderWindow window(sf::VideoMode(SiseXWindow,SiseYWindow), "TestGame", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
	window.clear(sf::Color::White);
	
	float EndXBoard = Board_x0+SizeRect*8;
	float EndYBoard = Board_y0+SizeRect*8;
	
	int tr_x = -1;
	int tr_y = -1;
	while (window.isOpen()) 
	{
		sf::Event event;
        while(window.pollEvent(event))
		{
            if(event.type == sf::Event::Closed) window.close();
			
			if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if((Board_x0 <= event.mouseButton.x) && (event.mouseButton.x <= EndXBoard) && (Board_y0 <= event.mouseButton.y) && (event.mouseButton.y <= EndYBoard))
					{
						tr_x = -1;tr_y = -1;
						int x = (event.mouseButton.x-Board_x0)/SizeRect;
						int y = (event.mouseButton.y-Board_y0)/SizeRect;
						std::cout << "X=" << x<< " Y="<< y <<" State="<< abs(Game.board.state[x][y]) << std::endl; 
						if (Game.checkGoPlayer(x, y)) 
						{	
							Game.MoveFigure(Game.selectedF, x, y);
							Game.PCgo(1);
						}	
						
                    }
                }
				if(event.mouseButton.button == sf::Mouse::Right) 
				{
					if (tr_x ==-1)
					{	
						Game.board.clearSelected();
						Game.board.drawBoard(sf::Color::White, sf::Color::Blue);
						tr_x = (event.mouseButton.x-Board_x0)/SizeRect;
						tr_y = (event.mouseButton.y-Board_y0)/SizeRect;
						Game.board.marker(tr_x, tr_y, sf::Color::Magenta);
					}
					else 
					{
						int x = (event.mouseButton.x-Board_x0)/SizeRect;
						int y = (event.mouseButton.y-Board_y0)/SizeRect;
						std::vector<TypeWay> buf = Game.Trace(tr_x, tr_y, x,  y);
						//Game.board.markerTrace(buf);
						tr_x = -1;
						tr_y = -1;
						Game.board.drawBoard(sf::Color::White, sf::Color::Blue);
						Game.markerTrace(buf);
					}
					//Game.board.clearSelected();
				}
            }
		}
		
		window.draw(Game);
		window.display();
	}
	return 0;
}