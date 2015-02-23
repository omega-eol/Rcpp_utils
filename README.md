
A set of useful function write in C for R using Rcpp package.

1. `code/generateRandomSparseMatrix(ratio, nrow, ncol)` - generates a random sparse matrix with nrow rows and ncol columns. Number of non-zero elements is as calculated as `ceiling(nrow*ncol*ratio)`.

2. `code/convertToSVMLite(X, labels)` - converts sparse matrix X and labels to the SVM Lite format. See example in `test/testConvertToSVMLite.R`

