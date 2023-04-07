#include "Piece.h"
#include "Board.h"
  
// This cpp file includes all the function definition of al classes


Piece::Piece(const int _r, const int _c, const int clr, Board* Br,char x)
{
	Origin.row = _r;
	Origin.col = _c;
	this->clr = clr;
	//cout << &Br;
	this->B = Br;
	this->sym = x;
}

char Piece::get_sym()
{

	return this->sym;

}

void Piece::move(const int _r, const int _c)
{
	this->Origin.row = _r;
	this->Origin.col = _c;
}

Position Piece::get_Org()
{
	return this->Origin;
}
int Piece::get_clr()
{
	return clr;
}

bool Piece::isHorizontalMove(const Position& pick, const Position& drop)
{
	if (pick.row == drop.row)
	{
		return true;
	}
	return false;
}

bool Piece::isVerticleMove(const Position& pick, const Position& drop)
{
	if (pick.col == drop.col)
	{
		return true;
	}
	return false;
}

bool Piece::isDiagnalMove(const Position& pick, const Position& drop)
{
	
	int _c = abs(pick.col - drop.col);
	int _r= abs(pick.row - drop.row);
	if (_r == _c)
	{
		return true;
	}
	return false;
}


//____________  outhenticators   // checks if there any piece b/w the path of piece movement

void Piece::assign(const Piece& P)
{
	
	this->clr = P.clr;
	this->isAlive = P.isAlive;
	this->sym = P.sym;
	this->Origin.row = P.Origin.row;
	this->Origin.col = P.Origin.col;
	this->B = P.B;  // this one is a shallow copy be careful
	
}

void Piece::operator= (const Piece& P)
{
	
	delete[]this->B;
	this->assign(P);
}

void Piece::base_of_pieces(int row, int col, char x)
{
	gotoRowCol(row, col); cout << x;
	gotoRowCol(row + 1, col + 1); cout << x;
	gotoRowCol(row + 1, col); cout << x;
	gotoRowCol(row + 1, col - 1); cout << x;
	//_________________________________________
	gotoRowCol(row + 2, col - 2); cout << x;
	gotoRowCol(row + 2, col - 1); cout << x;
	gotoRowCol(row + 2, col); cout << x;
	gotoRowCol(row + 2, col + 1); cout << x;
	gotoRowCol(row + 2, col + 2); cout << x;

}

