#include "Queen.h"
#include "Board.h"

void Queen::Queen_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 3, col + 2); cout << x;
	gotoRowCol(row - 3, col); cout << x;
	gotoRowCol(row - 3, col - 2); cout << x;
	//___________________________________

	gotoRowCol(row - 2, col + 2); cout << x;
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	gotoRowCol(row - 2, col - 2); cout << x;

	//___________________________________
	gotoRowCol(row - 1, col + 1); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	//___________________________________
	base_of_pieces(row, col, x);
}

Queen::Queen(int _r, int _c, int clr, Board* B, char x)
	: Piece(_r, _c, clr, B,x)
{

}

void Queen::Draw_Piece(Position x)
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White) : SetClr(Black));
	if (clr == White)
	{
		Queen_shape(x.row, x.col, White, -37);
	}
	else
	{
		Queen_shape(x.row, x.col, Black, -37);

	}

}

bool Queen::Legal_Move(const Position& Dst)
{
	if (isHorizontalMove(this->Origin, Dst))
	{
		return B->Horizontal_move_othenticator(this->Origin, Dst);
	}
	else if (isVerticleMove(this->Origin, Dst))
	{
		return B->Verticle_move_othenticator(this->Origin, Dst);
	}
	else if (isDiagnalMove(this->Origin, Dst))
	{              // From bottom left to top right and vice verse
		if ((this->Origin.col < Dst.col && this->Origin.row < Dst.row) || (this->Origin.col > Dst.col && this->Origin.row > Dst.row))
		{
			return B->Diagnal_move_othenticator_1(this->Origin, Dst);
		}
		{              // From bottom right to top left and vice verse
			if ((this->Origin.col< Dst.col && this->Origin.row > Dst.row) || (this->Origin.col > Dst.col && this->Origin.row < Dst.row))
			{
				return B->Diagnal_move_othenticator_2(this->Origin, Dst);
			}
		}
		return false;



	}
}

