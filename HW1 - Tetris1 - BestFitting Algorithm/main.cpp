#include <iostream>
#include "Tetromino.h"
#include "Utils.h"
using namespace std;


int main() {
	
	auto tlist = getTetrominoListFromUser();
	
	cout << "\nFinding the best-fit among all of the possibilities...\n";
	cout << "This process may take some time, please wait !\n";
	cout << "***********\n\n";
	
	Map map(TetrominoManager::findTheBest(tlist));
	map.print();
	cout << "\n";
	
	return 0;
}



