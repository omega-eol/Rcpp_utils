// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppArmadillo)]]
#define ARMA_64BIT_WORD
#include <RcppArmadillo.h>
#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

typedef Eigen::MappedSparseMatrix<double> MSpMat;
typedef MSpMat::InnerIterator InIterMat;
typedef std::pair<double,int> Rpair;
bool Rcomparator ( const Rpair& l, const Rpair& r) { return l.first > r.first; };

// [[Rcpp::export]]
Rcpp::List row_nth_largest_filter(MSpMat X, int nth = 1){
     // number of columns
     int ncol = X.cols();
     
     // keep track on indices
     int nonzero_count = X.nonZeros();
     IntegerVector x(nonzero_count);
     IntegerVector y(nonzero_count);
     NumericVector coeff(nonzero_count);
     
     // for each column
     int index = 0;
     for (int j = 0; j < ncol; j++) {
          // find number of elements in the j column
          int col_size = 0;
          for (InIterMat i_(X, j); i_; ++i_) col_size++;
          
          if (nth < col_size) {
               // array of values and indices in column j
               std::vector<Rpair> col_values(col_size);
               int i = 0;
               for (InIterMat i_(X, j); i_; ++i_) {
                    col_values[i].first = i_.value();
                    col_values[i].second = i_.index(); // row index from 0 to nrow-1
                    i++;
               };
               
               // sort the vector of pairs
               std::sort(col_values.begin(), col_values.end(), Rcomparator);
               
               // generate indices for the filtered sparce matrix
               for (int i = 0; i < nth; i++) {
                    x[index] = col_values[i].second+1;
                    y[index] = j+1;
                    coeff[index] = col_values[i].first;
                    index++;
               };
               
          } else { // we do not need to sort, we just copy all values
                   // for all non-zero values in column j
                   for (InIterMat i_(X, j); i_; ++i_) {
                        x[index] = i_.row()+1;
                        y[index] = i_.col()+1;
                        coeff[index] = i_.value();
                        index++;
                   };              
          }; // end nth < col_size
          
     }; // end j loop
     
     //output
     Rcpp::List list = Rcpp::List::create(Rcpp::Named("x") = x, 
                                          Rcpp::Named("y") = y, 
                                          Rcpp::Named("coeff") = coeff, 
                                          Rcpp::Named("nonZeros") = index); 
     return(list);
}

