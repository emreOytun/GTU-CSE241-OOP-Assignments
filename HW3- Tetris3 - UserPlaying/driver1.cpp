#include <iostream>
#include "Tetromino.h"
#include "Tetris.h"
using namespace std;
using namespace GTUTetris;

int main() {
	cout << "\t\t **********  DRIVER - 1   ************ \n\n";
	
	cout << "*************************** TESTING PRINT AND ROTATE FUNCTIONS OF TETROMINO CLASS ****************** \n\n";

	cout << "--------------- I Tetromino : ------------------- \n";
	Tetromino tI(Tetromino_t::I);
	cout << "Print I Tetromino : \n";
	tI.print();
	cout << "\nRotate right and print I Tetromino : \n";
	tI.rotate(Direction_t::Right);
	tI.print();
	cout << "\n";	

	cout << "--------------- O Tetromino : ------------------- \n";
	Tetromino tO(Tetromino_t::O);
	cout << "Print O Tetromino : \n";
	tO.print();
	cout << "\nRotate right and print O Tetromino : \n";
	tO.rotate(Direction_t::Right);
	tO.print();
	cout << "\n";


	cout << "--------------- T Tetromino : ------------------- \n";
	Tetromino tT(Tetromino_t::T);
	cout << "Print T Tetromino : \n";
	tT.print();
	cout << "\nRotate right and print T Tetromino : \n";
	tT.rotate(Direction_t::Right);
	tT.print();
	cout << "\n";
	cout << "\nRotate right and print T Tetromino : \n";
	tT.rotate(Direction_t::Right);
	tT.print();
	cout << "\n";
	cout << "\nRotate right and print T Tetromino : \n";
	tT.rotate(Direction_t::Right);
	tT.print();
	cout << "\n";
		
	cout << "--------------- J Tetromino : ------------------- \n";	
	Tetromino tJ(Tetromino_t::J);
	cout << "Print J Tetromino : \n";
	tJ.print();
	cout << "\nRotate right and print J Tetromino : \n";
	tJ.rotate(Direction_t::Right);
	tJ.print();
	cout << "\n";
	cout << "\nRotate right and print J Tetromino : \n";
	tJ.rotate(Direction_t::Right);
	tJ.print();
	cout << "\n";
	cout << "\nRotate right and print J Tetromino : \n";
	tJ.rotate(Direction_t::Right);
	tJ.print();
	cout << "\n";
	
	
	cout << "--------------- L Tetromino : ------------------- \n";
	Tetromino tL(Tetromino_t::L);
	cout << "Print L Tetromino : \n";
	tL.print();
	cout << "\nRotate right and print L Tetromino : \n";
	tL.rotate(Direction_t::Right);
	tL.print();
	cout << "\n";
	cout << "\nRotate right and print L Tetromino : \n";
	tL.rotate(Direction_t::Right);
	tL.print();
	cout << "\n";
	cout << "\nRotate right and print L Tetromino : \n";
	tL.rotate(Direction_t::Right);
	tL.print();
	cout << "\n";
	
	cout << "--------------- S Tetromino : ------------------- \n";
	Tetromino tS(Tetromino_t::S);
	cout << "Print T Tetromino : \n";
	tS.print();
	cout << "\nRotate right and print S Tetromino : \n";
	tS.rotate(Direction_t::Right);
	tS.print();
	cout << "\n";
	cout << "\nRotate right and print S Tetromino : \n";
	tS.rotate(Direction_t::Right);
	tS.print();
	cout << "\n";
	cout << "\nRotate right and print S Tetromino : \n";
	tS.rotate(Direction_t::Right);
	tS.print();
	cout << "\n";
	
	cout << "--------------- Z Tetromino : ------------------- \n";
	Tetromino tZ(Tetromino_t::Z);
	cout << "Print T Tetromino : \n";
	tZ.print();
	cout << "\nRotate right and print Z Tetromino : \n";
	tZ.rotate(Direction_t::Right);
	tZ.print();
	cout << "\n";
	cout << "\nRotate right and print Z Tetromino : \n";
	tZ.rotate(Direction_t::Right);
	tZ.print();
	cout << "\n";
	cout << "\nRotate right and print Z Tetromino : \n";
	tZ.rotate(Direction_t::Right);
	tZ.print();
	cout << "\n";
	
		
	cout << "\n*************************** TESTING DRAW FUNCTION OF TETRIS CLASS WHEN BOARD IS EMPTY ****************** \n\n";
	const int length = 10;
	const int width = 10;
	
	Tetris tetris(length, width);
	cout << "TETRIS BOARD LENGTH*WIDTH = " << length << "*" << width << "\n\n";
	
	tetris.draw();
	cout << "\n";
	
	
	cout << "\n*************************** TESTING += OPERATOR OF TETRIS CLASS ************************ \n\n";
	Tetromino newTet(Tetromino_t::I);
	
	cout << "New Tetromino : \n";
	newTet.print();
	cout << "\n";
	
	tetris += newTet;
	cout << "Tetris Board After Adding New Tetromino : \n";
	tetris.draw();
	cout << "\n";
	
	Tetris tetris2(length, width);
	Tetromino newTet2(Tetromino_t::Z);
	
	cout << "New Tetromino : \n";
	newTet2.print();
	cout << "\n";
	
	tetris2 += newTet2;
	cout << "Tetris Board After Adding New Tetromino : \n";
	tetris2.draw();
	
	cout << "\n*************************** Since animate function gets input from user, you will be testing it in Driver2. ************************ \n\n";

	return 0;
}
