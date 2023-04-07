#include "Player.h"

Player::Player(string n, int c, int T)
{
	this->name = n;
	this->clr = c;
	this->turn = T;
}

Position Player::Selectposition(int& prow_check, int& pcol_check)
{

	Position x;
	
	int ch; int d;
	int count = 0;
	do
	{
		getRowColbyLeftClick(ch, d);
		x.row = (ch / 10);  // cols = box dimension = 10
		x.col = (d / 10);   // b_rows = box dimension = 10 
		count++;
	} while ((x.row==prow_check&&x.col==pcol_check)&& count<2);
	prow_check = x.row;
	pcol_check = x.col;
	//x.row--;
	//x.col--;
	return x;
	



}

