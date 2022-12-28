all: clean compile run

compile: driver1.cpp driver2.cpp Tetromino.cpp Tetromino.h AbstractTetris.h AbstractTetris.cpp TetrisArray1D.h TetrisArray1D.cpp TetrisVector.cpp TetrisVector.h TetrisAdapter.h TetrisAdapter.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test1 driver1.cpp Tetromino.cpp AbstractTetris.cpp TetrisVector.cpp TetrisArray1D.cpp
	@g++ -std=c++11 -o test2 driver2.cpp Tetromino.cpp AbstractTetris.cpp TetrisVector.cpp TetrisArray1D.cpp 

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test1
	./test2
	@echo "================================================================================="
	@echo "Completed tests...."


clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test1 test2
