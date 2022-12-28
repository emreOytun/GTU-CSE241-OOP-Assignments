#include <iostream>
#include <stdexcept>
#include "Tetromino.h"
using namespace std;

namespace {
	/* Swaps two integer variables. */
	void swapNum(int& num1, int& num2) {
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}
}

namespace GTUTetris {

	Tetromino::Tetromino() : active_rowNum(0), active_colNum(0), blocks(nullptr) {
		initMemory();
		init(Tetromino_t::O);
	}

	Tetromino::Tetromino(const Tetromino_t& tetrominoType) : active_rowNum(0), active_colNum(0), startX(0), startY(0), blocks(nullptr) {
		initMemory();
		init(tetrominoType);	
	}

	Tetromino::Tetromino(const Tetromino_t& tetrominoType, int startX, int startY) : active_rowNum(0), active_colNum(0), blocks(nullptr) {
		initMemory();
		setStartPosition(startX, startY);
		init(tetrominoType);
	}

	Tetromino::Tetromino(const Tetromino& oth) : blocks(nullptr) {
		initMemory();
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				blocks[i][j] = oth.blocks[i][j];
			}
		}
		
		active_rowNum = oth.active_rowNum;
		active_colNum = oth.active_colNum;
		startX = oth.startX;
		startY = oth.startY;
	}

	Tetromino& Tetromino::operator=(const Tetromino& oth) {
		if (this == &oth) return *this;
		
		if (blocks == nullptr) initMemory();
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				blocks[i][j] = oth.blocks[i][j];
			}
		}
		
		active_rowNum = oth.active_rowNum;
		active_colNum = oth.active_colNum;
		startX = oth.startX;
		startY = oth.startY;

		return *this;
	}

	Tetromino::~Tetromino() {
		if (blocks != nullptr) {
			for (int i = 0; i < ROWSIZE; ++i) {
				if (blocks[i] != nullptr) {
					delete [] blocks[i];
					blocks[i] = nullptr;
				}
			}
			delete [] blocks;
			blocks = nullptr;
		}
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
	void Tetromino::rotate(const Direction_t& direction) {
		char** rotatedBlocks = new char*[ROWSIZE];
		for (int i = 0; i < ROWSIZE; ++i) {
			rotatedBlocks[i] = new char[COLSIZE];
		}
		
		switch (direction) {
			
			case Direction_t::Right :
				for (int i = 0; i < ROWSIZE; ++i) {
					for (int j = 0; j <  COLSIZE; ++j) {
						rotatedBlocks[j][COLSIZE-1-i] = blocks[i][j];
					}
				}
				break;
				
			case Direction_t::Left :
				for (int i = 0; i < ROWSIZE; ++i) {
					for (int j = 0; j < COLSIZE; ++j) {
						rotatedBlocks[ROWSIZE-1-j][i] = blocks[i][j];
					}
				}
				break;
		
		}

		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				blocks[i][j] = rotatedBlocks[i][j];
			}
			delete [] rotatedBlocks[i];
		}
		delete [] rotatedBlocks;
		rotatedBlocks = nullptr;
		
		setActualBlocks();
		swapNum(active_rowNum, active_colNum);
	}

	void Tetromino::changeType(const Tetromino_t& tetrominoType) {
		/* Empty the data. */
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				blocks[i][j] = ' ';
			}
		}
		
		/* Initialize the new type. */
		init(tetrominoType);
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


	void Tetromino::lower() {
		setStartX(startX+1);
	}

	void Tetromino::goRight() {
		setStartY(startY+1);
	}

	void Tetromino::goLeft() {
		setStartY(startY-1);
	}

	const char* Tetromino::operator[](int idx) const {
		if (idx < 0 || idx >= active_rowNum) {
			throw out_of_range("Index is out of boundaries for tetromino.");
		}
		return blocks[idx];
	}

	char* Tetromino::operator[](int idx) {
		if (idx < 0 || idx >= active_rowNum) {
			throw out_of_range("Index is out of boundaries for tetromino.");
		}
		return blocks[idx];
	}

	bool Tetromino::operator==(const Tetromino& oth) const {
		bool res = false;
		
		if (this == &oth) res = true;
		
		else if (active_rowNum == oth.active_rowNum && active_colNum == oth.active_colNum) {
			bool blocksEqual = true;
			for (int i = 0; i < active_rowNum && blocksEqual; ++i) {
				for (int j = 0; j < active_colNum && blocksEqual; ++j) {
					if (blocks[i][j] != oth.blocks[i][j]) blocksEqual = false;
				}
			}
			if (blocksEqual) res = true;
		}

		return res;
	}

	bool Tetromino::operator!=(const Tetromino& oth) const {
		return !((*this) == oth);
	}
	
	void Tetromino::writeToFile(ofstream& ostream) const {
		
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
		
		ostream << "activeRowNum: " << active_rowNum << "\n";
		ostream << "activeColNum: " << active_colNum << "\n";
		ostream << "startX: " << startX << "\n";
		ostream << "startY: " << startY << "\n";
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				if (blocks[i][j] == ' ') ostream << "*";
				else ostream << blocks[i][j];
			}
			ostream << "\n";
		}
				
	}
	
	void Tetromino::readFromFile(ifstream& ifstream) {
		string buff;
		
		ifstream >> buff;			// activeRowNum: 
		ifstream >> active_rowNum;	// 3
		
		ifstream >> buff;			// activeColNum;
		ifstream >> active_colNum;	// 2
		
		ifstream >> buff;			// startX:
		ifstream >> startX;			// 7
		
		ifstream >> buff;			// startY:
		ifstream >> startY;			// 20
		
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 0; j < COLSIZE; ++j) {
				char ch;
				ifstream >> ch;
				if (ch == '*') blocks[i][j] = ' ';
				else blocks[i][j] = ch;
			}
			ifstream.get();
		}
		
	}


	/* Precondition : Takes the Tetromino_t as parameter to initialize. */
	/* Postcondition : Initializes the rotateMatrix, blocks, active_rowNum, active_colNum according to the type. */
	void Tetromino::init(const Tetromino_t& tetrominoType) {
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

	/* Allocates dynamic memory to keep tetromino's data. */
	void Tetromino::initMemory() {
		blocks = new char*[ROWSIZE];
		for (int i = 0; i < ROWSIZE; ++i) {
			blocks[i] = new char[COLSIZE];
			for (int j = 0; j < COLSIZE; ++j) {
				blocks[i][j] = ' ';
			}
		}
	}

	/* Checks if the left col of the blocks array is empty or not. */
	bool Tetromino::isLeftColEmpty() const {
		bool isEmpty = true;
		for (int i = 0; i < ROWSIZE; ++i) {
			if (blocks[i][0] != ' ') isEmpty = false;
		}		
		return isEmpty;
	}

	/* Checks if the top row of the blocks array is empty or not. */
	bool Tetromino::isTopRowEmpty() const {
		bool isEmpty = true;
		for (int j = 0; j < COLSIZE; ++j) {
			if (blocks[0][j] != ' ') isEmpty = false;
		}
		return isEmpty;
	}

	/* Shifts the blocks matrix 1 col toward left  */
	void Tetromino::shiftActualBlocksToLeft() {
		for (int i = 0; i < ROWSIZE; ++i) {
			for (int j = 1; j < COLSIZE; ++j) {
				blocks[i][j-1] = blocks[i][j];
				blocks[i][j] = ' ';
			}
		}
	}

	/* Shifts the blocks matrix 1 column upward. */
	void Tetromino::shiftActualBlocksToUp() {
		for (int i = 0; i < COLSIZE; ++i) {
			for (int j = 1; j < ROWSIZE; ++j) {
				blocks[j-1][i] = blocks[j][i];
				blocks[j][i] = ' ';
			}
		}
	}

	/* Sets the blocks array using the rotateMatrix so that blocks array has the actual blocks in the top mostleft part. */
	void Tetromino::setActualBlocks() {
		while (isTopRowEmpty()) shiftActualBlocksToUp();
		while (isLeftColEmpty()) shiftActualBlocksToLeft();
	}

}

