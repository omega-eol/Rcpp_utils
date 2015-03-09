
A set of useful functions written in C for R using Rcpp package.

1. `code/generateRandomSparseMatrix(ratio, nrow, ncol)` - generates a random sparse matrix with nrow rows and ncol columns. Number of non-zero elements is as calculated as `ceiling(nrow*ncol*ratio)`.

2. `code/convertToSVMLite(X, labels)` - converts sparse matrix X and labels to the SVM Lite format. See example in `test/testConvertToSVMLite.R`

3. `code/toBinarySparseMatrix.cpp` - converts all values in sparse matrix X to 1s.

4. `code/row_nth_largest_filter.cpp` - filters each row in sparse matrix, in way that every value in that row is less than Nth largest value in the current row.