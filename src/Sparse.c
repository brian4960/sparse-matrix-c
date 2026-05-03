#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *infile, *outfile;
    infile  = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    if( infile==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if( outfile==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int n, a, b, row, col;
    double value;

    // begin by scanning the first 3 numbers
    fscanf(infile, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // scan for Matrix A values
    for (int i = 0; i < a; i++) {
        fscanf(infile, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // scan for Matrix B values
    for (int i = 0; i < b; i++) {
        fscanf(infile, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // A
    fprintf(outfile, "A has %d non-zero entries:\n", numNonZero(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    // B
    fprintf(outfile, "B has %d non-zero entries:\n", numNonZero(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");

    // (1.5)*A
    Matrix C = scalarMult(1.5, A);
    fprintf(outfile, "(1.5)*A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // A+B
    C = sum(A, B);
    fprintf(outfile, "A+B =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // A+A
    C = sum(A, A);
    fprintf(outfile, "A+A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // B-A
    C = diff(B, A);
    fprintf(outfile, "B-A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // A-A
    C = diff(A, A);
    fprintf(outfile, "A-A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // Transpose(A)
    C = transpose(A);
    fprintf(outfile, "Transpose(A) =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // A*B
    C = product(A, B);
    fprintf(outfile, "A*B =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");
    freeMatrix(&C);

    // B*B
    C = product(B, B);
    fprintf(outfile, "B*B =\n");
    printMatrix(outfile, C);
    freeMatrix(&C);

    freeMatrix(&A);
    freeMatrix(&B);
    fclose(infile);
    fclose(outfile);

    return 0;
}