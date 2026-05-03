#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    // TEST 1: Initialization & Basic Access
    Matrix A = newMatrix(5);
    Matrix B = newMatrix(5);

    fprintf(stdout, "TEST 1\n");
    fprintf(stdout, "%d\n", dimension(A));
    fprintf(stdout, "%d\n", numNonZero(A));
    fprintf(stdout, "%d\n", equals(A, B));
    fprintf(stdout, "\n");

    // TEST 2: changeEntry Sorting, Updating, Deleting, and Zero No-op
    changeEntry(A, 3, 4, 4.4);
    changeEntry(A, 3, 2, 2.2);
    changeEntry(A, 3, 5, 5.5);
    changeEntry(A, 3, 1, 1.1);
    changeEntry(A, 3, 3, 3.3);

    fprintf(stdout, "TEST 2\n");
    fprintf(stdout, "%d\n", numNonZero(A));
    printMatrix(stdout, A);
    fprintf(stdout, "\n");

    changeEntry(A, 3, 3, 9.9);
    changeEntry(A, 3, 4, 0.0);
    changeEntry(A, 1, 1, 0.0);

    fprintf(stdout, "%d\n", numNonZero(A));
    printMatrix(stdout, A);
    fprintf(stdout, "\n");

    // TEST 3: copy() Deep Copy and makeZero()
    Matrix C = copy(A);

    fprintf(stdout, "TEST 3\n");
    fprintf(stdout, "%d\n", equals(A, C));

    changeEntry(A, 3, 1, 0.0);

    fprintf(stdout, "%d\n", equals(A, C));
    fprintf(stdout, "%d\n", numNonZero(A));
    fprintf(stdout, "%d\n", numNonZero(C));
    printMatrix(stdout, A);
    fprintf(stdout, "\n");
    printMatrix(stdout, C);
    fprintf(stdout, "\n");

    makeZero(A);

    fprintf(stdout, "%d\n", numNonZero(A));
    printMatrix(stdout, A);

    changeEntry(A, 5, 5, 5.5);

    fprintf(stdout, "%d\n", numNonZero(A));
    printMatrix(stdout, A);
    fprintf(stdout, "\n");

    // TEST 4: transpose()
    makeZero(A);
    changeEntry(A, 1, 3, 1.3);
    changeEntry(A, 2, 1, 2.1);
    changeEntry(A, 4, 5, 4.5);
    changeEntry(A, 5, 2, 5.2);

    Matrix T = transpose(A);
    Matrix TT = transpose(T);

    fprintf(stdout, "TEST 4\n");
    printMatrix(stdout, A);
    fprintf(stdout, "\n");
    printMatrix(stdout, T);
    fprintf(stdout, "\n");
    fprintf(stdout, "%d\n", numNonZero(T));
    fprintf(stdout, "%d\n", equals(A, TT));
    fprintf(stdout, "\n");

    // TEST 5: scalarMult()
    Matrix S1 = scalarMult(2.0, A);
    Matrix S0 = scalarMult(0.0, A);
    Matrix Sneg = scalarMult(-1.0, A);

    fprintf(stdout, "TEST 5\n");
    fprintf(stdout, "%d\n", numNonZero(S1));
    fprintf(stdout, "%d\n", numNonZero(S0));
    fprintf(stdout, "%d\n", numNonZero(Sneg));
    printMatrix(stdout, S1);
    fprintf(stdout, "\n");
    printMatrix(stdout, S0);
    fprintf(stdout, "\n");
    printMatrix(stdout, Sneg);
    fprintf(stdout, "\n");

    // TEST 6: sum()
    Matrix D = newMatrix(5);

    changeEntry(D, 1, 3, -1.3);
    changeEntry(D, 2, 1, 7.0);
    changeEntry(D, 3, 3, 3.3);
    changeEntry(D, 4, 4, 4.4);
    changeEntry(D, 5, 2, -5.2);

    Matrix SumAA = sum(A, A);
    Matrix TwoA = scalarMult(2.0, A);
    Matrix SumAD = sum(A, D);

    fprintf(stdout, "TEST 6\n");
    fprintf(stdout, "%d\n", equals(SumAA, TwoA));
    fprintf(stdout, "%d\n", numNonZero(SumAA));
    fprintf(stdout, "%d\n", numNonZero(SumAD));
    printMatrix(stdout, D);
    fprintf(stdout, "\n");
    printMatrix(stdout, SumAA);
    fprintf(stdout, "\n");
    printMatrix(stdout, SumAD);
    fprintf(stdout, "\n");

    // TEST 7: diff()
    Matrix DiffAA = diff(A, A);
    Matrix DiffAD = diff(A, D);

    fprintf(stdout, "TEST 7\n");
    fprintf(stdout, "%d\n", numNonZero(DiffAA));
    fprintf(stdout, "%d\n", numNonZero(DiffAD));
    printMatrix(stdout, DiffAA);
    fprintf(stdout, "\n");
    printMatrix(stdout, DiffAD);
    fprintf(stdout, "\n");

    // TEST 8: product() with Identity and Zero Matrix
    Matrix I = newMatrix(5);

    for (int i = 1; i <= 5; i++) {
        changeEntry(I, i, i, 1.0);
    }

    Matrix AI = product(A, I);
    Matrix IA = product(I, A);
    Matrix AZ = product(A, S0);

    fprintf(stdout, "TEST 8\n");
    fprintf(stdout, "%d\n", equals(AI, A));
    fprintf(stdout, "%d\n", equals(IA, A));
    fprintf(stdout, "%d\n", numNonZero(AZ));
    printMatrix(stdout, I);
    fprintf(stdout, "\n");
    printMatrix(stdout, AI);
    fprintf(stdout, "\n");
    printMatrix(stdout, IA);
    fprintf(stdout, "\n");
    printMatrix(stdout, AZ);
    fprintf(stdout, "\n");

    // TEST 9: product() Known 3x3 Case
    Matrix P = newMatrix(3);
    Matrix Q = newMatrix(3);

    changeEntry(P, 1, 1, 1.0);
    changeEntry(P, 1, 2, 2.0);
    changeEntry(P, 1, 3, 3.0);
    changeEntry(P, 2, 1, 4.0);
    changeEntry(P, 2, 2, 5.0);
    changeEntry(P, 2, 3, 6.0);
    changeEntry(P, 3, 1, 7.0);
    changeEntry(P, 3, 2, 8.0);
    changeEntry(P, 3, 3, 9.0);

    changeEntry(Q, 1, 1, 1.0);
    changeEntry(Q, 2, 2, 1.0);

    Matrix PQ = product(P, Q);

    fprintf(stdout, "TEST 9\n");
    fprintf(stdout, "%d\n", numNonZero(PQ));
    printMatrix(stdout, P);
    fprintf(stdout, "\n");
    printMatrix(stdout, Q);
    fprintf(stdout, "\n");
    printMatrix(stdout, PQ);
    fprintf(stdout, "\n");

    // TEST 10: equals() Edge Cases
    Matrix E1 = newMatrix(5);
    Matrix E2 = newMatrix(5);

    changeEntry(E1, 1, 1, 10.0);
    changeEntry(E2, 1, 1, 10.0);

    fprintf(stdout, "TEST 10\n");
    fprintf(stdout, "%d\n", equals(E1, E2));

    changeEntry(E2, 1, 1, 11.0);
    fprintf(stdout, "%d\n", equals(E1, E2));

    changeEntry(E2, 1, 1, 0.0);
    changeEntry(E2, 1, 2, 10.0);
    fprintf(stdout, "%d\n", equals(E1, E2));

    makeZero(E1);
    makeZero(E2);
    fprintf(stdout, "%d\n", equals(E1, E2));
    fprintf(stdout, "\n");

    // TEST 11: Original Matrix Not Mutated by Operations
    Matrix Original = newMatrix(4);

    changeEntry(Original, 1, 1, 1.0);
    changeEntry(Original, 2, 2, 2.0);
    changeEntry(Original, 3, 3, 3.0);

    Matrix OriginalCopy = copy(Original);
    Matrix Temp1 = transpose(Original);
    Matrix Temp2 = scalarMult(5.0, Original);
    Matrix Temp3 = sum(Original, Original);
    Matrix Temp4 = diff(Original, Original);
    Matrix Temp5 = product(Original, Original);

    fprintf(stdout, "TEST 11\n");
    fprintf(stdout, "%d\n", equals(Original, OriginalCopy));
    printMatrix(stdout, Original);
    fprintf(stdout, "\n");
    printMatrix(stdout, Temp1);
    fprintf(stdout, "\n");
    printMatrix(stdout, Temp2);
    fprintf(stdout, "\n");
    printMatrix(stdout, Temp3);
    fprintf(stdout, "\n");
    printMatrix(stdout, Temp4);
    fprintf(stdout, "\n");
    printMatrix(stdout, Temp5);

    // Clean Up
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&T);
    freeMatrix(&TT);
    freeMatrix(&S1);
    freeMatrix(&S0);
    freeMatrix(&Sneg);
    freeMatrix(&D);
    freeMatrix(&SumAA);
    freeMatrix(&TwoA);
    freeMatrix(&SumAD);
    freeMatrix(&DiffAA);
    freeMatrix(&DiffAD);
    freeMatrix(&I);
    freeMatrix(&AI);
    freeMatrix(&IA);
    freeMatrix(&AZ);
    freeMatrix(&P);
    freeMatrix(&Q);
    freeMatrix(&PQ);
    freeMatrix(&E1);
    freeMatrix(&E2);
    freeMatrix(&Original);
    freeMatrix(&OriginalCopy);
    freeMatrix(&Temp1);
    freeMatrix(&Temp2);
    freeMatrix(&Temp3);
    freeMatrix(&Temp4);
    freeMatrix(&Temp5);

    return 0;
}

