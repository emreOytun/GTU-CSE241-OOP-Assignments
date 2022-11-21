#include <iostream>
#include "Tetromino.h"
#include "Tetris.h"
using namespace std;

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
	
	cout << "\n*************************** TESTING CANFIT FUNCTION OF TETROMINO CLASS ****************** \n\n";
	
	Tetromino t1(Tetromino_t::O);
	Tetromino t2(Tetromino_t::Z);
	
	cout << "1st tetromino : \n";
	t1.print();
	cout << "\n";
	
	cout << "2nd tetromino : \n";
	t2.print();
	cout << "\n";
	
	cout << "Canfit function result when putting 1st tet. right to 2nd tet. (1-true, 0-false): " << t1.canFit(t2, Direction_t::Right) << "\n\n";
	
	cout << "1st tetromino : \n";
	t1.print();
	cout << "\n";
	
	cout << "2nd tetromino : \n";
	t2.rotate(Direction_t::Right);
	t2.print();
	cout << "\n";
	
	cout << "Canfit function result when putting 1st tet. right to 2nd tet. (1-true, 0-false): " << t1.canFit(t2, Direction_t::Right) << "\n\n";
	
	Tetromino t3(Tetromino_t::S);
	
	cout << "1st tetromino : \n";
	t1.print();
	cout << "\n";
	
	cout << "2nd tetromino : \n";
	t3.print();
	cout << "\n";
	
	cout << "Canfit function result when putting 1st tet. right to 2nd tet. (1-true, 0-false): " << t1.canFit(t3, Direction_t::Right) << "\n\n";
	
	
	cout << "\n*************************** TESTING DRAW FUNCTION OF TETRIS CLASS WHEN BOARD IS EMPTY ****************** \n\n";
	const int length = 10;
	const int width = 10;
	
	Tetris tetris(length, width);
	cout << "TETRIS BOARD LENGTH*WIDTH = " << length << "*" << width << "\n\n";
	
	tetris.draw();
	cout << "\n";
	
	
	cout << "\n*************************** TESTING ADD FUNCTION OF TETRIS CLASS ************************ \n\n";
	Tetromino newTet(Tetromino_t::I);
	
	cout << "New Tetromino : \n";
	newTet.print();
	cout << "\n";
	
	tetris.add(newTet);
	cout << "Tetris Board After Adding New Tetromino : \n";
	tetris.draw();
	cout << "\n";
	
	Tetris tetris2(length, width);
	Tetromino newTet2(Tetromino_t::Z);
	
	cout << "New Tetromino : \n";
	newTet2.print();
	cout << "\n";
	
	tetris2.add(newTet2);
	cout << "Tetris Board After Adding New Tetromino : \n";
	tetris2.draw();
	cout << "\n";
	
	cout << "\n*************************** TESTING FIT FUNCTION OF TETRIS CLASS ************************* \n\n";
	
	cout << "Added Tetromino : \n";
	newTet.print();
	cout << "\n";
	
	cout << "Tetris Board After Fitting New Tetromino At The Top : \n";
	tetris.fit();
	tetris.draw();
	cout << "\n";
	
	cout << "Added Tetromino : \n";
	newTet2.print();
	cout << "\n";
	
	cout << "Tetris Board After Fitting New Tetromino At The Top : \n";
	tetris2.fit();
	tetris2.draw();
	cout << "\n\n";
	
	cout << "\n*************************** TESTING ANIMATE FUNCTION OF TETRIS CLASS ************************* \n\n";
	
	cout << "\n ******* ANIMATE TEST - 1 : ************ \n";
	cout << "Tetromino list will be sent to animate : L, S, T, Z, O, I, I, L, J, T, T, S, Z, I, J, J, L, J, I, S, Z, O \n";
	cout << "Press Any Character to Test Animate Function : ";
	char ch;
	cin >> ch;
	
	Tetris animateTetris(10, 10);
	vector<Tetromino> tetrominoList {Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::S), Tetromino(Tetromino_t::T), Tetromino(Tetromino_t::Z), Tetromino(Tetromino_t::O), Tetromino(Tetromino_t::I),
				Tetromino(Tetromino_t::I), Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::T), Tetromino(Tetromino_t::T), Tetromino(Tetromino_t::S),
				Tetromino(Tetromino_t::Z), Tetromino(Tetromino_t::I), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::J),
				Tetromino(Tetromino_t::I), Tetromino(Tetromino_t::S), Tetromino(Tetromino_t::Z), Tetromino(Tetromino_t::O)
	};
	
	bool isDone = false;
	for (int i = 0; i < tetrominoList.size() && !isDone; ++i) {
		
		Tetromino& tet = tetrominoList[i];
		animateTetris.add(tet);
			
		if (animateTetris.gameStatus() == false) {
			cout << "\n ******* ANIMATE TEST - 1 : ************ \n";
	
			cout << "Current tetromino : \n";
			tet.print();
			cout << "\n";
			
			cout << "Current tetromino cannot be added at the top row in the middle !\n\n";
			
			cout << "The board : \n";
			animateTetris.draw();
		
			cout << "\nGAME OVER!\n";
			
			isDone = true;
		}
		
		else {
			animateTetris.animate();
		}	
	}
	
	
	cout << "\n ******* ANIMATE TEST - 2 : ************ \n";
	cout << "Tetromino list will be sent to animate : O, J, L, S, Z, T, L, J, S, O, T, Z, J, I, L, J, O, S \n";
	cout << "Press Any Character to Test Animate Function : ";
	cin >> ch;
	
	animateTetris = Tetris(10, 8);
	vector<Tetromino>tetrominoList2 {
						Tetromino(Tetromino_t::O), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::S), Tetromino(Tetromino_t::Z), Tetromino(Tetromino_t::T),
						Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::S), Tetromino(Tetromino_t::O), Tetromino(Tetromino_t::T), Tetromino(Tetromino_t::Z),
						Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::I), Tetromino(Tetromino_t::L), Tetromino(Tetromino_t::J), Tetromino(Tetromino_t::O), Tetromino(Tetromino_t::S)
					};
	
	isDone = false;
	for (int i = 0; i < tetrominoList2.size() && !isDone; ++i) {
		
		Tetromino& tet = tetrominoList2[i];
		animateTetris.add(tet);
			
		if (animateTetris.gameStatus() == false) {
			cout << "\n ******* ANIMATE TEST - 2 : ************ \n";
	
			cout << "Current tetromino : \n";
			tet.print();
			cout << "\n";
			
			cout << "Current tetromino cannot be added at the top row in the middle !\n\n";
			
			cout << "The board : \n";
			animateTetris.draw();
		
			cout << "\nGAME OVER!\n";
			
			isDone = true;
		}
		
		else {
			animateTetris.animate();
		}	
	}
	
	cout << "\n\n";
	
	

	return 0;
}
