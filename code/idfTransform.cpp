// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppArmadillo)]]
#define ARMA_64BIT_WORD
#include <RcppArmadillo.h>
#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

typedef Eigen::SparseMatrix<double> SpMat;
typedef SpMat::InnerIterator InIteratorSpMat;

// [[Rcpp::export]]
NumericVector colMax(SpMat X) { // find maximum value in each column
     // number of columns
     int ncol = X.cols();
     
     // allocate memory
     NumericVector col_m(ncol);
     
     // find col max
     for (int j = 0; j < ncol; j++) {
          col_m[j] = std::numeric_limits<double>::lowest();
          for (InIteratorSpMat i_(X, j); i_; ++i_) {
               if (i_.value() > col_m[j]) col_m[j] = i_.value();
          };
     };
     
     return(col_m);
};

// [[Rcpp::export]]
NumericVector rowMax(SpMat X) { // find maximum value in each column
     return(colMax(X.transpose()));
};

// [[Rcpp::export]]
SpMat idfTransform(SpMat X, NumericVector idf) {
     
     // number of columns
     int ncol = X.cols();
     
     // find maximum value in each row
     NumericVector rm = rowMax(X);
     
     // for each column
     for (int j = 0; j < ncol; j++) {
          // for each row (with non-zero element) in the current colunm j
          for (InIteratorSpMat i_(X, j); i_; ++i_) {
               i_.valueRef() = (0.5+0.5*i_.value()/rm[i_.row()])*idf[j]; // augmented frequency
          };
     };
     
     return(X);
};

// [[Rcpp::export]]
S4 norm_aug_tfidf(S4 mat, NumericVector idf) { // find maximum value in each row
     IntegerVector dims = mat.slot( "Dim" );
     IntegerVector i = mat.slot( "i" );
     IntegerVector p = mat.slot( "p" );
     NumericVector x = mat.slot( "x" );
     int nrow = dims[0], ncol = dims[1] ;
     
     // find row max first
     NumericVector i_max(nrow);
     for(int j = 0; j < ncol; ++j) {
         for (int k = p[j]; k < p[j + 1]; ++k) { 
              if (x[k] > i_max(i[k])) i_max(i[k]) = x[k]; 
         }
     };
     
     // copy values from mat to res and normalized them
     NumericVector x_new(x.size());
     for(int j = 0; j < ncol; ++j) {
         for (int k = p[j]; k < p[j + 1]; ++k) {
              int row = i[k];
              x_new(k) = (0.5+0.5*x[k]/i_max(row))*idf(j);
         }
     };
     
     S4 m_out = clone(mat);
     m_out.slot( "x" ) = x_new;
     return m_out;
};


