# Test row_nth_largest_filter function

# clear memory
rm(list=ls());

# set working directory
setwd("~/code/Rcpp_utils/test/");

# load functions
Rcpp::sourceCpp('../code/row_nth_largest_filter.cpp');
source('../code/generateRandomSparseMatrix.R');

# generate a random sparse matrix
data = generateRandomSparseMatrix(ratio = 0.5, nrow = 10000, ncol = 10);
head(data);

# get labels
nth = 1;

# convert to SVM lite format
ptm = proc.time();
# here we pass a transpose 'data' sparse matrix. since it is a column-oriented matrix and we need
# filter rows
res = row_nth_largest_filter(t(data), nth);
print(proc.time()-ptm);

# reconstruct the new matrix
new_data = sparseMatrix(i = res$y[1:res$nonZeros], j = res$x[1:res$nonZeros], 
                        x = res$coeff[1:res$nonZeros], dims=c(nrow(data), ncol(data)) );
head(new_data);
