#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"

// map between colour and opacity values
std::unordered_map< std::string, std::string > line_colours = {
  { "stroke_colour", "stroke_opacity" }
};

// vector of possible legend components
Rcpp::StringVector line_legend = Rcpp::StringVector::create(
  "stroke_colour"
);

// [[Rcpp::export]]
Rcpp::List rcpp_widget_line(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = line_defaults( data_rows );

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    line_colours,
    line_legend,
    data_rows,
    geometry_columns
  );
}
