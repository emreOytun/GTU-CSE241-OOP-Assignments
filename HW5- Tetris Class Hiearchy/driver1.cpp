#include <iostream>
#include <deque>
#include <stdexcept>
#include "Tetromino.h"
#include "TetrisVector.h"
#include "TetrisArray1D.h"
#include "TetrisAdapter.cpp"

using namespace std;
using namespace GTUTetris;
using std::deque;

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
	
		
	cout << "\n*************************** TESTING CONSTRUCTORS AND DRAW FUNCTIONS OF TETRIS CLASSES WHEN BOARDS ARE EMPTY ****************** \n\n";
	const int length = 10;
	const int width = 10;
	
	cout << "TETRIS BOARDLENGTH*WIDTH = " << length << "*" << width << "\n\n";
	
	cout << "TETRIS VECTOR Constructor and Draw Function Testing: \n";
	TetrisVector tetrisVector1(length, width);
	tetrisVector1.draw();
	cout << "\n";
	
	cout << "TETRIS ARRAY Constructor and Draw Function Testing: \n";
	TetrisArray1D tetrisArray1(length, width);
	tetrisArray1.draw();
	cout << "\n";
	
	cout << "TETRIS ADAPTER Constructor and Draw Function Testing: \n";
	TetrisAdapter<deque> tetrisAdapter1(length, width);
	tetrisAdapter1.draw();
	cout << "\n\n";
	
	try {
		cout << "TETRIS VECTOR Constructor Testing: \n";
		cout << "Expected Result: Invalid_argument exception. \n";
		TetrisVector tetrisVectorTest(-2, -3);
	} catch (const invalid_argument& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	try {
		cout << "TETRIS ARRAY Constructor Testing: \n";
		cout << "Expected Result: Invalid_argument exception. \n";
		TetrisArray1D tetrisArrayTest(-2, -3);
	} catch (const invalid_argument& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	try {
		cout << "TETRIS VECTOR Constructor Testing: \n";
		cout << "Expected Result: Invalid_argument exception. \n";
		TetrisAdapter<deque> tetrisAdapterTest(-2, -3);
	} catch (const invalid_argument& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	cout << "\n*************************** TESTING NUMBER OF MOVES AND LASTMOVE FUNCTIONS WHEN NO TETROMINO ADDED TO THE BOARDS ************************* \n\n";
	
	cout << "TETRIS VECTOR Number Of Moves Function Testing : \n";
	cout << "Expected Result: 0 \n";
	cout << "Result: " << tetrisVector1.numberOfMoves() << "\n\n";
	
	try {
		cout << "TETRIS VECTOR Last Move Function Testing : \n";
		cout << "Expected Result: Throws Exception \n";
		cout << "Result: ";
		tetrisVector1.lastMove().print();
		cout << "\n";
	} catch(const runtime_error& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	cout << "TETRIS ARRAY Number Of Moves Function Testing : \n";
	cout << "Expected Result: 0 \n";
	cout << "Result: " << tetrisArray1.numberOfMoves() << "\n\n";
	
	try {
		cout << "TETRIS ARRAY Last Move Function Testing : \n";
		cout << "Expected Result: Throws Exception \n";
		cout << "Result: ";
		tetrisArray1.lastMove().print();
		cout << "\n";
	} catch(const runtime_error& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	cout << "TETRIS ADAPTER Number Of Moves Function Testing : \n";
	cout << "Expected Result: 0 \n";
	cout << "Result: " << tetrisAdapter1.numberOfMoves() << "\n\n";
	
	try {
		cout << "TETRIS ADAPTER Last Move Function Testing : \n";
		cout << "Expected Result: Throws Exception \n";
		cout << "Result: ";
		tetrisAdapter1.lastMove().print();
		cout << "\n";
	} catch(const runtime_error& e) {
		cout << "EXCEPTION: " << e.what();
	}
	cout << "\n\n";
	
	cout << "\n*************************** TESTING += OPERATOR AND DRAW FUNCTION OF TETRIS CLASSES ************************ \n\n";
	Tetromino newTet(Tetromino_t::I);
	
	cout << "New Tetromino : \n";
	newTet.print();
	cout << "\n";
	
	tetrisVector1 += newTet;
	cout << "TETRIS VECTOR Board After Adding New Tetromino : \n";
	tetrisVector1.draw();
	cout << "\n";
	
	tetrisArray1 += newTet;
	cout << "TETRIS ARRAY Board After Adding New Tetromino : \n";
	tetrisArray1.draw();
	cout << "\n";
	
	tetrisAdapter1 += newTet;
	cout << "TETRIS ADAPTER Board After Adding New Tetromino : \n";
	tetrisAdapter1.draw();
	cout << "\n\n";
	
	TetrisVector tetrisVector2(length, width);
	TetrisArray1D tetrisArray2(length, width);
	TetrisAdapter<deque> tetrisAdapter2(length, width);
	
	Tetromino newTet2(Tetromino_t::Z);
	
	cout << "New Tetromino : \n";
	newTet2.print();
	cout << "\n";
	
	tetrisVector2 += newTet2;
	cout << "TETRIS VECTOR Board After Adding New Tetromino : \n";
	tetrisVector2.draw();
	cout << "\n";
	
	tetrisArray2 += newTet2;
	cout << "TETRIS ARRAY Board After Adding New Tetromino : \n";
	tetrisArray2.draw();
	cout << "\n";
	
	tetrisAdapter2 += newTet2;
	cout << "TETRIS ADAPTER Board After Adding New Tetromino : \n";
	tetrisAdapter2.draw();
	cout << "\n\n";
		
	cout << "\n*************************** TESTING ANIMATE, NUMBER OF MOVES AND LAST MOVE FUNCTIONS OF TETRIS CLASSES ************************* \n\n";
		
	cout << "\n ******* ANIMATE TEST - 1 : ************ \n";
	cout << "Press Any Character to Test TETRIS VECTOR's Animate Function (Q - QUIT DRIVER1): ";
	char ch;
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisVector1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisVector1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisVector1.lastMove().print();
	cout << "\n";
	
	
	cout << "\n ******* ANIMATE TEST - 1 : ************ \n";
	cout << "Press Any Character to Test TETRIS ARRAY's Animate Function (Q - QUIT DRIVER1): ";
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisArray1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisArray1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisArray1.lastMove().print();
	cout << "\n";
	
	
	cout << "\n ******* ANIMATE TEST - 1 : ************ \n";
	cout << "Press Any Character to Test TETRIS ADAPTER's Animate Function (Q - QUIT DRIVER1): ";
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisAdapter1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisAdapter1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisAdapter1.lastMove().print();
	cout << "\n";
	
	
	tetrisVector1 += newTet2;
	tetrisArray1 += newTet2;
	tetrisAdapter1 += newTet2;
	
	cout << "\n ******* ANIMATE TEST - 2 : ************ \n";
	cout << "Press Any Character to Test TETRIS VECTOR's Animate Function (Q - QUIT DRIVER1): ";
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisVector1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisVector1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisVector1.lastMove().print();
	cout << "\n";
	
	
	cout << "\n ******* ANIMATE TEST - 2 : ************ \n";
	cout << "Press Any Character to Test TETRIS ARRAY's Animate Function (Q - QUIT DRIVER1): ";
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisArray1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisArray1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisArray1.lastMove().print();
	cout << "\n";
	
	
	cout << "\n ******* ANIMATE TEST - 2 : ************ \n";
	cout << "Press Any Character to Test TETRIS ADAPTER's Animate Function (Q - QUIT DRIVER1): ";
	cin >> ch;
	if (ch == 'q' || ch == 'Q') return 0;
	
	tetrisAdapter1.animate();
	cout << "Number Of Moves Function Result(Each animation rotate count + vertical steps added): " << tetrisAdapter1.numberOfMoves() << "\n";
	cout << "Last Move Function Result: \n"; 
	tetrisAdapter1.lastMove().print();
	cout << "\n";
	
	cout << "\n*************************** TESTING FILE FUNCTIONS OF TETRIS CLASSES ************************* \n\n";
		
	cout << "\n ******* WRITING TETRIS FROM DIFFERENT TYPES TO THE .TXT FILES : ************ \n\n";
		
	ofstream fileVector1("TestTetrisVector.txt");
	if (fileVector1.fail()) {
		cout << "TestTetrisVector.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "TETRIS VECTOR1: \n";
		tetrisVector1.draw();
		cout << "\n";
		
		cout << "Writing TETRIS VECTOR1 to TestTetrisVector.txt \n\n";
		tetrisVector1.writeToFile(fileVector1);
		fileVector1.close();
	}
	
	ofstream fileArray1("TestTetrisArray.txt");
	if (fileArray1.fail()) {
		cout << "TestTetrisArray.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "TETRIS ARRAY1: \n";
		tetrisArray1.draw();
		cout << "\n";
	
		cout << "Writing TETRIS ARRAY1 to TestTetrisArray.txt \n\n";
		tetrisArray1.writeToFile(fileArray1);
		fileArray1.close();
	}
	
	ofstream fileAdapter1("TestTetrisAdapter.txt");
	if (fileAdapter1.fail()) {
		cout << "TestTetrisAdapter.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "TETRIS ADAPTER1: \n";
		tetrisAdapter1.draw();
		cout << "\n";
			
		cout << "Writing TETRIS ADAPTER1 to TestTetrisAdapter.txt \n\n";
		tetrisAdapter1.writeToFile(fileAdapter1);
		fileAdapter1.close();
	}
	
	cout << "\n ******* READING TETRIS FROM DIFFERENT TYPES FROM THE .TXT FILES : ************ \n\n";
	
	TetrisVector tetrisVector3(0, 0);
	TetrisArray1D tetrisArray3(0, 0);
	TetrisAdapter<vector> tetrisAdapter3(0, 0);
	
	ifstream fileVector2("TestTetrisVector.txt");
	if (fileVector2.fail()) {
		cout << "TestTetrisVector.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "Reading TETRIS VECTOR from TestTetrisVector.txt into TetrisVector3. \n";
		tetrisVector3.readFromFile(fileVector2);
		fileVector2.close();
		
		cout << "TETRIS VECTOR3: \n";
		tetrisVector3.draw();
		cout << "\n";
	}
	
	ifstream fileArray2("TestTetrisArray.txt");
	if (fileArray2.fail()) {
		cout << "TestTetrisArray.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "Reading TETRIS ARRAY from TestTetrisArray.txt into TetrisArray3. \n";
		tetrisArray3.readFromFile(fileArray2);
		fileArray2.close();
		
		cout << "TETRIS ARRAY3: \n";
		tetrisArray3.draw();
		cout << "\n";
	}
	
	ifstream fileAdapter2("TestTetrisAdapter.txt");
	if (fileAdapter2.fail()) {
		cout << "TestTetrisAdapter.txt cannot opened. Try again later.\n";
	}
	else {
		cout << "Reading TETRIS ADAPTER from TestTetrisAdapter.txt into TetrisAdapter3. \n";
		tetrisAdapter3.readFromFile(fileAdapter2);
		fileAdapter2.close();
		
		cout << "TETRIS ADAPTER3: \n";
		tetrisAdapter3.draw();
		cout << "\n";
	}
	
	
		
	cout << "\n*************************** DRIVER1 IS COMPLETED. TESTS ARE DONE. ************************* \n\n";
	
	return 0;
}
