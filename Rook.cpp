#include "Rook.h"
#include "board.h"
Rook::Rook(int _r, int _c, int clr, Board* B, char x)
	: Piece(_r, _c, clr, B,x)
{

}

void Rook::Draw_Piece(Position x)
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White) : SetClr(Black));
	if (clr == White)
	{
		Rook_shape(x.row, x.col, White, -37);
	}
	else
	{
		Rook_shape(x.row, x.col, Black, -37);

	}
}

bool Rook::Legal_Move(const Position& Dst)
{
	if (isVerticleMove(this->Origin,Dst))
	{
		return B->Verticle_move_othenticator(this->Origin, Dst);
	}
	else if (isHorizontalMove(this->Origin, Dst))
	{
		return B->Horizontal_move_othenticator(this->Origin, Dst);
	}
	return false;




}

void Rook::Rook_shape(int row, int col, int clr, char x)
{
	SetClr(clr);

	gotoRowCol(row - 3, col); cout << char(-129);
	gotoRowCol(row - 2, col); cout << x;
	//_____________________

	//_____________________
	gotoRowCol(row - 1, col + 1); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	//______________________
	gotoRowCol(row, col); cout << x;
	//______________________________
	base_of_pieces(row, col, x);
}