GXX=g++
FLAGS=-Wall -W -Wextra -Werror
INFILE=test.cpp
OUTFILE=test.out

all:
	$(GXX) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -rf *.out

memcheck:
	valgrind --leak-check=full ./$(OUTFILE)
