#include "Tetris.h"
#include "Tetromino.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

Tetris::Tetris(int rowNum, int colNum) : gameMap(rowNum, colNum), status(true), isCurTetrominoActive(false) {
	
}
	
/* 	1) Adjusts the new tetromino's position to be at the top row in the middle, and checks if it can be added to the map.
	2) If it can be added then new tetromino is active for game; if it's not then the new tetromino is not active.
*/
void Tetris::add(const Tetromino& newTetromino) {
	curTetromino = newTetromino;

	/* Set the position of the tetromino to the middle of the game map. */
	int gameMap_middle_col = static_cast<int>(gameMap.getColNum()/2);
	int curTetromino_startCol = gameMap_middle_col - static_cast<int>(curTetromino.getActiveColNum()/2);
	curTetromino.setStartPosition(0, curTetromino_startCol);
	
	if (!gameMap.canBeAdded(curTetromino)) {
		status = false;
		isCurTetrominoActive = false;
	}
	else isCurTetrominoActive = true;
}

/* Finds the best fit of the current tetromino and sets its column to that position. */
void Tetris::fit() {

	if (isCurTetrominoActive) {
		Tetromino fittingTetromino = findBestFitToMap(curTetromino);

		/* Save the fitting results. */
		curTetromino_fittingX = fittingTetromino.getStartX();
		curTetromino_fittingY = fittingTetromino.getStartY();
		
		curTetromino = fittingTetromino;
		curTetromino.setStartPosition(0, curTetromino_fittingY);
	}
	
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

	draw();
	fit();
	
	int rightShiftNumber = 0;
	int leftShiftNumber = 0;
	
	bool isPlaced = false;
	while (!isPlaced) {
		/* Add the temporary tetromino to the map, draw the map, and delete it from the map. */
		cout << "\033[H\033[J";	// Clear the screen with escape sequences.
		draw();
		cout << "\n";
		
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		
		if (curTetromino.getStartX() == curTetromino_fittingX && curTetromino.getStartY() == curTetromino_fittingY) isPlaced = true;
		else {
			/* Lower the tetromino when it is not its ideal position at the bottom. */
			if (curTetromino.getStartX() < curTetromino_fittingX) curTetromino.lower();
			
			/* If tetromino has gone to the right before, try to shift it toward left. */
			if (rightShiftNumber > 0) {
				bool isDone = false;
				while (!isDone) {
					curTetromino.goLeft();
					if (gameMap.canBeAdded(curTetromino)) --rightShiftNumber;
					else {
						curTetromino.goRight();
						isDone = true;
					}
				}
			}
			
			/* If tetromino has gone to the left before, try to shift it toward right. */
			if (leftShiftNumber > 0) {
				bool isDone = false;
				while (!isDone) {
					curTetromino.goRight();
					if (gameMap.canBeAdded(curTetromino)) --leftShiftNumber;
					else {
						curTetromino.goLeft();
						isDone = true;
					} 
				}
			}
			
			/* If tetromino cannot be placed, shift it to the right or left. */
			if (!gameMap.canBeAdded(curTetromino)) {
				curTetromino.goRight();
				++rightShiftNumber;
				
				if (!gameMap.canBeAdded(curTetromino)) {
					curTetromino.goLeft();
					--rightShiftNumber;
					
					curTetromino.goLeft();
					++leftShiftNumber;
				}
			}
		}
	}
	
	/* Lastly, add the new tetromino to the board permanently. */
	gameMap.addTetromino(curTetromino);
	addedTetrominos.push_back(curTetromino);
}

bool Tetris::gameStatus() const { return status; }

