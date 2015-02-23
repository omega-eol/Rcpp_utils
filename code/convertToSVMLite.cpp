// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppArmadillo)]]
#define ARMA_64BIT_WORD
#include <RcppArmadillo.h>
#include <RcppEigen.h>
#include <Rcpp.h>
#include <string>

using namespace Rcpp;

typedef Eigen::MappedSparseMatrix<double> MSpMat;
typedef MSpMat::InnerIterator InIterMat;

// convert sparse matrix to SVM lite format
// [[Rcpp::export]]
CharacterVector convertToSVMLiteF(MSpMat X, NumericVector labels = NumericVector::create()){ // sparse option
     // number of columns
     int ncol = X.cols();
     int n_labels = labels.size();
     
     // output vector
     CharacterVector out(ncol);
     
     // for each column
     for (int j = 0; j < ncol; j++) {
        // start from empty string
        String line = "";
        
        // add lebels if needed
        if (n_labels > 0) {
             int l = labels[j];
             if (l == 0) l = -1;
             line += std::to_string(l) + " ";
        };
        
        // for each non-zero element in the j column
        for (InIterMat i_(X, j); i_; ++i_) {
             line += std::to_string(i_.row() + 1) + ":" + std::to_string(i_.value()) + " ";
        };
        
        out[j] = line;
     }; // end j loop
     
     return out;
}
