# Test convertToSVMLite function

# clear memory
rm(list=ls());

# set working directory
setwd("~/code/Rcpp_utils/test/");

# load functions
Rcpp::sourceCpp('../code/convertToSVMLite.cpp');
source('../code/generateRandomSparseMatrix.R');

# generate a random sparse matrix
data = generateRandomSparseMatrix(ratio = 0.1, nrow = 10000, ncol = 10000);

# get labels
l = round(runif(100, 0, 1));

# convert to SVM lite format
ptm = proc.time();
svm_lite = convertToSVMLite(data, l);
print(proc.time()-ptm);
