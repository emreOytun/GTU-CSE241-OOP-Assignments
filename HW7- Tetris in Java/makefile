all: clean compile run

compile: 
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@javac Driver1.java
	@javac Driver2.java

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	java Driver1
	java Driver2
	@echo "================================================================================="
	@echo "Completed tests...."


clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.class
