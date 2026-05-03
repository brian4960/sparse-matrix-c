#------------------------------------------------------------------------------
# Makefile for Sparse Matrix Arithmetic in C
#
# make                   builds Sparse
# make MatrixTest        builds MatrixTest
# make clean             removes binaries and object files
# make checkSparse       runs Sparse under valgrind
# make checkMatrixTest   runs MatrixTest under valgrind
#------------------------------------------------------------------------------

CC       = gcc
CFLAGS   = -std=c17 -Wall -Iinclude
REMOVE   = rm -f
MEMCHECK = valgrind --leak-check=full

MAIN     = Sparse
TEST     = MatrixTest

INFILE   = examples/example1_input.txt
OUTFILE  = myout.txt

MAINOBJ  = src/Sparse.o
TESTOBJ  = tests/MatrixTest.o
OBJS     = src/Matrix.o src/List.o

$(MAIN): $(MAINOBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(MAINOBJ) $(OBJS)

$(TEST): $(TESTOBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST) $(TESTOBJ) $(OBJS)

src/Sparse.o: src/Sparse.c include/Matrix.h include/List.h
	$(CC) $(CFLAGS) -c src/Sparse.c -o src/Sparse.o

src/Matrix.o: src/Matrix.c include/Matrix.h include/List.h
	$(CC) $(CFLAGS) -c src/Matrix.c -o src/Matrix.o

src/List.o: src/List.c include/List.h
	$(CC) $(CFLAGS) -c src/List.c -o src/List.o

tests/MatrixTest.o: tests/MatrixTest.c include/Matrix.h include/List.h
	$(CC) $(CFLAGS) -c tests/MatrixTest.c -o tests/MatrixTest.o

clean:
	$(REMOVE) $(MAIN) $(TEST) src/*.o tests/*.o myout.txt

checkSparse: $(MAIN)
	$(MEMCHECK) ./$(MAIN) $(INFILE) $(OUTFILE)

checkMatrixTest: $(TEST)
	$(MEMCHECK) ./$(TEST)