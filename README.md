### Description
A set of useful functions written in C for R using Rcpp package.

1. `code/generateRandomSparseMatrix(ratio, nrow, ncol)` - generates a random sparse matrix with nrow rows and ncol columns. Number of non-zero elements is as calculated as `ceiling(nrow*ncol*ratio)`.

2. `code/convertToSVMLite(X, labels)` - converts sparse matrix X and labels to the SVM Lite format. See example in `test/testConvertToSVMLite.R`

3. `code/toBinarySparseMatrix.cpp` - converts all values in sparse matrix X to 1s.

4. `code/row_nth_largest_filter.cpp` - filters each row in sparse matrix, in way that every value in that row is less than Nth largest value in the current row.

### Requirements
1. Rcpp package
2. RcppEigen package
3. RcppArmadillo package

### For Mac Users
In case you have the following error while compiling the Rcpp functions:
`ld: library not found for -lgfortran`
1. First install `brew install gcc`
2. Add this line `FLIBS=-L/usr/local/Cellar/gcc/5.2.0/bin/gfortran` to `~/.R/Makevars` file.

