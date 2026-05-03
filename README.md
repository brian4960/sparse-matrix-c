# Sparse Matrix Arithmetic in C

A modular C project that implements sparse matrix arithmetic using custom Abstract Data Types. The project represents matrices as arrays of sorted linked-list rows, storing only nonzero entries to reduce memory usage and support efficient matrix operations.

## Overview

This project implements a sparse matrix calculator in C. Instead of storing every entry in an n x n matrix, the Matrix ADT stores only nonzero values. Each row is represented as a sorted linked list of entries, where each entry contains a column index and a value.

The program reads two sparse matrices from an input file, performs several matrix operations, and writes the formatted results to an output file.

Supported operations include:

- Scalar multiplication
- Matrix addition
- Matrix subtraction
- Matrix transpose
- Matrix multiplication
- Matrix equality checking
- Sparse matrix printing

## Key Features

- Implemented a custom generic doubly linked List ADT in C
- Built a Matrix ADT using an array of sorted linked-list rows
- Stored only nonzero matrix entries to support sparse data
- Implemented matrix operations including addition, subtraction, transpose, scalar multiplication, and multiplication
- Used dynamic memory allocation and manual memory management
- Included a Matrix ADT test client for validating functionality
- Used a Makefile for automated compilation and testing
- Organized source files, headers, tests, documentation, and examples into a clean project structure
- Designed around algorithmic efficiency and sparse representation principles

## Data Structure Design

The Matrix ADT uses a sparse representation:

```text
Matrix
├── row[1] -> List of nonzero entries
├── row[2] -> List of nonzero entries
├── row[3] -> List of nonzero entries
└── ...
```

Each stored matrix entry contains:

```text
(column, value)
```

Rows are maintained in sorted order by column number. This allows operations like addition, subtraction, equality checking, and sparse dot product to scan rows efficiently.

## Project Structure

```text
sparse-matrix-c/
├── README.md
├── Makefile
├── .gitignore
├── include/
│   ├── List.h
│   └── Matrix.h
├── src/
│   ├── List.c
│   ├── Matrix.c
│   └── Sparse.c
├── tests/
│   └── MatrixTest.c
├── docs/
│   └── runtime-analysis.md
└── examples/
    ├── example1_input.txt
    ├── example1_expected_output.txt
    ├── example2_input.txt
    ├── example2_expected_output.txt
    ├── example3_input.txt
    └── example3_expected_output.txt
```

## Building the Project

To build the main program:

```bash
make
```

This creates the executable:

```bash
./Sparse
```

To build the Matrix test client:

```bash
make MatrixTest
```

To remove compiled files and generated output:

```bash
make clean
```

## Running the Program

The main program expects an input file and an output file:

```bash
./Sparse examples/example1_input.txt myout.txt
```

The program reads two sparse matrices from the input file, performs the required matrix operations, and writes the results to the output file.

To compare the output with the expected output:

```bash
diff -u examples/example1_expected_output.txt myout.txt
```

If there is no output from `diff`, then the files match.

## Running Tests

To compile and run the Matrix ADT test client:

```bash
make MatrixTest
./MatrixTest
```

To run the main program with Valgrind:

```bash
make checkSparse
```

To run the Matrix test client with Valgrind:

```bash
make checkMatrixTest
```

## Input Format

The first line of the input file contains:

```text
n a b
```

where:

- n is the matrix dimension
- a is the number of nonzero entries in matrix A
- b is the number of nonzero entries in matrix B

The next a lines contain the nonzero entries of matrix A:

```text
row column value
```

The next b lines contain the nonzero entries of matrix B:

```text
row column value
```

## Example Input

```text
3 3 3

1 2 4.0
2 3 5.0
3 1 6.0

1 1 2.0
2 2 -4.0
3 3 1.0
```

## Example Output Sections

The program outputs the original matrices and the results of the following operations:

```text
A
B
(1.5)*A
A+B
A+A
B-A
A-A
Transpose(A)
A*B
B*B
```

## Runtime Analysis

The project uses sparse matrix representation so that many operations depend on the number of nonzero entries rather than all n² possible matrix entries.

Let:

- n = matrix dimension
- a = number of nonzero entries in matrix A
- b = number of nonzero entries in matrix B

Selected operation runtimes:

| Operation | Runtime |
|---|---:|
| newMatrix(n) | Θ(n) |
| freeMatrix(&M) | Θ(n + a) |
| makeZero(M) | Θ(n + a) |
| changeEntry(M, i, j, x) | Θ(r_i), worst-case Θ(a) |
| copy(A) | Θ(n + a) |
| transpose(A) | Θ(n + a) |
| scalarMult(x, A) | Θ(n + a) |
| sum(A, B) | Θ(n + a + b) |
| diff(A, B) | Θ(n + a + b) |
| product(A, B) | Θ(n² + ab) |
| printMatrix(out, M) | Θ(n + a) |

A more detailed explanation is available in:

```text
docs/runtime-analysis.md
```

## Skills Demonstrated

- C programming
- Abstract Data Types
- Linked lists
- Sparse matrix representation
- Dynamic memory allocation
- Pointer manipulation
- File input/output
- Makefile usage
- Modular project organization
- Algorithm analysis
- Memory management with Valgrind

## Notes

This project was developed as part of a data structures and algorithms course and reorganized into a cleaner GitHub project structure. The implementation emphasizes modularity, sparse data representation, manual memory management, and runtime efficiency.