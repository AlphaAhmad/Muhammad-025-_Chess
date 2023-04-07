#pragma once

#include <fstream>
#include "Board.h"
//#include "Player.h"

class Board;
class Piece;
class Player;

class Chess
{
	Position Src;
	Position Dst;
	int turn = 0;
	Player* Plr[2];
	Board* B;

public:
	
	Chess();
	bool Validate_pick(Player* Pl,Position x);
	bool Validate_drop(Player* Pl, Position x);
	void play_Chess();
	void turn_change();
	bool piece_legality_check(Position Pick,Position Drop);
	void save_Load(int turn);
	void undo_button();
	void redo_button();
	bool undo_signal(Position x);
	bool redo_signal(Position x);
	/*const Position& drop*/
};

  