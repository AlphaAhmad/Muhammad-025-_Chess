#include "King.h"
#include "Board.h"

void King::King_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 3, col); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	//_________________________________
	base_of_pieces(row, col, x);
}

King::King(int _r, int _c, int clr, Board* B, char x)
	: Piece(_r, _c, clr, B,x)
{

}

void King::Draw_Piece(Position x)
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White) : SetClr(Black));
	if (this->clr == White)
	{
		King_shape(x.row, x.col,White, -37);
	}
	else
	{
		King_shape(x.row, x.col, Black, -37);

	}
}

bool King::Legal_Move(const Position& Dst)
{
	int row_difference = 0,col_difference=0;
	row_difference = abs(this->Origin.row-Dst.row);
	col_difference = abs(this->Origin.col - Dst.col);
	      // Jab pick or drop positions ka difference 1 ho too condition tru ha
	if (isDiagnalMove(this->Origin, Dst) && (row_difference == 1))
	{
		if ((this->Origin.col < Dst.col && this->Origin.row < Dst.row) || (this->Origin.col > Dst.col && this->Origin.row > Dst.row))
		{
			return B->Diagnal_move_othenticator_1(this->Origin, Dst);
		}
		if ((this->Origin.col< Dst.col && this->Origin.row > Dst.row) || (this->Origin.col > Dst.col && this->Origin.row < Dst.row))
		{
			return B->Diagnal_move_othenticator_2(this->Origin, Dst);
		}

	}
	else if (isVerticleMove(this->Origin, Dst) && (row_difference == 1))
	{

		return B->Verticle_move_othenticator(this->Origin, Dst);

	}
	else if (isHorizontalMove(this->Origin, Dst) && (col_difference == 1))
	{
		return B->Horizontal_move_othenticator(this->Origin, Dst);
	}
	else
		return false;


}










