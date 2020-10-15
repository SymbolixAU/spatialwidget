#ifndef SPATIALWIDGET_UTILS_FILL_H
#define SPATIALWIDGET_UTILS_FILL_H

#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace fill {

  inline Rcpp::StringVector fill_vector( Rcpp::String& x, R_xlen_t n ) {
    Rcpp::StringVector v( n, x );
    return v;
  }

  template< int RTYPE >
  inline Rcpp::Vector< RTYPE > fill_vector( Rcpp::Vector< RTYPE >& x, R_xlen_t n ) {
    Rcpp::Vector< RTYPE > v( n, x[0] );
    return v;
  }

  inline void fill_vector(
      Rcpp::List& lst_defaults,
      Rcpp::String& param_name,
      SEXP& value,
      R_xlen_t n_rows
  ) {

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
