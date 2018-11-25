#include <Rcpp.h>

#include "spatialwidget/utils/utils.hpp"

/*
 * fill_single_vector
 *
 * @param value SEXP - value to fill in the vector
 * @param n_rows int - number of values to fill
 */
// [[Rcpp::export]]
Rcpp::List rcpp_fill_vector(
    Rcpp::List lst_defaults,
    Rcpp::String param_name,
  SEXP value,
  int n_rows) {

  spatialwidget::utils::fill::fill_vector( lst_defaults, param_name, value, n_rows );
  return lst_defaults;
}

/*
 * find_character_index_in_vector
 *
 * @param sv StringVector
 * @param to_find StringVector value to find in sv
 *
 * @return index of to_find in sv
 */
// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_where_is( Rcpp::StringVector to_find, Rcpp::StringVector sv ) {
  return spatialwidget::utils::where::where_is( to_find, sv );
}

/*
 * remove_list_elements
 *
 * @param list
 * @param elements
 * @param to_remove
 */
// [[Rcpp::export]]
Rcpp::List rcpp_remove_list_elements( Rcpp::List lst, Rcpp::StringVector to_remove) {
  spatialwidget::utils::remove::remove_list_elements( lst, to_remove );
  return lst;
}

/*
 * is_hex
 */
// [[Rcpp::export]]
Rcpp::LogicalVector is_hex( std::string hex_str ) {
  bool res = spatialwidget::utils::colour::is_hex( hex_str );
  Rcpp::LogicalVector lv(1);
  lv[0] = res;
  return res;
}
