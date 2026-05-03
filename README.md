# Sparse Matrix Arithmetic in C

A modular C project that implements sparse matrix arithmetic using custom Abstract Data Types. The project represents matrices as arrays of sorted linked-list rows, storing only nonzero entries to reduce memory usage and support efficient matrix operations.

## Overview

This project implements a sparse matrix calculator in C. Instead of storing every entry in an `n x n` matrix, the Matrix ADT stores only nonzero values. Each row is represented as a sorted linked list of entries, where each entry contains a column index and a value.

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
- Designed around algorithmic efficiency and sparse representation principles

## Data Structure Design

The Matrix ADT uses a sparse representation:

```text
Matrix
├── row[1] → List of nonzero entries
├── row[2] → List of nonzero entries
├── row[3] → List of nonzero entries
└── ...