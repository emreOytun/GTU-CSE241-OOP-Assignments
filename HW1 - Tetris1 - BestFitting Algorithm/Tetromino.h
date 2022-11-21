#include <vector>
using namespace std;

enum class Tetromino_t {I, O, T, J, L, S, Z};
enum class Direction_t {Left, Right};

class Tetromino {
	
public : 
	
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
	
	vector< vector<char> > getBlock() const;
	
	vector<int> findFittingIndexes_and_spaceNumbers_whenRight(const Tetromino& t2) const;	
	
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
	
	vector<int> getLeftMostBottomIndexes() const;
	vector<int> getRightMostBottomIndexes() const;

};
