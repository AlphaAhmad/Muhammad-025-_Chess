#pragma once 
#include <Windows.h>
#include <iostream>
#include "Utility.h"
//include "Board.h"
//#include "Chess.h"


using namespace std;



//________________________________________________


class Board;


class Piece
{
protected:
	char sym;
	Position Origin;
	bool isAlive = true;
	Board* B;
	int clr;
public:
	
	Position get_Org();
	virtual void set_bool(bool x)=0;
	char get_sym();
	int get_clr();
	void set_B(Board* Bptr) { this->B = Bptr; }
	Piece(const int _r,const int _c,const int clr,  Board* B,char x);
	
	virtual void Draw_Piece(Position x) = 0;
	void move(const int _r, const int _c); // Just changes the origin of piece to desired coordinates
	
	static bool isHorizontalMove(const Position &pick, const Position& drop);
	static bool isVerticleMove(const Position& pick, const Position& drop);
	static bool isDiagnalMove(const Position& pick, const Position& drop);
	
	// These function will already have origin of piece they only need its drop position.
	void assign(const Piece& P);
	void operator=(const Piece& P);
	
	virtual bool Legal_Move(const Position& Dst)=0; // every derived piece will have its own
	void base_of_pieces(int row, int col, char x);
	

};

