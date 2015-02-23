# generate random sparse matrix
generateRandomSparseMatrix = function(ratio = 0.05, nrow=1000, ncol=100) {
     # load Matrix library
     library('Matrix');
     
     # number of non-zero element in the matrix
     n = ceiling(nrow*ncol*ratio);
     
     # the coordinates i and j are uniform distribution from 1 to nrow or ncol. Value are normal distr. with mean - 0 and std = 1
     m = sparseMatrix(i = round(runif(n, 1, nrow)), j = round(runif(n, 1, ncol)), x = rnorm(n));
     
     return(m);
};