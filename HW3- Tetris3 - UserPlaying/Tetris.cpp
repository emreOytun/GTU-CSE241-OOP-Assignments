#include "Tetris.h"
#include "Tetromino.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

namespace {
	/* Reads the direction commands from user. */
	/* Direction name parameter is used for formatting purpose. */
	void readDirection(char& direction, const string& directionName) {
		bool isRead = false;
		do {
			cout << "\n";
			cout << "Enter " + directionName + " direction ('L' or 'l' for Left) ('R' or 'r' for Right) : ";
			cin >> direction;
		
			/* Check the validity of the input. */
			if (cin.fail()) {
				cout << "Enter a valid input!\n";
				cin.clear();
				cin.ignore(256, '\n');	// Ignore the stream.
			}
			else if (! (direction == 'R' || direction == 'r' || direction == 'L' || direction == 'l') ) cout << "WARNING: Enter only 'L','l' / 'R','r' !\n";
			else isRead = true;
					
		}while (!isRead);
	}
	
	/* Reads the counts from user. */
	/* Count name parameter is used for formatting purpose. */
	void readCount(int& count, const string& countName) {
		bool isRead = false;
		do {
			cout << "Enter " + countName + " count : ";
			cin >> count;
		
			/* Check the validity of the input. */
			if (cin.fail()) {
				cout << "Enter a valid input!\n";
				cin.clear();
				cin.ignore(256, '\n');	// Ignore the stream.
			}
			else if (count < 0) cout << "Rotate count cannot be negative !\n";
			else isRead = true;
					
		}while (!isRead);
	}
	
}

namespace GTUTetris {

	Tetris::Tetris(int rowNum, int colNum) : gameMap(rowNum, colNum), status(true), isCurTetrominoActive(false) {
		
	}
		
	/* 	1) Adjusts the new tetromino's position to be at the top row in the middle, and checks if it can be added to the map.
		2) If it can be added then new tetromino is active for game; if it's not then the new tetromino is not active.
	*/
	
	Tetris& Tetris::operator+=(const Tetromino& newTetromino) {
		curTetromino = newTetromino;

		/* Set the position of the tetromino to the middle of the game map. */
		curTetromino.setStartPosition(0, static_cast<int>( (gameMap.getColNum()-curTetromino.getActiveColNum()) / 2));
		
		if (!gameMap.canBeAdded(curTetromino)) {
			status = false;
			isCurTetrominoActive = false;
		}
		else isCurTetrominoActive = true;
		
		return *this;
	}


	/* Draws the board with the current tetromino if there is an active current tetromino, or draws the board without a new tetromino otherwise. */
	void Tetris::draw() {
		if (isCurTetrominoActive) {
			gameMap.addTetromino(curTetromino);
			gameMap.print();
			gameMap.deleteTetromino(curTetromino);
		}
		
		else {
			gameMap.print();
		}
	}

	void Tetris::draw() const {
		gameMap.print();
	}

