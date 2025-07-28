#include "testgame.h"

TestGame::TestGame(sf::Color bordCol1, sf::Color bordCol2)
: board(bordCol1,bordCol2)
{
    font.loadFromFile("Textures/arial.ttf");
    
	for (int i=0; i<9 ; i++)
	{
		Figurs[i].setTypeFigure(false); // Black
		Figurs[i].setPosition(i%3, i/3);
		board.state[i%3][i/3]=i;
		Figurs[i].N = i;
		
		Figurs[i+9].setTypeFigure(true); // white
		Figurs[i+9].setPosition(White.x + i%3, White.y + i/3);
		board.state[White.x + i%3][White.y + i/3]=i+9;
		Figurs[i+9].N = i+9;
		
	}
/*	
	for (int fig=8; fig>=0; fig--)
	{
		if (treks[fig].empty()) 
		{
			int x = Figurs[fig].pos.x;
			int y = Figurs[fig].pos.y;
			if(x==2) treks[fig] = Trace(x, y, 7-y, 4);
			if(y==2) treks[fig] = Trace(x, y, 4, 7-x);
		}
	}
	*/
}

void TestGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.clear(sf::Color::White);

    target.draw(board);
	for (int i=0; i<18 ; i++) target.draw(Figurs[i]);
}

void TestGame::PCgo(int d)
{
	static int fig=0;
	static int j =1;
	
	for (int i=0; i<19; i++)
	{
		if (Figurs[fig].Stop) continue;	
		if (j and check(fig, Figurs[fig].pos.x+1, Figurs[fig].pos.y)) 
			{MoveFigure(fig, Figurs[fig].pos.x+1, Figurs[fig].pos.y); if (++fig>=9) fig=0; return;} 
		else
		if (!j and check(fig, Figurs[fig].pos.x, Figurs[fig].pos.y+1)) 
			{MoveFigure(fig, Figurs[fig].pos.x, Figurs[fig].pos.y+1); if (++fig>=9) fig=0; return;}
		if (++fig>=9) fig=0;	
		j ^= 1;	
		std::cout << "j= "<< j << std::endl;
				
	}
	
 }

void TestGame::PCgo111(int d)
{
	int useful = -1; 
	
	static int strateg=1;
	int targertFunc[9]={0};
	
	int usefulX;
	int usefulY;
			
	int fig=0;
	//int steps=1000;
	
	int count=1000;
	int min=1000;
	//------------------------------strateg 1------------------------------------------------
	if (strateg==0)
	{	
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if ((board.state[i][j]>=0)&&(board.state[i][j]<9)) 
			{
				fig=board.state[i][j];
				if (Figurs[fig].Stop) continue;

				int NewX[2]={i, i+1};
				int NewY[2]={j+1, j};
				int D[2] = {(7-NewX[0])*(7-NewX[0])+(7-NewY[0])*(7-NewY[0]), (7-NewX[1])*(7-NewX[1])+(7-NewY[1])*(7-NewY[1])};
				for(int k=0; k<2; k++) 
					if (check(fig, NewX[k], NewY[k])&&(!Figurs[fig].Stop)&&(min>=D[k])&&(count >= Figurs[fig].CountSteps))
							{
								min = D[k];
								count = Figurs[fig].CountSteps;
								useful = fig;
								usefulX = NewX[k];
								usefulY = NewY[k];
							}
			}
	if (useful != -1)
	{	
		MoveFigure(useful, usefulX, usefulY); 
		std::cout << "Go figure strateg 1 fig= "<< useful << " x= "<< usefulX<<"  y="<< usefulY <<std::endl;
		return;
	}
	else strateg=1;
	}
	
	//-----------------------------strateg 2-----------------------------------------------
	else // выбор стратегии
	{	
	for (fig=8; fig>=0; fig--)
	{
		if (Figurs[fig].Stop) continue;	
		//if (fig == oldUseful) continue;
		
		if (!treks[fig].empty())
			if ((Figurs[fig].pos.x != treks[fig].back().x1)||(Figurs[fig].pos.y != treks[fig].back().y1)) treks[fig].clear();
		
		if (treks[fig].empty()) treks[fig] = NewTrace(fig);
		if (treks[fig].empty()) continue;	
		
		targertFunc[fig]=0;
		//if (check(fig, treks[fig].back().x2, treks[fig].back().y2))
		for (int i=8; i>=0; i--) 
		{
			if (i==fig) targertFunc[fig] += treks[fig].back().x2  *  treks[fig].back().y2 ;
			else targertFunc[fig] += Figurs[i].pos.x * Figurs[i].pos.y;
			//targertFunc[fig] += 9-fig;
			//if (Figurs[i].pos.x>=5 and Figurs[i].pos.y>=5) targertFunc[fig] /=10;
		} 
						
	}
	
	int mtf=0;
	for (fig=8; fig>=0; fig--) 
	{
		if ((targertFunc[fig] > mtf) and check(fig, treks[fig].back().x2, treks[fig].back().y2))
		{
			mtf = targertFunc[fig];
			useful = fig;				
		}

	}
	std::cout << "targertFunc= " << targertFunc[0] << " " << targertFunc[1] << " " << targertFunc[2] << " " << targertFunc[3]  << " " 
				<< targertFunc[4] << " " << targertFunc[5] << " " << targertFunc[6] << " "  << targertFunc[7] << " "  << targertFunc[8]  << std::endl;
	 std::cout << "useful= " << useful << std::endl;
	
	if (useful != -1) 
	{
		int x = treks[useful].back().x2; 
		int y = treks[useful].back().y2;
		treks[useful].pop_back();
		/*if (treks[useful].empty() && (!Figurs[fig].Stop)) 
		{
			treks[useful].clear();
			treks[useful] = NewTrace(useful);
		}*/
		
		MoveFigure(useful, x, y);
		std::cout << "Go figure strateg 2 fig= "<< useful << " x= "<< x<<"  y="<< y<<std::endl;
		return;
	}//else 	
		//if (CalculateNewWays() !=0 ) return PCgo(1);

	
	} // выбор стратегии															
	return;
	
}