/* Finds the best rotate and position of the new incoming tetromino. */
/* 1) Rotate the tetromino in 4 ways, then save the position and space number results coming from the Map for each rotation. */
/* 2) Compare the result, and select the best one. */
Tetromino Tetris::findBestFitToMap(Tetromino t) {
	vector<int> deadSpaces;
	vector<int> totalSpaces;
	vector< vector<int> > positions;
	vector<int> bottomY;
	vector<int> bottomX;
	vector<Tetromino> resTetrominos;
	
	for (int i = 0; i < 4; ++i) {
		auto res = gameMap.getFittingIndex_and_spaceNumbers(t);
			
			deadSpaces.push_back(res[2]);
			totalSpaces.push_back(res[3]);
			
			vector<int> newPositions{res[0], res[1]};
			positions.push_back(newPositions);
			bottomY.push_back(res[1] + t.getLeftMostBottomIndexes().at(1));
			bottomX.push_back(res[0]+(t.getActiveRowNum()-1));
			resTetrominos.push_back(t);
			
			t.rotate(Direction_t::Right);
		
	}
	
	int min_i = 0;
	
	for (int i = 1; i < positions.size(); ++i) {
		if (deadSpaces[i] < deadSpaces[min_i]) min_i = i;
		else if (deadSpaces[i] == deadSpaces[min_i] && bottomX[i] > bottomX[min_i]) min_i = i; 
		else if (deadSpaces[i] == deadSpaces[min_i] && bottomX[i] == bottomX[min_i] && totalSpaces[i] < totalSpaces[min_i]) min_i = i; 
	}
	
	resTetrominos[min_i].setStartPosition(positions[min_i][0], positions[min_i][1]);
	return resTetrominos[min_i];
}




/*********************************** MAP CLASS **********************************/

Map::Map(int rowNumber, int colNumber) : rowNum(rowNumber), colNum(colNumber), map(rowNumber, vector<char>(colNumber, ' ')) {
	
}

Map::Map(vector<Tetromino> list) {
	setMap(list);
}


int Map::getRowNum() const { return rowNum; }
int Map::getColNum() const { return colNum; }

/* When a list of tetrominos given, find their horizantal optimal positions and create new map with these tetrominos in it. */
void Map::setMap(vector<Tetromino> list) {
	/* Calculate the map width and length. */
	int width = 0;
	int length = 0;
	for (auto t : list) {
		width += t.getActiveColNum();
		length = max(length, t.getActiveRowNum());
	}

	vector< vector<char> > newMap(length, vector<char>(width, ' '));

	/* Determine the starting positions of tetrominos. */
	if (list.size() > 0) {

		list[0].setStartPosition(length-list[0].getActiveRowNum(), 0);
		
		for (int i = 0; i < list.size()-1; ++i) {
			auto fittingRes = list[i].findFittingIndexes_and_spaceNumbers_whenRight(list[i+1]);
			list[i+1].setStartPosition(fittingRes.at(0), fittingRes.at(1));
		
		}
		
	}

	/* Render the map. */
	for (auto t : list) {
		
		auto v = t.getBlock();
		for (int i = 0; i < v.size(); ++i) {
			for (int j = 0; j < v[i].size(); ++j) {
				int realX = i + t.getStartX();
				int realY = j + t.getStartY();
				if (realX >= 0 && realX < length && realY >= 0 && realY < width && v[i][j] != ' ') {
					newMap[realX][realY] = v[i][j];
				}
			}
		}
	}
	
	map = newMap;
}


void Map::print() const {
	for (auto line : map) {
		for (auto ch : line) {
			if (ch == ' ') cout << "*";
			else cout << ch;
		}
		cout << "\n";
	}
}

/* Count the total spaces between two horizantal piece of block. */
int Map::countTotalSpaces() const {
	int totalSpaces = 0;
	int spaces = 0;
		
	for (int i = 0; i < rowNum; ++i) {
		
		bool canCount = false;
		spaces = 0;
		int j = 0;
		while (j < colNum) {
			if (map[i][j] != ' ') {		
				if (canCount) {
					totalSpaces += spaces;
					spaces = 0;
				}
				canCount = true;
			}	
				
			else {
				if (canCount) {
					++spaces;
				}
			}
			
			++j;
		} 
	}
	
	return totalSpaces;
}

