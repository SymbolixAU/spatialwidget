#include <Rcpp.h>
#include "spatialwidget/data_construction/data_construction.hpp"


/*
 * construct data
 *
 * Creates a data.frame from the user-supplied data object, and the columsn the user
 * has said to use for colouring, stroke, etc.
 *
 */
// [[Rcpp::export]]
Rcpp::DataFrame rcpp_construct_data(
  Rcpp::StringVector param_names,
  Rcpp::List params,
  Rcpp::StringVector data_names,
  Rcpp::List lst_defaults,
  Rcpp::DataFrame data,
  int data_rows) {

  return spatialwidget::construction::construct_data(
    param_names, params, data_names, lst_defaults, data, data_rows
  );

}
