#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Exported type --------------------------------------------------------------

typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------

// newMatrix()
// Returns a reference to a new n by n Matrix in the zero state.
Matrix newMatrix(int n);

// freeMatrix()
// Frees all heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);


// Access functions -----------------------------------------------------------

// dimension()
// Returns the number of rows and columns of square Matrix M.
int dimension(Matrix M);

// numNonZero()
// Returns the number of non-zero elements in M.
int numNonZero(Matrix M);

// equals()
// Returns true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B);


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Resets M to the zero Matrix.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to be the value x.
// Pre: 1 <= i <= dimension(M), 1 <= j <= dimension(M)
void changeEntry(Matrix M, int i, int j, double x);


// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix representing the transpose of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix representing A+B.
// Pre: dimension(A) == dimension(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix representing A-B.
// Pre: dimension(A) == dimension(B)
Matrix diff(Matrix A, Matrix B);

// vectorDot()
// Returns the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot(List P, List Q);

// product()
// Returns a reference to a new Matrix representing AB.
// Pre: dimension(A) == dimension(B)
Matrix product(Matrix A, Matrix B);


// Other operations -----------------------------------------------------------

// printMatrix()
// Prints a string representation of Matrix M to filestream out.
void printMatrix(FILE* out, Matrix M);

#endif