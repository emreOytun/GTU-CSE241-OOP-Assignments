#ifndef _TETRIS_H_
#define _TETRIS_H_
#include "Tetromino.h"

namespace GTUTetris {

	/*************************** MAP CLASS **************************/

	/* Map class to render tetrominos and print them into the screen. */
	class Map {

	public :
		Map(int rowNum, int colNum);	// initializes the map with the given row and column numbers.
		
		Map(const Map& oth);
		Map& operator=(const Map& oth);
		~Map();
		
		int getRowNum() const;
		int getColNum() const;
		
		void print() const;	// prints the map onto the screen
		
		void addTetromino(const Tetromino& t);	// adds given tetromino to the board
		void deleteTetromino(const Tetromino& t);	// deletes given tetromino from the board
		
		bool canBeAdded(const Tetromino& t) const;	// checks if given tetromino can be added to the board.
		bool checkHorizantalMovement(const Tetromino& comingT, int newT_fittingY) const;	// checks if given tetromino can be shifted to the given Y position horizantally.

	private :
		char **map;
		int rowNum;
		int colNum;
		
		void initMemory(int rowSize, int colSize);
	};


	/******************** TETRIS CLASS ********************/

	class Tetris {

	public :
		Tetris(int rowNum, int colNum);
		
		void draw() const;	// draws the const tetris board to the screen without new tetromino.
		void draw();	// draws the tetris board to the screen with the new tetromino.
		void animate();
		bool gameStatus() const;	// returns the status of the game.
		Tetris& operator+=(const Tetromino& newTetromino);
		
		// Big three is not implemented in this class since it's not needed.
		
	private :
		Map gameMap;	
		bool status;
		
		bool isCurTetrominoActive;
		Tetromino curTetromino;
		int curTetromino_fittingX;
		int curTetromino_fittingY;

	};

	/*****************************************************/

}

#endif