/*
Expected Output:

TEST 1
5
0
1

TEST 2
5
3: (1, 1.1) (2, 2.2) (3, 3.3) (4, 4.4) (5, 5.5) 

4
3: (1, 1.1) (2, 2.2) (3, 9.9) (5, 5.5) 

TEST 3
1
0
3
4
3: (2, 2.2) (3, 9.9) (5, 5.5) 

3: (1, 1.1) (2, 2.2) (3, 9.9) (5, 5.5) 

0
1
5: (5, 5.5) 

TEST 4
1: (3, 1.3) 
2: (1, 2.1) 
4: (5, 4.5) 
5: (2, 5.2) 

1: (2, 2.1) 
2: (5, 5.2) 
3: (1, 1.3) 
5: (4, 4.5) 

4
1

TEST 5
4
0
4
1: (3, 2.6) 
2: (1, 4.2) 
4: (5, 9.0) 
5: (2, 10.4) 


1: (3, -1.3) 
2: (1, -2.1) 
4: (5, -4.5) 
5: (2, -5.2) 

TEST 6
1
4
4
1: (3, -1.3) 
2: (1, 7.0) 
3: (3, 3.3) 
4: (4, 4.4) 
5: (2, -5.2) 

1: (3, 2.6) 
2: (1, 4.2) 
4: (5, 9.0) 
5: (2, 10.4) 

2: (1, 9.1) 
3: (3, 3.3) 
4: (4, 4.4) (5, 4.5) 

TEST 7
0
6

1: (3, 2.6) 
2: (1, -4.9) 
3: (3, -3.3) 
4: (4, -4.4) (5, 4.5) 
5: (2, 10.4) 

TEST 8
1
1
0
1: (1, 1.0) 
2: (2, 1.0) 
3: (3, 1.0) 
4: (4, 1.0) 
5: (5, 1.0) 

1: (3, 1.3) 
2: (1, 2.1) 
4: (5, 4.5) 
5: (2, 5.2) 

1: (3, 1.3) 
2: (1, 2.1) 
4: (5, 4.5) 
5: (2, 5.2) 


TEST 9
6
1: (1, 1.0) (2, 2.0) (3, 3.0) 
2: (1, 4.0) (2, 5.0) (3, 6.0) 
3: (1, 7.0) (2, 8.0) (3, 9.0) 

1: (1, 1.0) 
2: (2, 1.0) 

1: (1, 1.0) (2, 2.0) 
2: (1, 4.0) (2, 5.0) 
3: (1, 7.0) (2, 8.0) 

TEST 10
1
0
0
1

TEST 11
1
1: (1, 1.0) 
2: (2, 2.0) 
3: (3, 3.0) 

1: (1, 1.0) 
2: (2, 2.0) 
3: (3, 3.0) 

1: (1, 5.0) 
2: (2, 10.0) 
3: (3, 15.0) 

1: (1, 2.0) 
2: (2, 4.0) 
3: (3, 6.0) 


1: (1, 1.0) 
2: (2, 4.0) 
3: (3, 9.0) 
*/