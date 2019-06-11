#include <Rcpp.h>
using namespace Rcpp;

#include "spatialwidget/legend/legend.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_construct_legend_list(
    Rcpp::List& lst_params,
    Rcpp::List& params,
    Rcpp::StringVector& param_names,
    Rcpp::StringVector& legend_types
  ) {
  return spatialwidget::legend::construct_legend_list( lst_params, params, param_names, legend_types );
}


// [[Rcpp::export]]
std::string rcpp_set_legend_option(
  Rcpp::List& opts,
  std::string& option,
  std::string value,
  std::string& colour_name
  ) {
  spatialwidget::legend::set_legend_option(opts, option, value, colour_name);
  return value;
}
