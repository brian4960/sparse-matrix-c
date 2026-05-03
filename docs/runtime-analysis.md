# Runtime Analysis

This project implements sparse matrix arithmetic in C using a custom Matrix ADT and a generic doubly linked List ADT. Instead of storing every value in an n x n matrix, the Matrix ADT stores only nonzero entries. Each row is represented as a sorted linked list of (column, value) pairs, and any missing entry is treated as zero.

## Variables Used

| Symbol | Meaning |
|---|---|
| n | Matrix dimension |
| a | Number of nonzero entries in matrix A |
| b | Number of nonzero entries in matrix B |
| r_i | Number of nonzero entries in row i |
| p, q | Number of entries in two sparse rows |

## Sparse Matrix Design

A dense matrix stores all n² entries, including zeros. This project uses a sparse representation where each row stores only its nonzero entries:

row[1] -> sorted List of nonzero entries  
row[2] -> sorted List of nonzero entries  
row[3] -> sorted List of nonzero entries  
...  
row[n] -> sorted List of nonzero entries  

Each stored entry contains a (column, value) pair. Rows are kept sorted by column number, which makes operations like addition, subtraction, equality checking, and dot product more efficient because rows can be scanned in order.

## Runtime Summary

| Operation | Runtime | Why |
|---|---:|---|
| newMatrix(n) | Θ(n) | Creates n empty row Lists |
| freeMatrix(&M) | Θ(n + a) | Frees each row and each stored Entry |
| makeZero(M) | Θ(n + a) | Removes all nonzero entries |
| dimension(M) | Θ(1) | Returns a stored field |
| numNonZero(M) | Θ(1) | Returns a stored field |
| equals(A, B) | Θ(n + a + b) | Compares rows and stored entries |
| changeEntry(M, i, j, x) | Θ(r_i), worst-case Θ(a) | Searches only row i |
| copy(A) | Θ(n + a) | Copies the row structure and nonzero entries |
| transpose(A) | Θ(n + a) | Moves each entry from (i, j) to (j, i) |
| scalarMult(x, A) | Θ(n + a) | Multiplies each stored value by x |
| sum(A, B) | Θ(n + a + b) | Merges corresponding sorted rows |
| diff(A, B) | Θ(n + a + b) | Merges corresponding sorted rows and subtracts |
| vectorDot(P, Q) | Θ(p + q) | Scans two sorted sparse rows once |
| product(A, B) | Θ(n² + ab) | Uses sparse dot products after transposing B |
| printMatrix(out, M) | Θ(n + a) | Checks rows and prints stored entries |

## Key Runtime Ideas

### Constant-Time Access Functions

The functions dimension(M) and numNonZero(M) are Θ(1) because these values are stored directly inside the Matrix object. They do not need to scan the matrix.

### Row-Based Operations

changeEntry(M, i, j, x) only searches row i, not the entire matrix. If row i has r_i entries, the runtime is Θ(r_i). In the worst case, all nonzero entries could be in one row, so the worst-case runtime is Θ(a).

### Single-Matrix Operations

Operations like copy(A), transpose(A), and scalarMult(x, A) visit each nonzero entry once and also create a new row structure. That gives Θ(n + a).

### Two-Matrix Operations

For sum(A, B) and diff(A, B), corresponding rows from A and B are merged. Since the rows are sorted, each stored entry is visited once. That gives Θ(n + a + b).

### Sparse Dot Product

vectorDot(P, Q) computes the dot product of two sparse rows. Since both rows are sorted, the function scans through both rows once. If the row lengths are p and q, the runtime is Θ(p + q).

### Matrix Multiplication

Dense matrix multiplication usually takes Θ(n³) because there are n² output entries, and each output entry requires a length-n dot product.

This project uses sparse multiplication. It transposes B first, then computes dot products between rows of A and rows of transpose(B). The target runtime is Θ(n² + ab), where a and b are the numbers of nonzero entries in the input matrices.

When a and b are much smaller than n², sparse multiplication can be more efficient than dense multiplication.

## Main Takeaways

- Sparse matrices store only nonzero entries.
- Missing entries are treated as zero.
- Sorted row Lists allow efficient merging and dot products.
- Many operations depend on the number of nonzero entries instead of all n² possible entries.
- This project demonstrates how data structure design directly affects algorithm efficiency.