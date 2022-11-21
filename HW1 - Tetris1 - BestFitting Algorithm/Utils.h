#include <vector>
using namespace std;
class Tetromino;

/* Swaps two integer variables. */
void swap(int& num1, int& num2);

vector<Tetromino> getTetrominoListFromUser();

/* Map class to render tetrominos and print them into the screen. */
class Map {

public :
	Map(vector<Tetromino> list);
	
	void setMap(vector<Tetromino> list);
	void print() const;

private :
	vector< vector<char> > map;
};


/* TetrominoManager class to deal with managing tetromino groups. */
class TetrominoManager {
	
public :
	
	static vector<Tetromino> findBestFitRec(vector<Tetromino> list, int idx);
	static vector<Tetromino> findBestFitLinear(vector<Tetromino> list);
	static vector<Tetromino> findTheBest(vector<Tetromino> list);
	static vector<Tetromino> findBestBestFitLinear(vector<Tetromino> list);
	
};


