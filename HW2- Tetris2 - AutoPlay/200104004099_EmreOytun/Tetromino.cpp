#include <iostream>
#include <vector>
#include "Tetromino.h"
using namespace std;

/* Swaps two integer variables. */
void swap(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

/* Precondition : Takes the Tetromino_t as parameter to initialize. */
/* Postcondition : Initializes the rotateMatrix, blocks, active_rowNum, active_colNum according to the type. */
void Tetromino::init(Tetromino_t tetrominoType) {
	switch(tetrominoType) {
	
		case Tetromino_t::I :
			blocks[0][0] = blocks[0][1] = blocks[0][2] = blocks[0][3] = 'I';
			setActualBlocks();
			
			active_rowNum = 1;
			active_colNum = 4;
			break;
			
		case Tetromino_t::O :
			blocks[0][0] = blocks[0][1] = blocks[1][0] = blocks[1][1] = 'O';
			setActualBlocks();

			active_rowNum = 2;
			active_colNum = 2;
			break;
			
		case Tetromino_t::T :
			blocks[1][0] = blocks[1][1] = blocks[1][2] = blocks[0][1] = 'T';
			setActualBlocks();
			
			active_rowNum = 2;
			active_colNum = 3;
			break;
			
		case Tetromino_t::J :
			blocks[0][0] = blocks[1][0] = blocks[1][1] = blocks[1][2] = 'J';
			setActualBlocks();
			
			active_rowNum = 2;
			active_colNum = 3;
			break;
			
		case Tetromino_t::L :
			blocks[0][2] = blocks[1][0] = blocks[1][1] = blocks[1][2] = 'L';
			setActualBlocks();
			
			active_rowNum = 2;
			active_colNum = 3;
			break;
			
		case Tetromino_t::S :
			blocks[0][1] = blocks[0][2] = blocks[1][0] = blocks[1][1] = 'S';
			setActualBlocks();
			
			active_rowNum = 2;
			active_colNum = 3;
			break;
			
		case Tetromino_t::Z :
			blocks[0][0] = blocks[0][1] = blocks[1][1] = blocks[1][2] = 'Z';
			setActualBlocks();
			
			active_rowNum = 2;
			active_colNum = 3;
			break;
	
	}
}

/* Checks if the left col of the blocks vector is empty or not. */
bool Tetromino::isLeftColEmpty() const {
	bool isEmpty = true;
	for (int i = 0; i < blocks.size(); ++i) {
		if (blocks[i][0] != ' ') isEmpty = false;
	}		
	return isEmpty;
}

/* Checks if the top row of the blocks vector is empty or not. */
bool Tetromino::isTopRowEmpty() const {
	bool isEmpty = true;
	for (int j = 0; j < blocks[0].size(); ++j) {
		if (blocks[0][j] != ' ') isEmpty = false;
	}
	return isEmpty;
}

/* Shifts the blocks matrix 1 col toward left  */
void Tetromino::shiftActualBlocksToLeft() {
	for (int i = 0; i < blocks.size(); ++i) {
		for (int j = 1; j < blocks[0].size(); ++j) {
			blocks[i][j-1] = blocks[i][j];
			blocks[i][j] = ' ';
		}
	}
}

/* Shifts the blocks matrix 1 column upward. */
void Tetromino::shiftActualBlocksToUp() {
	for (int i = 0; i < blocks[0].size(); ++i) {
		for (int j = 1; j < blocks.size(); ++j) {
			blocks[j-1][i] = blocks[j][i];
			blocks[j][i] = ' ';
		}
	}
}

/* Sets the blocks vector using the rotateMatrix so that blocks vector has the actual blocks in the top mostleft part. */
void Tetromino::setActualBlocks() {
	while (isTopRowEmpty()) shiftActualBlocksToUp();
	while (isLeftColEmpty()) shiftActualBlocksToLeft();
}

/* Find and return the left most bottom indexes of the tetromino. */
vector<int> Tetromino::getLeftMostBottomIndexes() const {
	bool isFound = false;
	int lastRowIndex = active_rowNum - 1;
	int i;
	for (i = 0; i < blocks[lastRowIndex].size() && !isFound;) {
		if (blocks[lastRowIndex][i] != ' ') isFound = true;
		else ++i;
	}	
	
	return vector<int>{lastRowIndex, i};
}

/* Find and return the right most bottom indexes of the tetromino. */
vector<int> Tetromino::getRightMostBottomIndexes() const {
	bool isFound = false;
	int lastRowIndex = active_rowNum - 1;
	int i;
	for (i = blocks[lastRowIndex].size()-1; i >= 0 && !isFound;) {
		if (blocks[lastRowIndex][i] != ' ') isFound = true;
		else --i;
	}	

	return vector<int>{lastRowIndex, i};
}

Tetromino::Tetromino() : active_rowNum(0), active_colNum(0), blocks(4, vector<char>(4, ' ')) {
	init(Tetromino_t::O);
}

Tetromino::Tetromino(Tetromino_t tetrominoType) : active_rowNum(0), active_colNum(0), startX(0), startY(0), blocks(4, vector<char>(4, ' ')) {
	init(tetrominoType);	
}

Tetromino::Tetromino(Tetromino_t tetrominoType, int startX, int startY) : active_rowNum(0), active_colNum(0), blocks(4, vector<char>(4, ' ')) {
	setStartPosition(startX, startY);
	init(tetrominoType);
}

void Tetromino::print() const {
	for (int i = 0; i < active_rowNum; ++i) {
		for (int j = 0; j < active_colNum; ++j) {
			cout << blocks[i][j];
		}
		cout << "\n";
	}
}

/* Precondition : Takes a rotation direction as parameter. */
/* Postconditon : Rotates the tetromino according to the given direction. */
void Tetromino::rotate(Direction_t direction) {
	vector< vector<char> > rotatedBlocks(blocks[0].size(), vector<char>(blocks.size(), ' '));
	
	switch (direction) {
		
		case Direction_t::Right :
			for (int i = 0; i < blocks.size(); ++i) {
				for (int j = 0; j <  blocks[0].size(); ++j) {
					rotatedBlocks[j][blocks[0].size()-1-i] = blocks[i][j];
				}
			}
			break;
			
		case Direction_t::Left :
			for (int i = 0; i < blocks.size(); ++i) {
				for (int j = 0; j < blocks[0].size(); ++j) {
					rotatedBlocks[blocks.size()-1-j][i] = blocks[i][j];
				}
			}
			break;
	
	}

	blocks = rotatedBlocks;
	setActualBlocks();
	
	swap(active_rowNum, active_colNum);
}

/* Precondition : Takes another tetromino and the relative direction. */
/* Postconditon : Checks if the given tetromino can fit into the given direction. */
/* 	1) Call findFittingIndexes_and_spaceNumbers_whenRight function according to the given direction.
	2) If the function return 0 as deadspace number, then return true. Return false otherwise.
*/
bool Tetromino::canFit(const Tetromino& oth, Direction_t relativeDirection) const {
	bool canFit = false;
	
	switch(relativeDirection) {
	
		case Direction_t::Right :
			if (findFittingIndexes_and_spaceNumbers_whenRight(oth).at(2) == 0) canFit = true;
			break;
			
		case Direction_t::Left :
			if (oth.findFittingIndexes_and_spaceNumbers_whenRight(*this).at(2) == 0) canFit = true;
			break;
		
	}
	
	return canFit;
}

int Tetromino::getStartX() const { return startX; };
int Tetromino::getStartY() const { return startY; };

void Tetromino::setStartPosition(int startX, int startY) {
	setStartX(startX);
	setStartY(startY);
} 

void Tetromino::setStartX(int startX_) {
	startX = startX_;
}

void Tetromino::setStartY(int startY_) {
	startY = startY_;
}

int Tetromino::getActiveColNum() const { return active_colNum; }
int Tetromino::getActiveRowNum() const { return active_rowNum; }

vector< vector<char> > Tetromino::getBlock() const { return blocks; }

/* Find in which indexes the other tetromino can be placed and how many deadspaces there are, when it is in the right of this tetromino. */
/*	1) Get the right most indexes of this tetromino, and the other tetromino.
	2) Starting from testing like the other tetromino is placed just onto this tetromino, find how many times the other tetrimino should go toward right to be placed without crossing.
	3) Count the deadspaces when the other tetromino can be placed to the right.
	NOTE : Deadspace is a space where the player cannot place a tetromino block there.
*/
vector<int> Tetromino::findFittingIndexes_and_spaceNumbers_whenRight(const Tetromino& t2) const {
	vector<int> t1_i = getRightMostBottomIndexes();
	int t1_x = t1_i[0];
	int t1_y = t1_i[1];
	
	vector<int> t2_i = t2.getLeftMostBottomIndexes();
	int t2_x = t2_i[0];
	int t2_y = t2_i[1];
	
	/* The difference between the indexes of the second tetromino and the real indexes. */
	int t2_real_oX = (t1_x) - t2_x;
	int t2_real_oY = (t1_y + 1) - t2_y;
	
	/* Find how many times the other tetromino should go to the left, and so find the indexes of the other tetromino in this place. */
	bool isFit = true;
	do {
		isFit = true;
	
		for (int t2_i = 0; t2_i < t2.active_rowNum && isFit; ++t2_i) {
			if (t2_i + t2_real_oX >= 0) {
				for (int t2_j = 0; t2_j < t2.active_colNum && t2_j + t2_real_oY <= active_colNum-1 && isFit; ++t2_j) {	
					if (t2.blocks[t2_i][t2_j] != ' ' && blocks[t2_i + t2_real_oX][t2_j + t2_real_oY] != ' ') isFit = false;
				}
			}
		}
		
		if (!isFit) {
			t2_real_oX;
			++t2_real_oY;
		}
		
	} while (!isFit);
	
	
	/* Count the total spaces : */
	int commonRowNum = active_rowNum;
	if (t2.active_rowNum < active_rowNum) commonRowNum = t2.active_rowNum;
	
	int commonRow_realX = active_rowNum - commonRowNum;
	
	int totalSpaces = 0;
	for (int i = commonRow_realX; i < commonRow_realX + commonRowNum; ++i) {
		
		int t1_rightMost_realY;
		int t2_leftMost_realY;

		/* Find the real col index of the most-right block of this tetromino. */
		bool isFound;
		for (int j = active_colNum-1, isFound = false; j >= 0 && !isFound; --j) {
			if (blocks[i][j] != ' ') {
				t1_rightMost_realY = j;
				isFound = true;
			}
		}
	
		/* Find the real col index of the most-right block of this tetromino. */
		for (int j = 0, isFound = false; j < t2.active_colNum && !isFound; ++j) {
			if (t2.blocks[i-t2_real_oX][j] != ' ') {
				t2_leftMost_realY = j + t2_real_oY;
				isFound = true;
			}
		}
		
		totalSpaces += t2_leftMost_realY - t1_rightMost_realY - 1;
	}
	
	
	/* Count the deadspaces(spaces that no more tetromino can be placed in) */
	int deadSpaces = (t2_real_oY + t2_y) - (t1_y + 1);
	
	return vector<int>{t2_real_oX + getStartX(), t2_real_oY + getStartY(), deadSpaces, totalSpaces};
}

void Tetromino::lower() {
	setStartX(startX+1);
}

void Tetromino::goRight() {
	setStartY(startY+1);
}

void Tetromino::goLeft() {
	setStartY(startY-1);
}

bool Tetromino::operator==(const Tetromino& oth) {
	bool res = false;
	
	if (this == &oth) res = true;
	
	if (active_rowNum == oth.active_rowNum && active_colNum == oth.active_colNum) {
		for (int i = 0; i < active_rowNum; ++i) {
			for (int j = 0; j < active_colNum; ++j) {
				if (blocks[i][j] != oth.blocks[i][j]) res = false;
			}
		}
		res = true;
	}
	
	res = false;

	return res;
}

bool Tetromino::operator!=(const Tetromino& oth) {
	return !((*this) == oth);
}


