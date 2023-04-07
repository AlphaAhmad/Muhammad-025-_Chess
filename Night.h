#pragma once

#include "Piece.h"

class Night : public Piece
{
public:
	Night(int _r, int _c, int clr, Board* B, char x);
	void Draw_Piece(Position x) override;
	bool Legal_Move(const Position& Dst) override;
	void Night_shape(int row, int col, int clr, char x); // Ghora
	void set_bool(bool x)override
	{

	}
};

