#include <Rcpp.h>
#include "spatialwidget/utils/utils.hpp"


/*
 * fill_single_vector
 *
 * @param value SEXP - value to fill in the vector
 * @param n_rows int - number of values to fill
 */
// [[Rcpp::export]]
Rcpp::List rcpp_fill_single_vector(
    Rcpp::List lst_defaults,
    Rcpp::String param_name,
  SEXP value,
  int n_rows) {

  spatialwidget::utils::fill_single_vector( lst_defaults, param_name, value, n_rows );
  return lst_defaults;
}

/*
 * find_character_index_in_vector
 *
 * @param sv StringVector
 * @param to_find const char* value to find in sv
 *
 * @return index of to_find in sv
 */
// [[Rcpp::export]]
int rcpp_find_character_index_in_vector( Rcpp::StringVector sv, const char* to_find ) {
  return spatialwidget::utils::find_character_index_in_vector( sv, to_find );
}
