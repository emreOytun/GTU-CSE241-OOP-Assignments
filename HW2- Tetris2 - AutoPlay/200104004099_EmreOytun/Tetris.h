#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <vector>
#include "Tetromino.h"
using namespace std;

/*************************** MAP CLASS **************************/

/* Map class to render tetrominos and print them into the screen. */
class Map {
	const static int CANNOT_FIT_TETROMINO_X_VALUE = -10000;

public :
	Map(int rowNum, int colNum);	
	Map(vector<Tetromino> list);
	
	int getRowNum() const;
	int getColNum() const;
	
	void setMap(vector<Tetromino> list);
	void print() const;
	
	int countTotalSpaces() const;
	int countDeadSpaces() const;
	
	vector<int> getFittingIndex_and_spaceNumbers(const Tetromino& newT) const;
	void addTetromino(const Tetromino& t);
	void deleteTetromino(const Tetromino& t);
	
	bool canBeAdded(const Tetromino& t) const;

private :
	vector< vector<char> > map;

	int rowNum;
	int colNum;
	
	bool checkVerticalFitting(Tetromino newT, int fittingX, int fittingY) const;
	bool checkHorizantalFitting(Tetromino newT, int newT_fittingY) const;
	void addActiveBlock(const vector< vector<char> >& block, int start_x,int start_y);
};


/******************** TETRIS CLASS ********************/

class Tetris {

public :
	Tetris(int rowNum, int colNum);
	
	void add(const Tetromino& newTetromino);
	void fit();
	void draw() const;
	void draw();
	void animate();
	
	bool gameStatus() const;

private :
	Map gameMap;	
	vector<Tetromino> addedTetrominos;
	bool status;
	
	bool isCurTetrominoActive;
	Tetromino curTetromino;
	int curTetromino_fittingX;
	int curTetromino_fittingY;
	
	Tetromino findBestFitToMap(Tetromino t);
	
};

/*****************************************************/


#endif