/* Count the dead(useless) spaces in the map. */
int Map::countDeadSpaces() const {
	int deadSpaces = 0;
	
	for (int i = 0; i < map[0].size(); ++i) {
		bool canCount = false;
		int j = 0;
		while (j < map.size()) {
			if (map[j][i] != ' ') {
				canCount = true;
			}
			else if (canCount)  {
				++deadSpaces;	
			}
		
			++j;
		}
	}

	return deadSpaces;
}

/* Add the incoming active block to the map. */
void Map::addActiveBlock(const vector< vector<char> >& block, int start_x, int start_y) {
	for (int i = 0; i < block.size(); ++i) {
		for (int j = 0; j < block[i].size(); ++j) {
			if (block[i][j] != ' ') map[i+start_x][j+start_y] = block[i][j];
		}
	}
}

/* When finding a best fit of a given tetromino to put onto map, this function is used to check if it can be placed when tetromino lowers step-by-step. */
bool Map::checkVerticalFitting(Tetromino newT, int newT_fittingX, int newT_fittingY) const {
	
	newT.setStartPosition(0, newT_fittingY);
	
	int rightShiftNumber = 0;
	int leftShiftNumber = 0;
		
	bool isDone = false;
	bool result = false;
	while (!isDone) {
		
		if (newT.getStartX() == newT_fittingX && newT.getStartY() == newT_fittingY) {
			result = true;
			isDone = true;	
		}
		
		else {
			/* Lower the tetromino when it is not its ideal position at the bottom. */
			if (newT.getStartX() < newT_fittingX) {
				newT.lower();
				if (newT.getStartX() == newT_fittingX && !canBeAdded(newT)) {
					result = false;
					isDone = true;
				}
			}
			
			/* If tetromino has gone to the right before, try to shift it toward left. */
			if (!isDone && rightShiftNumber > 0) {
				bool isDone = false;
				while (!isDone) {	/* DUZENLEEEEEEEEE !!!!!!!!! */
					newT.goLeft();
					if (canBeAdded(newT)) --rightShiftNumber;
					else {
						newT.goRight();
						isDone = true;
					}
				}
			}
			
			/* If tetromino has gone to the left before, try to shift it toward right. */
			if (!isDone && leftShiftNumber > 0) {
				bool isDone = false;
				while (!isDone) {
					newT.goRight();
					if (canBeAdded(newT)) --leftShiftNumber;
					else {
						newT.goLeft();
						isDone = true;
					} 
				}
			}
			
			/* If tetromino cannot be placed, try to shift it to the right or left; if it cannot be shifted toward both way then it cannot be placed in that form, so return false. */
			if (!isDone && !canBeAdded(newT)) {
				
				newT.goRight();
				++rightShiftNumber;
				if (!canBeAdded(newT)) {
					newT.goLeft();
					--rightShiftNumber;
					
					newT.goLeft();
					++leftShiftNumber;
					if (!canBeAdded(newT)) {
						newT.goRight();
						--leftShiftNumber;
						
						result = false;
						isDone = true;
					}
				}	
			}
		}
	}
	
	return result;
}

