#include "Bishop.h"
#include "Board.h"

void Bishop::Bishop_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 3, col + 1); cout << char(-129);
	gotoRowCol(row - 3, col); cout << char(-129);
	gotoRowCol(row - 3, col - 1); cout << char(-129);
	//_____________________
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	//_____________________

	gotoRowCol(row - 1, col); cout << x;

	//______________________
	gotoRowCol(row, col); cout << x;
	//______________________________
	base_of_pieces(row, col, x);
}

Bishop::Bishop(int _r, int _c, int clr, Board* B,char x)
	: Piece(_r, _c, clr, B,x)
{

}

void Bishop::Draw_Piece(Position x)
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White) : SetClr(Black));
	if (this->clr == White)
	{
		Bishop_shape(x.row, x.col, White, -37);
	}
	else
	{
		Bishop_shape(x.row, x.col, Black, -37);

	}
}

bool Bishop::Legal_Move(const Position& Dst)
{
	if (isDiagnalMove(this->Origin,Dst))
	{
		if ((this->Origin.col < Dst.col && this->Origin.row < Dst.row) || (this->Origin.col > Dst.col && this->Origin.row > Dst.row))
		{
			return B->Diagnal_move_othenticator_1(this->Origin,Dst);
		}
		else if ((this->Origin.col < Dst.col && this->Origin.row > Dst.row) || (this->Origin.col > Dst.col && this->Origin.row < Dst.row))
		{
			return B->Diagnal_move_othenticator_2(this->Origin, Dst);
		}

	}
	else
	{
		return false;
	}



}