int TestGame::CalculateNewWays()
{
	int count=0;
	for (int fig=8; fig>=0; fig--)
	{
		if (Figurs[fig].Stop) continue;	
		treks[fig].clear();
		treks[fig] = NewTrace(fig); 
		if (!treks[fig].empty()) { std::cout << "New track for "<< fig <<std::endl; count++; }
	}
	return count;
}

std::vector<TypeWay> TestGame::NewTrace(int fig)
{
	
	int x = Figurs[fig].pos.x;
	int y = Figurs[fig].pos.y;

	std::vector<TypeWay> res[9];
	int k=0;
	int min=1000;
	int min_k=0;
	
	for (k=0; k<9; k++)
	{
		if (abs(board.state[7-k%3][7-k/3])==255) 
		{
			res[k] = Trace(x, y, 7 - k%3,  7 - k/3);
			std::cout << "NewTrace for " << fig << " targetX= "<<7 - k%3<<" targetY= "<<7 - k/3<<std::endl;
			std::cout << res[k].size() << std::endl;
				
		}
	}
	
	for (k=0; k<9; k++)
		if (!res[k].empty())
			if (min >= res[k].front().step)
		{
			min = res[k].front().step;
			min_k = k;
		}
	return res[min_k];

}

//-----------------------------------------------------------------------------------------------------	
bool TestGame::check(int fig, int x, int y) // проверка возможности хода фигурой fig в позицию (x,y)
{
	if ((x<0)||(y<0)||(x>=8)||(y>=8)) return false;
	int dx = abs(Figurs[fig].pos.x - x);
	int dy = abs(Figurs[fig].pos.y - y);
	if  (abs(board.state[x][y])==255) 
			if (((dx==1) && (dy==0))||((dx==0) && (dy==1)) ) 
			{
				if (fig >= 9) return true;
				int f = Figurs[fig].N;
				if (dy==1)
				{
					if ((f==0 or f==1 or f==2)and(y<=5)) return true;
					if ((f==3 or f==4 or f==5)and(y<=6)) return true;
					if ((f==6 or f==7 or f==8)and(y<=7)) return true;
				}
				
				if (dx==1)
				{
					if ((f==0 or f==3 or f==6)and(x<=5)) return true;
					if ((f==1 or f==4 or f==7)and(x<=6)) return true;
					if ((f==2 or f==5 or f==8)and(x<=7)) return true;
				}
			}
	return false;
}

