
#ifndef SPATIALWIDGET_UTILS_FACTORS_H
#define SPATIALWIDGET_UTILS_FACTORS_H

#include <Rcpp.h>


namespace spatialwidget {
namespace utils {
namespace factors {

  inline void factors_to_string( Rcpp::DataFrame& data ) {
    int n_cols = data.ncol();
    int i;
    Rcpp::StringVector col_names = data.names();
    for( i = 0; i < n_cols; i++ ) {
      const char* h = col_names[ i ];
      SEXP v = data[ h ];
      if (Rf_isFactor( v ) ) {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
        data[ h ] = sv;
      }
    }
  }

} // namespace factors
} // namespace utils
} // namespace spatialwidget

#endif
