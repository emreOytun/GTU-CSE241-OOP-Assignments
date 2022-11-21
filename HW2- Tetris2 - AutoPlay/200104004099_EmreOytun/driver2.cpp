#include <iostream>
#include "Tetromino.h"
#include "Tetris.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

Tetromino randomTetromino() {
	vector<Tetromino_t> typeList {Tetromino_t::I, Tetromino_t::O, Tetromino_t::L, Tetromino_t::S, Tetromino_t::Z, Tetromino_t::J, Tetromino_t::T};
	int randomNum = (int)rand() % 7; 
	
	return Tetromino(typeList.at(randomNum));
}

int main() {
	srand(time(NULL));
	
	cout << "\t\t ********* DRIVER - 2 ******** \n\n";
	
	int len = 0;
	int width = 0;
	
	
	/* Get the length of board. */
	bool isRead = false;
	do {
		cout << "Enter board length : ";
		cin >> len;
	
		/* Check the validity of the input. */
		if (cin.fail()) {
			cout << "Enter a valid input!\n";
			cin.clear();
			cin.ignore(256, '\n');	// Ignore the stream.
		}
		else if (len<0) cout << "Enter a positive number!\n";
		else isRead = true;
				
	}while (!isRead);
	
	/* Get the width of board. */
	isRead = false;
	do {
		cout << "Enter board width : ";
		cin >> width;
	
		/* Check the validity of the input. */
		if (cin.fail()) {
			cout << "Enter a valid input!\n";
			cin.clear();
			cin.ignore(256, '\n');	// Ignore the stream.
		}
		else if (width<0) cout << "Enter a positive number!\n";
		else isRead = true;
				
	}while (!isRead);
	
	/* Initialize a Tetris instance with given board parameters. */
	Tetris tetris(len, width);
	
	bool isDone = false;
	while(!isDone) {
		isRead = true;
		char ch;
		cout << "Enter a tetromino (R - Random) : ";
		cin >> ch;
		vector<Tetromino> tlist;
		
		switch (ch) {
			
				case 'I':
					tlist.push_back(Tetromino(Tetromino_t::I));
					break;
				
				case 'O' :
					tlist.push_back(Tetromino(Tetromino_t::O));
				 	break;
				 	
				case 'T' :
				 	tlist.push_back(Tetromino(Tetromino_t::T));
			 		break;
				 	
			 	case 'J' :
				 	tlist.push_back(Tetromino(Tetromino_t::J));
				 	break;
				
				case 'L' :
					tlist.push_back(Tetromino(Tetromino_t::L));
					break;
					
				case 'Z' :
					tlist.push_back(Tetromino(Tetromino_t::Z));
					break;
					
				case 'S' :
					tlist.push_back(Tetromino(Tetromino_t::S));
					break; 	
				
				case 'R' :
					tlist.push_back(randomTetromino());
					break;
				
				default :
					cout << "Enter a valid input!\n";
					cin.clear();
					cin.ignore(256, '\n');
					isRead = false;
					break;
				 
			}
			
			if (isRead) {
				Tetromino curTet = tlist[tlist.size()-1];
				
				tetris.add(curTet);
				
				if (tetris.gameStatus() == false) {
					cout << "Current tetromino : \n";
					curTet.print();
					cout << "\n";
					
					cout << "Current tetromino cannot be added at the top row in the middle !\n\n";
					
					cout << "The board : \n";
					tetris.draw();
				
					cout << "\nGAME OVER!\n";
					
					isDone = true;
				}
				
				else {
					tetris.animate();
				}
				
				cout << "\n";	
			}
	}
	
	return 0;
}



