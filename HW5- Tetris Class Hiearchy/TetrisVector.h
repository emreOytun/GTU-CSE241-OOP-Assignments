#ifndef _TETRISVEC_H_
#define _TETRISVEC_H_

#include <vector>
#include <fstream>
#include "AbstractTetris.h"
using namespace std;

namespace GTUTetris {

	class TetrisVector : public AbstractTetris {
	
	public :
		TetrisVector(int rowNum, int colNum);
		TetrisVector(const TetrisVector& oth);
		TetrisVector& operator=(const TetrisVector& oth);
		
		virtual void writeToFile(ofstream& ostream) const override final;
		virtual void readFromFile(ifstream& ifstream) override final;
		
	private :
		vector< vector<char> > map;
		
		virtual void print() const override final;
		
		virtual void addTetromino(const Tetromino& t) override final;
		virtual void deleteTetromino(const Tetromino& t) override final;
		
		virtual bool canBeAdded(const Tetromino& t) const override final;
		virtual bool checkHorizantalMovement(const Tetromino& comingT, int newT_fittingY) const override final;
		
	};

}

#endif