/* When finding a best fit of a given tetromino to put onto map, this function is used to check if it can be shifted horizantally when tetromino lowers step-by-step. */
bool Map::checkHorizantalFitting(Tetromino newT, int newT_fittingY) const {
	int gameMap_middle_col = static_cast<int>(getColNum()/2);
	int start_y = gameMap_middle_col - static_cast<int>(newT.getActiveColNum()/2);
				
	newT.setStartY(start_y);
	newT.setStartX(0);
	
	bool isPlaced = false;
	bool isDone = false;
	
	
	while (!isPlaced && !isDone) {
		if (newT.getStartY() == newT_fittingY) isPlaced = true;
		
		else {
		
			if (newT_fittingY < start_y) newT.goLeft();
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
	
	return isPlaced;
	
}

/* This function is used to find the best place where the given new tetromino can be placed. */
vector<int> Map::getFittingIndex_and_spaceNumbers(const Tetromino& newT) const {
	
	vector< vector<char> > block = newT.getBlock();
	int activeRow = newT.getActiveRowNum();
	int activeCol = newT.getActiveColNum();
	
	vector<int> deadSpaces;
	vector<int> totalSpaces;
	vector< vector<int> > positions;
	
	
	/* i -> col position of the block. */
	bool isFitted = false;
	for (int i = 0; i+activeCol <= colNum; ++i) {
		isFitted = false;
		/* Put the tetromino at the bottom, and shift it above step-by-step until it can be placed. */
		for (int j = rowNum-activeRow; j>=0 && !isFitted ;--j) {
			bool isCollide = false;
			/* Block ile map collision var mi diye cek edicek.*/
			for (int k = 0; k < block.size() && !isCollide; ++k) {
				for (int z = 0; z < block[k].size() && !isCollide; ++z) {
					if (block[k][z] != ' ' && map[j+k][i+z] != ' ') isCollide = true; 
				}
			}
			
			Tetromino t = newT;
		
			if (!isCollide && checkHorizantalFitting(t, i) && checkVerticalFitting(t, j, i) ) {
				
				Map copy = *this;
				copy.addActiveBlock(block, j, i);
					
				deadSpaces.push_back(copy.countDeadSpaces());
				totalSpaces.push_back(copy.countTotalSpaces());
				positions.push_back(vector<int>{j, i});
				
				
				isFitted = true;
			}
		}
	} 
	
	if (positions.size() == 0) return vector<int> {Map::CANNOT_FIT_TETROMINO_X_VALUE, 10000, 10000, 10000};
	
	
	int min_i = 0;
	
	for (int i = 1; i < positions.size(); ++i) {
		if (deadSpaces[i] < deadSpaces[min_i]) min_i = i;
		else if (deadSpaces[i] == deadSpaces[min_i] && positions[i][0] > positions[min_i][0]) min_i = i; 
		else if (deadSpaces[i] == deadSpaces[min_i] && positions[i][0] == positions[min_i][0] && totalSpaces[i] < totalSpaces[min_i]) min_i = i; 
	}
	
	return vector<int> {positions[min_i][0], positions[min_i][1], deadSpaces[min_i], totalSpaces[min_i]};
}

/* It adds the given tetromino to the map. */
void Map::addTetromino(const Tetromino& t) {
	auto block = t.getBlock();
	
	for (int i = 0; i < t.getActiveRowNum(); ++i) {
		for (int j = 0; j < t.getActiveColNum(); ++j) {
			if (block[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = block[i][j];
		}
	}
}

/* It deletes the given tetromino from the map. */
void Map::deleteTetromino(const Tetromino& t) {
	auto block = t.getBlock();
	
	for (int i = 0; i < t.getActiveRowNum(); ++i) {
		for (int j = 0; j < t.getActiveColNum(); ++j) {
			if (block[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = ' ';
		}
	}
	
}

/* It checks if a given tetromino can be added to the map. */
bool Map::canBeAdded(const Tetromino& t) const {
	auto blocks = t.getBlock();
	
	int start_x = t.getStartX();
	int start_y= t.getStartY();
	
	bool canAdded = true;
	for (int i = 0; i < t.getActiveRowNum() && canAdded; ++i) {
		for (int j = 0; j < t.getActiveColNum() && canAdded; ++j) {
			if (i+start_x<0 || i+start_x>=rowNum || j+start_y<0 || j+start_y>=colNum)	canAdded = false;

			if (i+start_x>=0 && i+start_x<rowNum && j+start_y>=0 && j+start_y<colNum && map[i+start_x][j+start_y] != ' ' && blocks[i][j] != ' ') canAdded = false; 		
		}
	}

	return canAdded;
}



