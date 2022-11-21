all: clean compile run

compile: main.cpp Tetromino.cpp Tetromino.h Utils.cpp Utils.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test Tetromino.cpp Utils.cpp main.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test
