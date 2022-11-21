#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include <vector>
using namespace std;

enum class Tetromino_t {I, O, T, J, L, S, Z};
enum class Direction_t {Left, Right};

/* Swaps two integer variables. */
void swap(int& num1, int& num2);

class Tetromino {
	
public : 
	Tetromino();
	Tetromino(Tetromino_t tetrominoType);
	Tetromino(Tetromino_t tetrominoType, int startX, int startY);
	
	void print() const;
	void rotate(Direction_t direction);
	bool canFit(const Tetromino& oth, Direction_t relativeDirection) const;
	
	int getStartX() const;
	int getStartY() const;
	
	void setStartPosition(int startX, int startY);
	void setStartX(int startX_);
	void setStartY(int startY_);
	
	int getActiveColNum() const;
	int getActiveRowNum() const;
	
	vector<int> getLeftMostBottomIndexes() const;
	vector<int> getRightMostBottomIndexes() const;
	vector< vector<char> > getBlock() const;
	
	vector<int> findFittingIndexes_and_spaceNumbers_whenRight(const Tetromino& t2) const;	
	void lower();
	void goRight();
	void goLeft();
	
	bool operator==(const Tetromino& oth);
	bool operator!=(const Tetromino& oth);
	
private :
	vector< vector<char> > blocks;

	int active_rowNum;
	int active_colNum;
	
	int startX;
	int startY;
	
	void init(Tetromino_t tetrominoType);
	
	bool isLeftColEmpty() const;
	bool isTopRowEmpty() const;
	void shiftActualBlocksToLeft();
	void shiftActualBlocksToUp();
	void setActualBlocks();
	
};

#endif
