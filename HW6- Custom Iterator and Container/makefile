all: clean compile run

compile: main.cpp Iterator.hpp ConstIterator.hpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test main.cpp PFArray.hpp Iterator.hpp ConstIterator.hpp

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