void TestGame::MoveFigure(int fig, int x, int y) // перемещение фигуры в позицию (x,y)
{	
	board.state[x][y] = Figurs[fig].N; 
	board.state[Figurs[fig].pos.x][Figurs[fig].pos.y] = 255; //пустая ячейка

	Figurs[fig].setPosition(x, y); 
	Figurs[fig].CountSteps++;
	
	//FixBlackFigures();
	//FixWhiteFigures(fig);
	
}
/*
void TestGame::FixBlackFigures()
{
	for (int fig=0; fig<9 ; fig++)
	{
		int x = Figurs[fig].pos.x;
		int y = Figurs[fig].pos.y;
	
		if ((x>=5)&&(y>=5)&&(!Figurs[fig].player))
		{
			if (x*y == 49) Figurs[fig].Stop = true;
			if (((x*y == 42)||((x*y == 36)))&&(abs(board.state[7][7]) < 9)) Figurs[fig].Stop = true;
			if ((abs(board.state[6][6]) < 9)&&(abs(board.state[7][6]) < 9)&&(abs(board.state[6][7]) < 9)&&(abs(board.state[7][7]) < 9)) 
				Figurs[fig].Stop = true;
		}
		Figurs[fig].setTexture();
	}
}

void TestGame::FixWhiteFigures(int fig)
{
	int x = Figurs[fig].pos.x;
	int y = Figurs[fig].pos.y;
	
	if ((x<=0)&&(y<=0)&&(Figurs[fig].player)&&																	
			( (!check(fig, x-1, y)) || (!check(fig, x, y-1)) )
	)	Figurs[fig].Stop = true;
	
	Figurs[fig].setTexture();
}	
*/
bool TestGame::checkGoPlayer(int x, int y)
{
	int fig = abs(board.state[x][y]);
	if ((fig >= 9)&&(fig < 18)) 
	{
		board.selected(x, y, sf::Color::Green); 	
		selectedF = fig;
		return false;
	}
	else board.selected(x, y, sf::Color::Red);
	
	if ((selectedF >= 9)&&(selectedF < 18)) 
		if ((Figurs[selectedF].player)&&check(selectedF, x, y)) return true;
		else return false;
	
	return false;
}	
//------------------------------------------------------------------------------
std::vector<TypeWay> TestGame::Trace(int x1, int y1, int x2, int y2)
{
	std::deque<TypeWay> deq;
	std::vector<TypeWay> ways;
	
	int x = x1; 
	int y = y1;
	int step = 0;
	
	while((x != x2)||(y != y2))
	{
		int NewX[4]={x-1, x+1, x, x };
		int NewY[4]={y, y, y-1, y+1};
		for(int i=0; i<4; i++)
			if ((NewX[i]>=0)&&(NewX[i]<8)&&(NewY[i]>=0)&&(NewY[i]<8))
				if (abs(board.state[NewX[i]][NewY[i]]) == 255) 
				{
					bool b=true;
					for(int k = 0; k<ways.size(); k++)
						if ((ways.at(k).x1 == NewX[i])&&(ways.at(k).y1 == NewY[i])&&(step>ways.at(k).step)) {b=false; break;}
					
					if (b) deq.push_front({x, y, NewX[i], NewY[i], step});
				}
		if (deq.empty()) break;
		TypeWay buf = deq.back();
		x = buf.x2; y = buf.y2;
		step = buf.step +1;
		ways.push_back(buf);
		deq.pop_back();	
	}	

	std::vector<TypeWay> res;
	
	if (ways.empty()) return res;
	

	TypeWay buf = ways.back();
	step = buf.step; x = buf.x1; y = buf.y1;
	res.push_back(buf);
	
	auto iter = ways.rbegin();  
	while(iter != ways.rend())	
	{	
		TypeWay buf = *iter;
		if ( (buf.step == step-1) && (buf.x2 == x) && (buf.y2 == y) )
		{	
			step = buf.step;
			x = buf.x1; y = buf.y1;
			res.push_back(buf);
		}
		iter++;			
	}	
	
	if ((res.front().x2 != x2)||(res.front().y2 != y2)) return {};
	
	
	std::cout << "------------- Trace function: "<< x1<<" "<<y1<<" "<<" "<<x2<<" "<<y2<<std::endl;
	//for(int i=0; i<ways.size(); i++)
	//	std::cout << "( "<< ways.at(i).x1<<" , "<<ways.at(i).y1<<" ) step="<<ways.at(i).step<< "  ( "<< ways.at(i).x2<<" , "<<ways.at(i).y2<<" ) "<<std::endl;
	//std::cout << "------------- --------------- "<<std::endl;
	for(int i=0; i<res.size(); i++)
		std::cout << "( "<< res.at(i).x1<<" , "<<res.at(i).y1<<" ) step="<<res.at(i).step<< "  ( "<< res.at(i).x2<<" , "<<res.at(i).y2<<" ) "<<std::endl;
	
	std::cout << "------------- --------------- "<<std::endl;
	
	return res;
}	
//------------------------------------------------------------------------------------------------------------------

void TestGame::markerTrace(std::vector<TypeWay> trace)
{
	for (int i=0; i < trace.size(); i++) 
		board.m_boardSquares[trace.at(i).x1 + (trace.at(i).y1 * 8)].setFillColor(sf::Color::Yellow);   //marker(buf.at(i).x1, y, sf::Color::Magenta);
	
	board.m_boardSquares[trace.front().x2 + (trace.front().y2 * 8)].setFillColor(sf::Color::Yellow); 
}
