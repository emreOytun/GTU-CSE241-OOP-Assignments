#ifndef _TETROMINO_H_
#define _TETROMINO_H_
#include <fstream>
using namespace std;

namespace GTUTetris {

	enum class Tetromino_t {I, O, T, J, L, S, Z};
	enum class Direction_t {Left, Right};

	class Tetromino {
		
	public : 
		Tetromino();
		Tetromino(const Tetromino_t& tetrominoType);
		Tetromino(const Tetromino_t& tetrominoType, int startX, int startY);
		
		Tetromino(const Tetromino& oth);
		Tetromino& operator=(const Tetromino& oth);
		~Tetromino();
		
		void print() const;
		void rotate(const Direction_t& direction);
		
		/* Changes the tetromino type to fiven one. */
		void changeType(const Tetromino_t& tetrominoType);
		
		/* Start positions */
		int getStartX() const;
		int getStartY() const;
		
		void setStartPosition(int startX, int startY);
		void setStartX(int startX_);
		void setStartY(int startY_);
		
		int getActiveColNum() const;
		int getActiveRowNum() const;
		
		/* Movement of tetromino. */
		void lower();
		void goRight();
		void goLeft();
		
		/* Returned array should not be deleted. */
		const char* operator[](int idx) const;	/* throws out_of_range */

		/* Returns the pointer to the array of the given index, it should not be deleted. */
		char* operator[](int idx); /* throws out_of_range */
		
		bool operator==(const Tetromino& oth) const;
		bool operator!=(const Tetromino& oth) const;
		
		void writeToFile(ofstream& ostream) const;
		void readFromFile(ifstream& ifstream);
		
	private :
		const static int ROWSIZE = 4;
		const static int COLSIZE = 4;
		char** blocks;

		int active_rowNum;
		int active_colNum;
		
		int startX;
		int startY;
		
		void init(const Tetromino_t& tetrominoType);	/* Sets the data to set type of tetromino. */
		void initMemory();	/* Initializes the 2D memory area with the ROWSIZE and COLSIZE. */
		
		bool isLeftColEmpty() const;
		bool isTopRowEmpty() const;
		void shiftActualBlocksToLeft();
		void shiftActualBlocksToUp();
		void setActualBlocks();	/* The function to adjust data in the way that the actual part of the blocks are always fixed at the top-leftmost part in 2D array. */
		
	};

}

#endif
