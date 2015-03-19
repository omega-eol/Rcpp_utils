# clear memory
rm(list=ls());

# set working directory
setwd("~/code/Rcpp_utils/test/");

# load function
source('../code/generateRandomSparseMatrix.R');
Rcpp::sourceCpp('../code/idfTransform.cpp');

# generate a random sparse matrix
n = 20000;
data = generateRandomSparseMatrix(ratio = 0.5, nrow = n, ncol = 1000);

# find IDFs
cc = colSums(data>0);
idf  = log(n/(cc+1e-10));

# transform
ptm = proc.time();
res1 = idfTransform(data, idf);
print(proc.time()-ptm);

ptm = proc.time();
res2 = norm_aug_tfidf(data, idf);
print(proc.time()-ptm);

