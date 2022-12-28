#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Tetromino.h"
#include "AbstractTetris.h"
#include "TetrisVector.h"
#include "TetrisArray1D.h"
#include "TetrisAdapter.cpp"
using namespace std;
using namespace GTUTetris;

Tetromino randomTetromino() {
	
	Tetromino randomTet;
	int randomNum = (int)rand() % 7; 
	switch(randomNum) {
	
		case 0 :
			randomTet.changeType(Tetromino_t::I);
			break;
			
		case 1 :
			randomTet.changeType(Tetromino_t::O);
			break;
			
		case 2 : 
			randomTet.changeType(Tetromino_t::L);
			break;
			
		case 3 : 
			randomTet.changeType(Tetromino_t::S);
			break;
			
		case 4 :
			randomTet.changeType(Tetromino_t::Z);
			break;
			
		case 5 :
			randomTet.changeType(Tetromino_t::J);
			break;
			
		case 6 :
			randomTet.changeType(Tetromino_t::T);
			break;
			
	
	}
	
	return randomTet;
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
	
	
	AbstractTetris* tetris = nullptr;
	char boardType = 'n';
	isRead = false;
	do {
		cout << "Enter Tetris Class Type (V - Vector, 1 - Array1D, A - Adaptor): ";
		cin >> boardType;
		
		switch (boardType) {
		
			case 'V':
				tetris = new TetrisVector(len, width);
				isRead = true;
				break;
				
			case '1':
				tetris = new TetrisArray1D(len, width);
				isRead = true;
				break;
				
			case 'A':
				tetris = new TetrisAdapter<deque>(len, width);
				isRead = true;
				break;
				
			default : 
				cout << "Enter a valid character such as (V - Vector, 1 - Array1D, A - Adaptor) \n";
		}
	
	}while (!isRead);
	
	
	bool isDone = false;
	while(!isDone) {
		isRead = true;
		char ch;
		cout << "Enter a tetromino (R - Random, Q- Quit) (Uppercase Only! (I,O,T,S,Z,L,J)) : ";
		cin >> ch;
		
		Tetromino curTet;
		
		switch (ch) {
			
				case 'I':
					curTet.changeType(Tetromino_t::I);
					break;
				
				case 'O' :
					curTet.changeType(Tetromino_t::O);
				 	break;
				 	
				case 'T' :
					curTet.changeType(Tetromino_t::T);
			 		break;
				 	
			 	case 'J' :
				 	curTet.changeType(Tetromino_t::J);
				 	break;
				
				case 'L' :
					curTet.changeType(Tetromino_t::L);
					break;
					
				case 'Z' :
					curTet.changeType(Tetromino_t::Z);
					break;
					
				case 'S' :
					curTet.changeType(Tetromino_t::S);
					break; 	
				
				case 'R' :
					curTet = randomTetromino();
					break;
					
				case 'Q' : 
					cout << "Goodbye!\n";
					isDone = true;
					isRead = false;
					break;
				
				default :
					cout << "Enter a valid input!\n";
					cin.clear();
					cin.ignore(256, '\n');
					isRead = false;
					break;
				 
			}
			
			if (isRead) {
				
				*tetris += curTet;
				
				if (tetris->gameStatus() == false) {
					cout << "Current tetromino : \n";
					curTet.print();
					cout << "\n";
					
					cout << "Current tetromino cannot be added at the top row in the middle !\n\n";
					
					cout << "The board : \n";
					tetris->draw();
				
					cout << "\nGAME OVER!\n";
					
					isDone = true;
					
				}
				
				else {
					tetris->animate();
				}
				
				cout << "\n";	
			}
	}
	
	if (tetris != nullptr) delete tetris;
	
	return 0;
}



