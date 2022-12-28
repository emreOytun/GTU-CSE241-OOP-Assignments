#ifndef _TETRISADAPTER_H_
#define _TETRISADAPTER_H_

#include <iostream>
#include <deque>
#include "AbstractTetris.h"
using namespace std;

namespace GTUTetris {
	
	template<template<typename ...>class Container = std::deque>
	class TetrisAdapter : public AbstractTetris {
	
	public :
		TetrisAdapter(int rowNum, int colNum);
		TetrisAdapter(const TetrisAdapter<Container>& oth);
		TetrisAdapter<Container>& operator=(const TetrisAdapter<Container>& oth);
	
		virtual void writeToFile(ofstream& ostream) const override final;
		virtual void readFromFile(ifstream& ifstream) override final;
	
	private :
		Container<char> map;
		
		virtual void print() const override final;
		
		virtual void addTetromino(const Tetromino& t) override final;
		virtual void deleteTetromino(const Tetromino& t) override final;
		
		virtual bool canBeAdded(const Tetromino& t) const override final;
		virtual bool checkHorizantalMovement(const Tetromino& comingT, int newT_fittingY) const override final;
	
	};

}

#endif
