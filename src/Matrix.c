#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

// Exported type --------------------------------------------------------------

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    int dimension;
    int numNonZero;
    List* row;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

Entry newEntry(int col, double n) {
    Entry E = malloc(sizeof(EntryObj));
    E->column = col;
    E->value = n;
    
    return E;
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));

    M->dimension = n;
    M->numNonZero = 0;
    M->row = calloc(n + 1, sizeof(List));

    for (int i = 1; i <= n; i++) {
        M->row[i] = newList();
    }

    return M;
}

void freeMatrix(Matrix* pM) {
    if (pM == NULL || (*pM) == NULL) {
        fprintf(stderr, "Matrix Error: freeMatrix(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= dimension(*pM); i++) {
        moveFront((*pM)->row[i]);

        while (position((*pM)->row[i]) > -1) {
            Entry E = (Entry) get((*pM)->row[i]);
            free(E);
            moveNext((*pM)->row[i]);
        }

        freeList(&((*pM)->row[i]));
    }
    
    free((*pM)->row);
    free((*pM));
    (*pM) = NULL;
}

// Access functions -----------------------------------------------------------

int dimension(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: dimension(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->dimension;
}

int numNonZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: numNonZero(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->numNonZero;
}

bool equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: equals(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    // if they are different sized matrices, they are automatically not equal
    if (dimension(A) != dimension(B)) {
        return false;
    }

    // loops through each entry and compares each row’s entries
    for (int i = 1; i <= dimension(A); i++) {

        // if the length of the two rows are different, then they are automatically not equal
        if (length(A->row[i]) != length(B->row[i])) {
            return false;
        }

        moveFront(A->row[i]);
        moveFront(B->row[i]);

        while (position(A->row[i]) > -1) {
            Entry eA = (Entry) get((A)->row[i]);
            Entry eB = (Entry) get((B)->row[i]);
            
            if (eA->value != eB->value || eA->column != eB->column) {
                return false;
            }

            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }

    // return true if it passes all checks
    return true;
}

// Manipulation procedures ----------------------------------------------------

void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: makeZero(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    M->numNonZero = 0;

    // loop through each row and free each node/value (column entry)
    // then empty the row of its nodes
    int len = 0;
    for (int i = 1; i <= dimension(M); i++) {
        len = length(M->row[i]);
        for (int j = 1; j <= len; j++) {
            moveFront(M->row[i]);
            Entry E = (Entry) get(M->row[i]);
            free(E);
            deleteFront(M->row[i]);
        }
    }
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: changeEntry(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (i < 1 || i > dimension(M)) {
        fprintf(stderr, "Matrix Error: changeEntry(): Invalid index reference\n");
        exit(EXIT_FAILURE);
    }

    if (j < 1 || j > dimension(M)) {
        fprintf(stderr, "Matrix Error: changeEntry(): Invalid index reference\n");
        exit(EXIT_FAILURE);
    }

    if (x == 0) {
        moveFront(M->row[i]);

        while (position(M->row[i]) > -1) {
            Entry E = (Entry) get(M->row[i]);

            // check if the entry that the user wants to be removed exists in the sparse matrix
            if (E->column == j) {
                free(E);
                delete(M->row[i]);
                M->numNonZero--;
                return;
            }

            moveNext(M->row[i]);
        }

        // since x is 0, if it doesn't remove any entry from the sparse matrix, it will do nothing
        return;
    }

    // if x is a valid number (non-zero), then it will replace its value if the entry exists
    moveFront(M->row[i]);

    while (position(M->row[i]) > -1) {
        Entry E = (Entry) get(M->row[i]);

        if (E->column == j) {
            E->value = x;
            return;
        }

        moveNext(M->row[i]);
    }

    // if the entry does not exist, a new one will be created
    moveFront(M->row[i]);
    Entry E = newEntry(j, x);

    // append automatically if the row is empty
    if (length (M->row[i]) == 0) {
            append(M->row[i], E);
            M->numNonZero++;
            return;
    }

    for (moveBack(M->row[i]); position(M->row[i]) > -1; movePrev(M->row[i])) {
        Entry tE = (Entry) get(M->row[i]);

        // insert in sorted order
        if (j >= tE->column) {
            insertAfter(M->row[i], E);
            M->numNonZero++;
            return;
        }
    }

    // prepends if it is the first element
    prepend(M->row[i], E);
    M->numNonZero++;
    return;
}

Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: copy(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(dimension(A));
    B->numNonZero = A->numNonZero;

    for (int i = 1; i <= dimension(A); i++) {
        for (moveFront(A->row[i]); position(A->row[i]) > -1; moveNext(A->row[i])) {
            Entry E = (Entry) get(A->row[i]);
            append(B->row[i], newEntry(E->column, E->value));
        }
    }

    return B;
}

Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: transpose(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix tA = newMatrix(dimension(A));
    tA->numNonZero = A->numNonZero;

    for (int i = 1; i <= dimension(A); i++) {
        for (moveFront(A->row[i]); position(A->row[i]) > -1; moveNext(A->row[i])) {
            Entry E = (Entry) get(A->row[i]);
            append(tA->row[E->column], newEntry(i, E->value));
        }
    }

    return tA;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: scalarMult(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    // if x = 0, return a zero Matrix
    if (x == 0) {
        Matrix sA = newMatrix(dimension(A));
        return sA;
    }

    Matrix sA = newMatrix(dimension(A));
    sA->numNonZero = A->numNonZero;

    for (int i = 1; i <= dimension(A); i++) {
        for (moveFront(A->row[i]); position(A->row[i]) > -1; moveNext(A->row[i])) {
            Entry E = (Entry) get(A->row[i]);
            append(sA->row[i], newEntry(E->column, (x * E->value)));
        }
    }

    return sA;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: sum(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: sum(): Non-equal dimensions\n");
        exit(EXIT_FAILURE);
    }

    if (equals(A, B) == true) {
        Matrix C = scalarMult(2.0, A);
        return C;
    }

    Matrix C = newMatrix(dimension(A));

    for (int i = 1; i <= dimension(A); i++) {
        moveFront(A->row[i]);
        moveFront(B->row[i]);

        while (position(A->row[i]) > -1 && position(B->row[i]) > -1) {
            Entry EA = (Entry) get(A->row[i]);
            Entry EB = (Entry) get(B->row[i]);

            if (EA->column == EB->column) {
                if (EA->value + EB->value != 0) {
                    append(C->row[i], newEntry(EA->column, EA->value + EB->value));
                    C->numNonZero++;
                }

                moveNext(A->row[i]);
                moveNext(B->row[i]);
            } else if (EA->column < EB->column) {
                append(C->row[i], newEntry(EA->column, EA->value));
                C->numNonZero++;
                moveNext(A->row[i]);
            } else if (EB->column < EA->column) {
                append(C->row[i], newEntry(EB->column, EB->value));
                C->numNonZero++;
                moveNext(B->row[i]);
            }
        }

        while (position(A->row[i]) > -1) {
            Entry EA = (Entry) get(A->row[i]);
            append(C->row[i], newEntry(EA->column, EA->value));
            C->numNonZero++;
            moveNext(A->row[i]);
        }

        while (position(B->row[i]) > -1) {
            Entry EB = (Entry) get(B->row[i]);
            append(C->row[i], newEntry(EB->column, EB->value));
            C->numNonZero++;
            moveNext(B->row[i]);
        }
    }

    return C;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: diff(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: diff(): Non-equal dimensions\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(dimension(A));

    for (int i = 1; i <= dimension(A); i++) {
        moveFront(A->row[i]);
        moveFront(B->row[i]);

        while (position(A->row[i]) > -1 && position(B->row[i]) > -1) {
            Entry EA = (Entry) get(A->row[i]);
            Entry EB = (Entry) get(B->row[i]);

            if (EA->column == EB->column) {
                if (EA->value - EB->value != 0) {
                    append(C->row[i], newEntry(EA->column, EA->value - EB->value));
                    C->numNonZero++;
                }

                moveNext(A->row[i]);
                moveNext(B->row[i]);
            } else if (EA->column < EB->column) {
                append(C->row[i], newEntry(EA->column, EA->value));
                C->numNonZero++;
                moveNext(A->row[i]);
            } else if (EB->column < EA->column) {
                append(C->row[i], newEntry(EB->column, -1 * EB->value));
                C->numNonZero++;
                moveNext(B->row[i]);
            }
        }

        while (position(A->row[i]) > -1) {
            Entry EA = (Entry) get(A->row[i]);
            append(C->row[i], newEntry(EA->column, EA->value));
            C->numNonZero++;
            moveNext(A->row[i]);
        }

        while (position(B->row[i]) > -1) {
            Entry EB = (Entry) get(B->row[i]);
            append(C->row[i], newEntry(EB->column, -1 * EB->value));
            C->numNonZero++;
            moveNext(B->row[i]);
        }
    }

    return C;
}

double vectorDot(List P, List Q) {
    if (P == NULL || Q == NULL) {
        fprintf(stderr, "List Error: vectorDot(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    double result = 0;

    for (moveFront(P); position(P) > -1; moveNext(P)) {
        Entry EP = (Entry) get(P);

        for (moveFront(Q); position(Q) > -1; moveNext(Q)) {
            Entry EQ = (Entry) get(Q);

            if (EP->column == EQ->column) {
                result += (EP->value * EQ->value);
            }
        }
    }

    return result;
}

Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: product(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: product(): Non-equal dimensions\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(dimension(A));
    Matrix tB = transpose(B);

    for (int i = 1; i <= dimension(A); i++) {
        for (int j = 1; j <= dimension(tB); j++) {
            double dotProduct = vectorDot(A->row[i], tB->row[j]);

            if (dotProduct != 0) {
                append(C->row[i], newEntry(j, dotProduct));
                C->numNonZero++;
            }
        }
    }

    freeMatrix(&tB);
    return C;
}

void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: printMatrix(): NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (out == NULL) {
        fprintf(stderr, "Matrix Error: printMatrix(): NULL file reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= dimension(M); i++) {
        if (length(M->row[i]) != 0) {
            fprintf(out, "%d: ", i);
            for (moveFront(M->row[i]); position(M->row[i]) > -1; moveNext(M->row[i])) {
                Entry E = (Entry) get(M->row[i]);
                fprintf(out, "(%d, %.1f) ", E->column, E->value);
            }

            fprintf(out, "\n");
        }
    }
}