#pragma once

#include "Piece.h"
#include "Player.h"
class Board
{
protected:

	Piece* ** Ps;
	int dim = 8; // Board dimension = 8 x 8
	Piece*** decoy_Ps = nullptr;

public:

	
	Board(const Board& B);
	Board(fstream& rdr);   // 1st initiaize all pieces on board
	Piece* get_Piece(int r, int c) { return Ps[r][c]; }; // returns the address stored in the pointer of piece type pointer to the inherited base part of derived class piece 
	//friend void printBox(Piece*** Ps, int shift_r, int shift_c, int _r, int _c, int start_row, int start_col, int clr);
	void print_Board(int pick_r , int pick_c , bool is_highlight, int turn);
	void move_piece(Position src, Position Dst);
	
	bool Horizontal_move_othenticator(const Position pick,const Position drop);
	bool Verticle_move_othenticator(const Position pick, const Position drop);
	bool Diagnal_move_othenticator_1(const Position pick, const Position drop);
	bool Diagnal_move_othenticator_2(const Position pick, const Position drop);
	bool Validate_drop_beta(int turn, Position x);
	bool isPawnPromoted();
	void Pawn_changer(char x, Position p);
	Position King_position(int turn);
	
	
	bool Self_check(int turn);  // checks the check 
	bool checker(Position pick,Position Drop,int turn);   // checks and restricts the move played (if it doesnot saves the king) after check is declared 
	
	bool checkmate(int turn);
	
	bool checkmate_extention(int pick_row, int pick_col,int turn);

	bool stale_Mate(int turn);

	void printBox(int turn,int shift_r, int shift_c, int _r, int _c, int start_row, int start_col, int clr, int pick_r, int pick_c, bool is_highlight);
	bool castling_legality(Position pick, Position Drop, int turn);
	bool casteling(Position pick, Position Drop, int &turn,Board* undo_B);
	void assign(const Board& Bs);
	void undo_Board_Loader(Board*B);
	Board operator= (const Board& B);
	void undo(Board* B);
	void redo();
	~Board();

	


};


// Pahla check ho ga or phir usa ma check mate lga ho gaa
// Magar stale mate Alahda ho ga


