#ifndef SPATIALWIDGET_UTILS_FILL_H
#define SPATIALWIDGET_UTILS_FILL_H

#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace fill {

  inline Rcpp::LogicalVector fill_vector( Rcpp::LogicalVector& x, int n ) {
    Rcpp::LogicalVector v( n, x[0] );
    return v;
  }

  inline Rcpp::IntegerVector fill_vector( Rcpp::IntegerVector& x, int n ) {
    Rcpp::IntegerVector v( n, x[0] );
    return v;
  }

  inline Rcpp::NumericVector fill_vector( Rcpp::NumericVector& x, int n ) {
    Rcpp::NumericVector v( n, x[0] );
    return v;
  }

  inline Rcpp::StringVector fill_vector( Rcpp::StringVector& x, int n ) {
    Rcpp::StringVector v( n, x[0] );
    return v;
  }

  inline Rcpp::StringVector fill_vector( Rcpp::String& x, int n ) {
    Rcpp::StringVector v( n, x );
    return v;
  }

  inline void fill_vector(
      Rcpp::List& lst_defaults,
      Rcpp::String& param_name,
      SEXP& value,
      int n_rows ) {

    switch( TYPEOF( value ) ) {
    case 10: { // LGLSXP
    Rcpp::LogicalVector l = Rcpp::as< Rcpp::LogicalVector >( value );
    lst_defaults[ param_name ] = fill_vector( l, n_rows );
    return;
  }
    case 13: { // INTSXP
      Rcpp::IntegerVector i = Rcpp::as< Rcpp::IntegerVector >( value );
      lst_defaults[ param_name ] = fill_vector( i, n_rows );
      return;
    }
    case 14: { // REALSXP
      Rcpp::NumericVector n = Rcpp::as< Rcpp::NumericVector >( value );
      lst_defaults[ param_name ] = fill_vector( n, n_rows );
      return;
    }
    default: {
      Rcpp::StringVector s = Rcpp::as< Rcpp::StringVector >( value );
      lst_defaults[ param_name ] = fill_vector( s, n_rows );
      return;
    }
    }
  }

} // namespace fill
} // namespace utils
} // namespace spatialwidget

#endif
