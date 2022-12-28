#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "AbstractTetris.h"
#include "Tetromino.h"
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

	AbstractTetris::AbstractTetris(int rowNumber, int colNumber) : rowNum(rowNumber), colNum(colNumber), status(true), isCurTetrominoActive(false), totalMoves(0) {
		if (rowNumber < 0 || colNumber < 0) {
			throw invalid_argument("Arguments row number: " + to_string(rowNumber) + " col number: " + to_string(colNumber) + " are invalid.");
		}
	}
		
	/* 	1) Adjusts the new tetromino's position to be at the top row in the middle, and checks if it can be added to the map.
		2) If it can be added then new tetromino is active for game; if it's not then the new tetromino is not active.
	*/
	void AbstractTetris::operator+=(const Tetromino& newTetromino) {
		curTetromino = newTetromino;

		/* Set the position of the tetromino to the middle of the game map. */
		curTetromino.setStartPosition(0, static_cast<int>( (colNum-curTetromino.getActiveColNum()) / 2));
		
		if (!canBeAdded(curTetromino)) {
			status = false;
			isCurTetrominoActive = false;
		}
		else isCurTetrominoActive = true;
		
	}


	/* Draws the board with the current tetromino if there is an active current tetromino, or draws the board without a new tetromino otherwise. */
	void AbstractTetris::draw() {
		if (isCurTetrominoActive) {
			addTetromino(curTetromino);
			print();
			deleteTetromino(curTetromino);
		}
		
		else {
			print();
		}
	}

	void AbstractTetris::draw() const {
		print();
	}

	void AbstractTetris::animate()  {
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
			
			if (canBeAdded(copyTet)) {
				
				/* Draw the map again for better user experience. */
				cout << "Game Board after rotation  : \n";
				addTetromino(copyTet);
				print();
				deleteTetromino(copyTet);
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
				
				if (checkHorizantalMovement(copyTet, newYPos)) { 
					curTetromino = copyTet;
					curTetromino.setStartY(newYPos);
					isDone = true;		
					totalMoves += moveCount;	/* Add the valid move count to the total moves. */	
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
			
			if (canBeAdded(copy) == false) isPlaced = true;
			else {
				curTetromino.lower();
				++totalMoves;	/* When tetromino lowers one step, increment total moves count. */
			}
		}
		
		/* Lastly, add the new tetromino to the board permanently. */
		addTetromino(curTetromino);
	}

	bool AbstractTetris::gameStatus() const noexcept { return status; }
	
	int AbstractTetris::numberOfMoves() const noexcept { return totalMoves; }
	
	const Tetromino& AbstractTetris::lastMove() const { 
		if (totalMoves == 0) {
			throw runtime_error("There are no moves in the board.");
		}
		
		return curTetromino;
	}
	
	void AbstractTetris::writeToFile(ofstream& ostream) const {
		
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
		
		if (status) ostream << "status: 1\n";
		else ostream << "status: 0\n";
		
		ostream << "totalMoves: " << totalMoves << "\n";
		
		if (isCurTetrominoActive) ostream << "isCurTetrominoActive: 1\n";
		else ostream << "isCurTetrominoActive: 0\n";
		
		ostream << "rowNum: " << rowNum << "\n";
		ostream << "colNum: " << colNum << "\n";
		
		curTetromino.writeToFile(ostream);
				
	}
	
	void AbstractTetris::readFromFile(ifstream& ifstream) {
		string buff;
		int num;
		
		ifstream >> buff;			// status:
		ifstream >> num;			// 1
		if (num == 1) status = true;
		else status = false;
		
		ifstream >> buff;			// totalMoves:
		ifstream >> totalMoves;		// 20
		
		ifstream >> buff;			// isCurTetrominoActive:
		ifstream >> num;			// 0
		if (num == 1) isCurTetrominoActive = true;
		else isCurTetrominoActive = false;
		
		ifstream >> buff;			// rowNum:
		ifstream >> rowNum;			// 10
		
		ifstream >> buff;			// colNum;
		ifstream >> colNum;			// 5
		
		curTetromino.readFromFile(ifstream);
		
	}
	
}


