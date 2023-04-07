#include "Pawn.h"
#include"Board.h"


Pawn::Pawn(int _r, int _c, int clr, Board* B, char x)
	: Piece(_r, _c, clr, B,x)
{

}

void Pawn::Draw_Piece(Position x) 
{
	//gotoRowCol(row, col);
	//(clr == White ? SetClr(White)  : SetClr(Black));
	if (this->clr == White)
	{
		Pawn_shape(x.row,x.col,White,-37);
	}
	else
	{
		Pawn_shape(x.row, x.col, Black, -37);

	}
}

bool Pawn::Legal_Move(const Position& Dst)
{
	// For White Pawn
	
	if (this->clr == White)
	{
		
		if (this->Origin.row - 1 == Dst.row && ((this->Origin.col==Dst.col-1)||(this->Origin.col == Dst.col + 1)))
		{          // Colour of the next piece has already been checked in Legal move
			
			// checking diagnal move of pawn
		    if (B->get_Piece(Dst.row, Dst.col) == nullptr)
			{
				return false;
			}
			this->first_move = true;
			return true;
		}
		   // checking straight move of pawn
		if (this->Origin.row - 1 == Dst.row && this->Origin.col == Dst.col)
		{
			
			if (B->get_Piece(Dst.row, Dst.col) != nullptr)
			{

				return false;
			}
			this->first_move = true;
			return true;
		
		}
		if (this->Origin.row - 2 == Dst.row && this->Origin.row == 6 && this->Origin.col == Dst.col)
		{

			if (B->get_Piece(Dst.row, Dst.col) != nullptr)
			{

				return false;
			}
			this->first_move = true;
			return true;

		}

    }  
	//  For Black Pawn
	else
	{
		if (this->Origin.row == Dst.row-1 && ((this->Origin.col == Dst.col - 1) || (this->Origin.col == Dst.col + 1)))
		{          // Colour of the next piece has already been checked in Legal move
			
			if (B->get_Piece(Dst.row, Dst.col) == nullptr) // if there is no opponents piece on side pawn cannot move
			{

				return false;
			}
			this->first_move = true;
			return true;
		}

		if (this->Origin.row == Dst.row - 1 && this->Origin.col == Dst.col )
		{
			
			if (B->get_Piece(Dst.row, Dst.col) != nullptr) // if there a piece in front pawn cant move
			{
				
				return false;

			}
			this->first_move = true;
			return true;
		}
		if (this->Origin.row + 2 == Dst.row && this->Origin.row==1 && this->Origin.col == Dst.col)
		{

			if (B->get_Piece(Dst.row, Dst.col) != nullptr)
			{
				return false;
			}
			this->first_move = true;
			return true;

		}
	}
	return false;
	
}

void Pawn::Pawn_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 1, col); cout << char(-129);
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


