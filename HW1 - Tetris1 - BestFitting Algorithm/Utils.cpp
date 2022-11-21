#include <iostream>
#include <vector>
#include <algorithm>
#include "Utils.h"
#include "Tetromino.h"
using namespace std;

/* Swaps two integer variables. */
void swap(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

vector<Tetromino> getTetrominoListFromUser() {
	
	int tNum = 0;
	bool isRead = false;
	do {
		cout << "How many tetrominos? \n";
		cin >> tNum;
		
		/* Check the validity of the input. */
		if (cin.fail()) {
			cout << "Enter a valid input!\n";
			cin.clear();
			cin.ignore(256, '\n');	// Ignore the stream.
		}
		else isRead = true;
				
	}while (!isRead);
	
	cout << "What are the types?\n";
	
	vector<Tetromino> tlist;
	char ch;
	for (int readTetrominos = 0; readTetrominos < tNum;) {
		cin >> ch;
		if (cin.fail()) {
			cout << "Enter a valid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
		}
		
		else {
		
			switch (ch) {
			
				case 'I':
					tlist.push_back(Tetromino(Tetromino_t::I));
					++readTetrominos;
					break;
				
				case 'O' :
					tlist.push_back(Tetromino(Tetromino_t::O));
				 	++readTetrominos;
				 	break;
				 	
				case 'T' :
				 	tlist.push_back(Tetromino(Tetromino_t::T));
			 		++readTetrominos;
			 		break;
				 	
			 	case 'J' :
				 	tlist.push_back(Tetromino(Tetromino_t::J));
				 	++readTetrominos;
				 	break;
				
				case 'L' :
					tlist.push_back(Tetromino(Tetromino_t::L));
					++readTetrominos;
					break;
					
				case 'Z' :
					tlist.push_back(Tetromino(Tetromino_t::Z));
					++readTetrominos;
					break;
					
				case 'S' :
					tlist.push_back(Tetromino(Tetromino_t::S));
					++readTetrominos;
					break; 	
					
				default :
					cout << "Enter a valid input!\n";
					cin.clear();
					cin.ignore(256, '\n');
					break;
				 
			}
		
		}
		
	}

	return tlist;
}


Map::Map(vector<Tetromino> list) {
	setMap(list);
}

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
			cout << ch;
		}
		cout << "\n";
	}
}

vector<Tetromino> TetrominoManager::findBestFitRec(vector<Tetromino> list, int idx) {
	if (idx >= list.size()) return list;
	
	vector< vector<Tetromino> > results;
	
	/* Rotate the tetromino at hand for this function, and send the new lists to the next functions. */
	results.push_back(findBestFitRec(list, idx+1));
	for (int i = 0; i < 3; ++i) {
		list[idx].rotate(Direction_t::Right);
		results.push_back(findBestFitRec(list, idx+1));	/* Save the results of the best lists coming from the next functions. */
	}

	/* Count the dead and total spaces of the results. */
	vector<int> deadSpaces(4, 0);
	vector<int> totalSpaces(4, 0);
	
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < list.size()-1; ++j) {
			auto res = results[i][j].findFittingIndexes_and_spaceNumbers_whenRight(results[i][j+1]);
			
			deadSpaces[i] += res.at(2);
			totalSpaces[i] += res.at(3);
		}
	}

	/* Determine which one is the best according to the dead space and total space numbers. */
	int min_i = 0;
	for (int i = 1; i < 4; ++i) {
		if (deadSpaces[i] < deadSpaces[min_i]) min_i = i;
		else if (deadSpaces[i] == deadSpaces[min_i] && totalSpaces[i] < totalSpaces[min_i]) min_i = i;
	}
	
	return results[min_i];
}

/* Put the incoming tetromino near the previous one in a best-fit position and do this until the end. */
vector<Tetromino> TetrominoManager::findBestFitLinear(vector<Tetromino> list) {
	/* First one in the list is fixed here */
	for (int i = 1; i < list.size(); ++i) {
		vector<int> deadSpaces(4, 0);
		vector<int> totalSpaces(4, 0);
		
		for (int j = 0; j < 4; ++j) {
			auto res = list[i-1].findFittingIndexes_and_spaceNumbers_whenRight(list[i]);
		
			deadSpaces[j] += res.at(2);
			totalSpaces[j] += res.at(3);
			list[i].rotate(Direction_t::Right);
		}
	
		int min_i = 0;
		for (int j = 1; j < 4; ++j) {
			if (deadSpaces[j] < deadSpaces[min_i]) min_i = j;
			else if (deadSpaces[j] == deadSpaces[min_i] && totalSpaces[j] < totalSpaces[min_i]) min_i = j;
		}
	
		for (int j = 0; j < min_i; ++j) {
			list[i].rotate(Direction_t::Right);
		}
	}
	
	return list;
}

/* This time rotate the first tetromino, get the linear best-fit results and compare them to find the best one between 4 results. */
vector<Tetromino> TetrominoManager::findBestBestFitLinear(vector<Tetromino> list) {
	vector<Tetromino> res;
	
	if (list.size() > 0) {
		vector< vector<Tetromino> > results;
		
		results.push_back(findBestFitLinear(list));
		for (int i = 0; i < 3; ++i) {
			list[0].rotate(Direction_t::Right);
			results.push_back(findBestFitLinear(list));
		}

		vector<int> deadSpaces(4, 0);
		vector<int> totalSpaces(4, 0);
		
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < list.size()-1; ++j) {
				auto res = results[i][j].findFittingIndexes_and_spaceNumbers_whenRight(results[i][j+1]);
				
				deadSpaces[i] += res.at(2);
				totalSpaces[i] += res.at(3);
			}
		}

		int min_i = 0;
		for (int i = 1; i < 4; ++i) {
			if (deadSpaces[i] < deadSpaces[min_i]) min_i = i;
			else if (deadSpaces[i] == deadSpaces[min_i] && totalSpaces[i] < totalSpaces[min_i]) min_i = i;
		}
		
		res = results[min_i];
	}	
		
	else res = list;
	
	return res;
}


/* Precondition : Get the tetromino list whose best-fit position will be found. */
/* Postcondition : Return the best-fit list. */
/* TO-DO : 
	1) Check the list size, if it's smaller than 6 then call the findBestFitRec function; call the findBestBestFitLinear function otherwise.
	TECHNICAL NOTE : This decision is made to prevent long time calculations when tetromino list is big.
	2) Return the coming result from the function called.
 */
vector<Tetromino> TetrominoManager::findTheBest(vector<Tetromino> list) {
	vector<Tetromino> res;
	
	if (list.size() < 6) res = TetrominoManager::findBestFitRec(list, 0);
	else {
		res = TetrominoManager::findBestBestFitLinear(list);
	}
	
	return res;
} 

