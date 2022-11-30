all: clean compile run

compile: driver1.cpp driver2.cpp Tetromino.cpp Tetromino.h Tetris.h Tetris.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test1 Tetromino.cpp driver1.cpp Tetris.cpp
	@g++ -std=c++11 -o test2 Tetromino.cpp driver2.cpp Tetris.cpp

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
