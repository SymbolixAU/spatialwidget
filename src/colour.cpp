#include <Rcpp.h>
using namespace Rcpp;

#include "spatialwidget/colour/colour.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_make_colours(
    Rcpp::List& lst_params,
    Rcpp::List& params,
    Rcpp::DataFrame& data,
    Rcpp::List& lst_defaults,
    int col_index,
    SEXP& palette_type,
    Rcpp::NumericVector& alpha,
    std::string& colour_name,
    bool& include_legend,
    int legend_digits = 2
  ) {
  return spatialwidget::colour::make_colours(
    lst_params, params, data, lst_defaults, col_index, palette_type, alpha, colour_name,
    include_legend, legend_digits
  );
}
