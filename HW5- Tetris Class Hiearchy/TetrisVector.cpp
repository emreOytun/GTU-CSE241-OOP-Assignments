#include <iostream>
#include <stdexcept>
#include "TetrisVector.h"
using namespace std;

namespace GTUTetris {


	TetrisVector::TetrisVector(int rowNum, int colNum) : AbstractTetris(rowNum, colNum), map(rowNum, vector<char>(colNum, ' ')) {
		
	}
	
	TetrisVector::TetrisVector(const TetrisVector& oth) : AbstractTetris(oth), map(oth.map) {
	
	}
	
	
	TetrisVector& TetrisVector::operator=(const TetrisVector& oth) {
		AbstractTetris::operator=(oth);
		map = oth.map;
		return *this;
	}
	
	void TetrisVector::writeToFile(ofstream& ostream) const {
		
		//status: 1
		//totalMoves: 20
		//isCurTetrominoActive: 0
		//rowNum: 10
		//colNum: 5
		//activeRowNum: 3
		//activeColNum: 2
		//startX: 7
		//staryY: 20
		//****
		//T***
		//TT**
		//T***
		//
		// MAP (* -> SPACE)
		//
		
		AbstractTetris::writeToFile(ostream);
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch = map[i][j];
				if (ch == ' ') ostream << "*";
				else ostream << ch;
			}
			ostream << "\n";
		}
				
	}
	
	void TetrisVector::readFromFile(ifstream& ifstream) {
		AbstractTetris::readFromFile(ifstream);
		
		map = vector< vector<char> >(rowNum, vector<char>(colNum, ' '));
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch;
				ifstream >> ch;
				if (ch == '*') map[i][j] = ' ';
				else map[i][j] = ch;
			}
		}
	}
	
	void TetrisVector::print() const {
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch = map[i][j];
				if (ch == ' ') cout << "*";
				else cout << ch;
			}
			cout << "\n";
		}
	}

	/* When finding a best fit of a given tetromino to put onto map, this function is used to check if it can be shifted horizantally when tetromino lowers step-by-step. */
	bool TetrisVector::checkHorizantalMovement(const Tetromino& comingT, int newYPos) const {
		Tetromino newT = comingT;
		int start_y = newT.getStartY();
		
		bool isPlaced = false;
		bool isDone = false;
		
		while (!isPlaced && !isDone) {
			if (!canBeAdded(newT)) isDone = true;
			else {
			
				if (newT.getStartY() == newYPos) {
					while (newT != comingT) {
						newT.rotate(Direction_t::Right);
					}
					if (canBeAdded(newT)) isPlaced = true; 		
					else isDone = true;
				}
				
				else {
				
					if (newYPos < start_y) newT.goLeft();
					else newT.goRight();
					
					bool canPlaced = false;
						
					if (canBeAdded(newT)) canPlaced = true;
					else {
						for (int i = 0; i < 3 && !canPlaced; ++i) {
							newT.rotate(Direction_t::Right);
							if (canBeAdded(newT)) canPlaced = true;
						}		
					}		
				
					if (!canPlaced) isDone = true;
				}
			}
		}
		
		return isPlaced;
		
	}

	/* It adds the given tetromino to the map. */
	void TetrisVector::addTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = t[i][j];
			}
		}
	}

	/* It deletes the given tetromino from the map. */
	void TetrisVector::deleteTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = ' ';
			}
		}
		
	}

	/* It checks if a given tetromino can be added to the map. */
	bool TetrisVector::canBeAdded(const Tetromino& t) const {
		
		int start_x = t.getStartX();
		int start_y= t.getStartY();
		
		bool canAdded = true;
		for (int i = 0; i < t.getActiveRowNum() && canAdded; ++i) {
			for (int j = 0; j < t.getActiveColNum() && canAdded; ++j) {
				if (i+start_x<0 || i+start_x>=rowNum || j+start_y<0 || j+start_y>=colNum)	canAdded = false;
				else if (map[i+start_x][j+start_y] != ' ' && t[i][j] != ' ') canAdded = false; 		
			}
		}

		return canAdded;
	}



}
