#define ARMA_64BIT_WORD
#include <Rcpp.h>
#include <string>

using namespace Rcpp;

// Converts sparse matrix to binaty sparse matrix
// [[Rcpp::export]]
S4 toBinarySparseMatrix(S4 mat){
     NumericVector x = mat.slot( "x" );
     
     // copy values from mat to res and normalized them
     int n = x.size();
     NumericVector x_new(n);
     for(int j = 0; j < n; ++j) x_new[j] = 1;

     S4 m_out = clone(mat);
     m_out.slot( "x" ) = x_new;
     return(m_out);
};
