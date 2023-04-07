#pragma once
#include "Piece.h"

#
class Pawn: public Piece
{
	bool first_move = false;
public:
	Pawn(int _r, int _c, int clr, Board* B, char x);
	void Draw_Piece(Position x) override;
	bool Legal_Move(const Position& Dst) override;
	void set_bool(bool x)override
	{
		first_move = x;
	}


	void Pawn_shape(int row, int col, int clr, char x);
	
	
};




