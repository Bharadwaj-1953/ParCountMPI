PYTHON=python3
SCRIPT=parcount.py

run:
	@echo "Enter the number of processes (containers):"
	@read NP; \
	echo "Enter the input file(s) (space-separated):"; \
	read INPUT_FILES; \
	echo "Running the parcount script with $$NP processes on input files: $$INPUT_FILES"; \
	mpirun -np $$NP $(PYTHON) $(SCRIPT) $$INPUT_FILES

