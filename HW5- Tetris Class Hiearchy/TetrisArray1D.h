#ifndef _TETRISARR_H_
#define _TETRISARR_H_
#include "AbstractTetris.h"
using namespace std;

namespace GTUTetris {

	class TetrisArray1D : public AbstractTetris {
	
	public :
		TetrisArray1D(int rowNum, int colNum);
		TetrisArray1D(const TetrisArray1D& oth);
		TetrisArray1D& operator=(const TetrisArray1D& oth);
		~TetrisArray1D();
	
		virtual void writeToFile(ofstream& ostream) const override final;
		virtual void readFromFile(ifstream& ifstream) override final;
	
	private : 
		char* map;
		
		virtual void print() const override final;
		
		virtual void addTetromino(const Tetromino& t) override final;
		virtual void deleteTetromino(const Tetromino& t) override final;
		
		virtual bool canBeAdded(const Tetromino& t) const override final;
		virtual bool checkHorizantalMovement(const Tetromino& comingT, int newT_fittingY) const override final;		
	
		void initMemory(int rowNum, int colNum);
	};

}

#endif
