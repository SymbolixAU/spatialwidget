// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"


/*
 * construct params
 *
 * Determins if the \code{params} are columns of \code{data}, their column index in
 * \code{data} (or -1 if not a column), and their SEPX data type
 *
 * @value
 */
// [[Rcpp::export]]
Rcpp::List rcpp_construct_params(
    Rcpp::DataFrame& data,
    Rcpp::List& params
  ) {
  return spatialwidget::parameters::construct_params(data, params);
}


/*
 * params to data
 *
 *
 */
// [[Rcpp::export]]
Rcpp::List rcpp_params_to_data(
    Rcpp::DataFrame& data,                // user-supplied data
    Rcpp::List& params,                   // list of parameters from calling function
    Rcpp::List& lst_defaults,
    Rcpp::StringVector layer_legend,     // vector of colours to use in the legend
    int data_rows,
    Rcpp::StringVector parameter_exclusions,
    bool factors_as_string
  ) {

  // this fails when used as an argument to the function!?
  std::unordered_map< std::string, std::string > colour_columns = {
    {"fill_colour","fill_opacity"},{"stroke_colour","stroke_opacity"}
  };

  Rcpp::IntegerVector repeats(1); // not used
  R_xlen_t total_colours = 0; // not used

  return spatialwidget::parameters::parameters_to_data(
    data, params, lst_defaults, colour_columns, layer_legend,
    data_rows, parameter_exclusions, repeats, total_colours, factors_as_string
  );
}
