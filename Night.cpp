#include "Night.h"

void Night::Night_shape(int row, int col, int clr, char x) // Ghora
{
	SetClr(clr);
	gotoRowCol(row - 3, col); cout << x;
	//_________________________________
	//gotoRowCol(row - 2, col + 2); cout << x;
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	//_________________________________
	//gotoRowCol(row - 1, col + 3); cout << x;
	gotoRowCol(row - 1, col + 2); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	gotoRowCol(row - 1, col - 2); cout << x;
	//_____________________________________
	gotoRowCol(row, col); cout << x;

	gotoRowCol(row, col); cout << x;
	gotoRowCol(row, col - 1); cout << x;
	//_________________________________________
	gotoRowCol(row + 1, col); cout << x;

	gotoRowCol(row + 2, col - 2); cout << x;
	gotoRowCol(row + 2, col - 1); cout << x;
	gotoRowCol(row + 2, col); cout << x;
	gotoRowCol(row + 2, col + 1); cout << x;
	gotoRowCol(row + 2, col + 2); cout << x;
}

Night::Night(int _r, int _c, int clr, Board* B, char x)
	: Piece(_r, _c, clr, B,x)
{

}

void Night::Draw_Piece(Position x)
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White) : SetClr(Black));
	if (this->clr == White)
	{
		Night_shape(x.row, x.col, White, -37);
	}
	else
	{
		Night_shape(x.row, x.col, Black, -37);

	}
}

bool Night::Legal_Move(const Position& Dst)
{
	// First checking the 2 row and 1 column moves
	int dif_row = abs(this->Origin.row-Dst.row);
	int dif_col = abs(this->Origin.col - Dst.col);
	if (dif_row == 2)
	{
		int x = abs(this->Origin.col - Dst.col);
		if (x==1)
		{
			return true;
		}
		

	}
	// Now checking 2 col and 1 row move
	else if (dif_col ==2)
	{
		int y = abs(this->Origin.row - Dst.row);
		if (y == 1)
		{
			return true;
		}

	}
	return false;

}


