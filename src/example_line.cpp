#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"

// map between colour and opacity values
std::unordered_map< std::string, std::string > line_colours = {
  { "stroke_colour", "stroke_opacity" }
};

// vector of possible legend components
Rcpp::StringVector line_legend = Rcpp::StringVector::create(
  "stroke_colour"
);

Rcpp::NumericVector default_stroke_colour( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::NumericVector default_stroke_width( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::List line_defaults( int n ) {
  return Rcpp::List::create(
   Rcpp::_["stroke_colour"] = default_stroke_colour( n ),
   Rcpp::_["stroke_width"] = default_stroke_width( n )
  );
}

// [[Rcpp::export]]
Rcpp::List line_example_geojson(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = line_defaults( data_rows );

  return spatialwidget::api::create_geojson(
    data, params,
    defaults,
    line_colours, line_legend,
    data_rows,
    geometry_columns
  );
}
