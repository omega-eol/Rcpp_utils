// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppArmadillo)]]
#define ARMA_64BIT_WORD
#include <RcppArmadillo.h>
#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

typedef Eigen::MappedSparseMatrix<double> MSpMat;
typedef MSpMat::InnerIterator InIterMat;

// convert sparse matrix to SVM lite format
// [[Rcpp::export]]
CharacterVector convertToSVMLite(MSpMat X, NumericVector labels = NumericVector::create(), bool Cstyle = false){
     // number of columns
     int ncol = X.cols();
     int n_labels = labels.size();
     
     // output vector
     CharacterVector out(ncol);
     
     if (Cstyle) { // col index will start from 0
          // for each column
          for (int j = 0; j < ncol; j++) {
             // start from empty string stream
             std::ostringstream os;
             
             // add lebels if needed
             if (n_labels > 0) {
                  int l = labels[j];
                  if (l == 0) l = -1;
                  os << l << " ";
             };
             
             // for each non-zero element in the j column
             for (InIterMat i_(X, j); i_; ++i_) {
                  os << i_.row() << ":" << i_.value() <<" ";
             };
             
             out[j] = os.str();
          }; // end j loop
          
     } else { // col index will start from 1
          
          // for each column
          for (int j = 0; j < ncol; j++) {
             // start from empty string stream
             std::ostringstream os;
             
             // add lebels if needed
             if (n_labels > 0) {
                  int l = labels[j];
                  if (l == 0) l = -1;
                  os << l << " ";
             };
             
             // for each non-zero element in the j column
             for (InIterMat i_(X, j); i_; ++i_) {
                  os << i_.row() + 1 << ":" << i_.value() <<" ";
             };
             
             out[j] = os.str();
          }; // end j loop
     }; // end of if statement
     
     return out;
}