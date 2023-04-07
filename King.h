#pragma once
#include "Piece.h"



class King: public Piece
{
public:
	King(int _r, int _c, int clr, Board* B, char x);
	void Draw_Piece(Position x) override;
	bool Legal_Move(const Position& Dst) override;
	void King_shape(int row, int col, int clr, char x);
	void set_bool(bool x)override
	{

	}
};

