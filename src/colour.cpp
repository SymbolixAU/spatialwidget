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
    int legend_digits = 2,
    std::string colour_format = "hex"
  ) {
  return spatialwidget::colour::make_colours(
    lst_params, params, data, lst_defaults, col_index, palette_type, alpha, colour_name,
    include_legend, legend_digits, colour_format
  );
}

// [[Rcpp::export]]
Rcpp::List rcpp_resolve_colour(
    Rcpp::List& lst_params,
    Rcpp::List& params,
    Rcpp::DataFrame& data,
    Rcpp::List& lst_defaults,
    std::string& colour_name,
    std::string& opacity_name,
    Rcpp::List& lst_legend,
    bool& include_legend,
    std::string colour_format = "hex"
) {
  spatialwidget::colour::resolve_colour(
    lst_params, params, data, lst_defaults, colour_name, opacity_name, lst_legend,
    include_legend, colour_format
  );

  Rcpp::List lst = Rcpp::List::create(
    _["defaults"] = lst_defaults,
    _["legend"] = lst_legend
  );
  return lst;

}
