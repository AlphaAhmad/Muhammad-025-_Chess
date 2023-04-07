#pragma once

#include "Piece.h"

class Queen : public Piece

{
public:
	Queen(int _r, int _c, int clr, Board* B, char x);
	void Draw_Piece(Position x) override;
	bool Legal_Move(const Position& Dst) override;
	void Queen_shape(int row, int col, int clr, char x);
	void set_bool(bool x)override
	{

	}
};

