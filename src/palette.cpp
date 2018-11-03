#include <Rcpp.h>
#include "spatialwidget/palette/palette.hpp"

/*
 * resolve palette
 *
 * @param lst_params named list( parameter = c(), parameter_type = c(), data_column_index = c() )
 * @param params the values supplied by the user when calling the function
 *
 * @return either the palette value supplied by the user, or the default "viridis"
 *
 */
// [[Rcpp::export]]
Rcpp::StringVector rcpp_resolve_palette( Rcpp::List lst_params, Rcpp::List params ) {
  SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );
  if ( TYPEOF( pal) == STRSXP ) {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( pal );
    return sv;
  }
  return R_NilValue;
}