	void Tetris::animate()  {
		if (!isCurTetrominoActive) return;
		
		cout << "\n**************************************************************************************************************************\n";
		cout << "IMPORTANT: When you rotate the tetromino take that into account that the leftmost coordinate of the tetromino is fixed.\n";
		cout << "**************************************************************************************************************************\n\n";
		
		/* Get rotate and move informations. */
		bool isDone = false;
		while (!isDone) {
			
			cout << "Current board : \n";
			draw();
			
			char rotateDirection;
			int rotateCount = 0;
			
			char moveDirection;
			int moveCount = 0;
			
			/* Copy current tetromino to check whether it can be rotated and moved in the given ways. */
			Tetromino copyTet = curTetromino;
			
			/* Read rotation infos from user. */
			//readRotateAndMove(rotateDirection, rotateCount, moveDirection, moveCount);
			readDirection(rotateDirection, "rotate");
			readCount(rotateCount, "rotate");
			cin.ignore(256, '\n');
			
			/* Rotate the tetromino. */
			Direction_t rotateDirection_t;
			if (rotateDirection == 'R' || rotateDirection == 'r') rotateDirection_t = Direction_t::Right;
			else if (rotateDirection == 'L' || rotateDirection == 'l') rotateDirection_t = Direction_t::Left;
			for (int i = 0; i < rotateCount; ++i) copyTet.rotate(rotateDirection_t);
			
			if (gameMap.canBeAdded(copyTet)) {
				
				/* Draw the map again for better user experience. */
				cout << "Game Board after rotation  : \n";
				gameMap.addTetromino(copyTet);
				gameMap.print();
				gameMap.deleteTetromino(copyTet);
				cout << "\n";
				
				/* Read movement infos from user. */
				readDirection(moveDirection, "move");
				readCount(moveCount, "move");
				cin.ignore(256, '\n');	
				
				int newYPos;
				if (moveDirection == 'R' || moveDirection == 'r') {
					newYPos = curTetromino.getStartY() + moveCount;
				}
				
				else if (moveDirection == 'L' || moveDirection == 'l') {
					newYPos = curTetromino.getStartY() - moveCount;
				}
				
				if (gameMap.checkHorizantalMovement(copyTet, newYPos)) { 
						curTetromino = copyTet;
						curTetromino.setStartY(newYPos);
						isDone = true;		
				}
				else cout << "WARNING: It cannot move '" + to_string(moveCount) + "' to given direction. Enter again...\n";
				
			}
			
			else cout << "WARNING: It cannot be rotated in that way. Enter again...\n";
			
		}
		
		bool isPlaced = false;
		while (!isPlaced) {
			cout << "\033[H\033[J";	// Clear the screen with escape sequences.
	
			draw();
			cout << "\n";
			
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			
			Tetromino copy = curTetromino;
			copy.lower();
			
			if (gameMap.canBeAdded(copy) == false) isPlaced = true;
			else curTetromino.lower();
		}
		
		/* Lastly, add the new tetromino to the board permanently. */
		gameMap.addTetromino(curTetromino);
	}

	bool Tetris::gameStatus() const { return status; }



	/*********************************** MAP CLASS **********************************/

	Map::Map(int rowNumber, int colNumber) : rowNum(rowNumber), colNum(colNumber), map(nullptr) {
		initMemory(rowNum, colNum);
	}

	Map::Map(const Map& oth) : rowNum(oth.rowNum), colNum(oth.colNum) {
		initMemory(rowNum, colNum);
		
		/* Copy the map characters one-by-one. */
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				map[i][j] = oth.map[i][j];
			}
		}
	}

	Map& Map::operator=(const Map& oth) {
		if (this == &oth) return *this;
		
		/* Delete the current memory. */
		if (map != nullptr) {
			for (int i = 0; i < rowNum; ++i) {
				if (map[i] != nullptr) {
					delete [] map[i];
					map[i] = nullptr;
				}
			}
			delete [] map;
			map = nullptr;
		}
		
		rowNum = oth.rowNum;
		colNum = oth.colNum;
		initMemory(oth.rowNum, oth.colNum);
		
		/* Copy the map one-by-one. */
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < colNum; ++j) {
				map[i][j] = oth.map[i][j];
			}
		}
		
		return *this;
	}

	Map::~Map() {
		if (map != nullptr) {
			for (int i = 0; i < rowNum; ++i) {
				if (map[i] != nullptr) {
					delete [] map[i];
					map[i] = nullptr;
				}
			}
			delete [] map;
			map = nullptr;
		}
	}

	int Map::getRowNum() const { return rowNum; }
	int Map::getColNum() const { return colNum; }

	void Map::print() const {
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
	bool Map::checkHorizantalMovement(const Tetromino& comingT, int newYPos) const {
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
	void Map::addTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = t[i][j];
			}
		}
	}

	/* It deletes the given tetromino from the map. */
	void Map::deleteTetromino(const Tetromino& t) {
		
		for (int i = 0; i < t.getActiveRowNum(); ++i) {
			for (int j = 0; j < t.getActiveColNum(); ++j) {
				if (t[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = ' ';
			}
		}
		
	}

	/* It checks if a given tetromino can be added to the map. */
	bool Map::canBeAdded(const Tetromino& t) const {
		
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

	void Map::initMemory(int rowSize, int colSize) {
		map = new char*[rowSize];
		
		for (int i = 0; i < rowSize; ++i) {
			map[i] = new char[colSize];
			for (int j = 0; j < colSize; ++j) {
				map[i][j] = ' ';
			}
		}
	}

}


