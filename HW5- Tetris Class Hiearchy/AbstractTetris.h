#ifndef _TETRIS_H_
#define _TETRIS_H_
#include <fstream>
#include "Tetromino.h"

namespace GTUTetris {

	class AbstractTetris {

	public :
		AbstractTetris(int rowNum, int colNum);	/* throws invalid_argument */
		AbstractTetris(const AbstractTetris& oth) = default;
		AbstractTetris& operator=(const AbstractTetris& oth) = default;
		virtual ~AbstractTetris() = default;
		
		void draw() const;	// draws the const tetris board to the screen without new tetromino.
		void draw();	// draws the tetris board to the screen with the new tetromino.
		void animate();
		bool gameStatus() const noexcept;	// returns the status of the game.
		void operator+=(const Tetromino& newTetromino);
		
		int numberOfMoves() const noexcept;
		const Tetromino& lastMove() const; /* throws runtime_error */
		
		virtual void writeToFile(ofstream& ostream) const;
		virtual void readFromFile(ifstream& ifstream);
		
	private :
		bool status;
		int totalMoves;
		
		bool isCurTetrominoActive;
		Tetromino curTetromino;
		
		
	protected :
		int rowNum;
		int colNum;
		
		virtual void print() const = 0;	// prints the map onto the screen
		
		virtual void addTetromino(const Tetromino& t) = 0;	// adds given tetromino to the board
		virtual void deleteTetromino(const Tetromino& t) = 0;	// deletes given tetromino from the board
		
		virtual bool canBeAdded(const Tetromino& t) const = 0;	// checks if given tetromino can be added to the board.
		virtual bool checkHorizantalMovement(const Tetromino& comingT, int newT_fittingY) const = 0;	// checks if given tetromino can be shifted to the given Y position horizantally.

	};

}

#endif
