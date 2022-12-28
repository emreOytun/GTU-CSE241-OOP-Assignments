#include <iostream>
#include <fstream>
#include "TetrisArray1D.h"
using namespace std;

namespace GTUTetris {


	TetrisArray1D::TetrisArray1D(int rowNum, int colNum) : AbstractTetris(rowNum, colNum), map(nullptr) {
		initMemory(rowNum, colNum);
	}
	
	TetrisArray1D::TetrisArray1D(const TetrisArray1D& oth) : AbstractTetris(oth), map(nullptr) {
		initMemory(rowNum, colNum);
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				map[colNum*i + j] = oth.map[colNum*i + j];
			}
		} 
	}
	
	TetrisArray1D& TetrisArray1D::operator=(const TetrisArray1D& oth) {
		AbstractTetris::operator=(oth);
		
		initMemory(rowNum, colNum);
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				map[colNum*i + j] = oth.map[colNum*i + j];
			}
		}
		
		return *this;
	}
	
	TetrisArray1D::~TetrisArray1D() {
		if (map != nullptr) {
			delete [] map;
		}
	}
	
	void TetrisArray1D::writeToFile(ofstream& ostream) const {
		AbstractTetris::writeToFile(ostream);
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch = map[i*colNum + j];
				if (ch == ' ') ostream << "*";
				else ostream << ch;
			}
			ostream << "\n";
		}
	}
	
	void TetrisArray1D::readFromFile(ifstream& ifstream) {
		AbstractTetris::readFromFile(ifstream);
		
		initMemory(rowNum, colNum);
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch;
				ifstream >> ch;
				if (ch == '*') map[i*colNum + j] = ' ';
				else map[i*colNum + j] = ch;
			}
		}
	}
	
	void TetrisArray1D::print() const {
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				char ch = map[i*colNum+j];
				if (ch == ' ') cout << "*";
				else cout << ch;
			}
			cout << "\n";
		}
	}

	/* When finding a best fit of a given tetromino to put onto map, this function is used to check if it can be shifted horizantally when tetromino lowers step-by-step. */
	bool TetrisArray1D::checkHorizantalMovement(const Tetromino& comingT, int newYPos) const {
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
	void TetrisArray1D::addTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[(i+t.getStartX())*colNum + j+t.getStartY()] = t[i][j];
			}
		}
	}

	/* It deletes the given tetromino from the map. */
	void TetrisArray1D::deleteTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[(i+t.getStartX())*colNum + j+t.getStartY()] = ' ';
			}
		}
		
	}

	/* It checks if a given tetromino can be added to the map. */
	bool TetrisArray1D::canBeAdded(const Tetromino& t) const {
		
		int start_x = t.getStartX();
		int start_y= t.getStartY();
		
		bool canAdded = true;
		for (int i = 0; i < t.getActiveRowNum() && canAdded; ++i) {
			for (int j = 0; j < t.getActiveColNum() && canAdded; ++j) {
				if (i+start_x<0 || i+start_x>=rowNum || j+start_y<0 || j+start_y>=colNum)	canAdded = false;
				else if (map[(i+start_x)*colNum + j+start_y] != ' ' && t[i][j] != ' ') canAdded = false; 		
			}
		}

		return canAdded;
	}
	
	void TetrisArray1D::initMemory(int rowNum, int colNum) {
		if (map != nullptr) delete [] map;
		map = new char[rowNum * colNum];
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				map[colNum*i + j] = ' ';
			}
		}
	}
	
	
		
}
