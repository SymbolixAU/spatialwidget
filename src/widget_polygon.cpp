#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"

// map between colour and opacity values
std::unordered_map< std::string, std::string > polygon_colours = {
  { "stroke_colour", "stroke_opacity" },
  { "fill_colour", "fill_opacity"}
};

// vector of possible legend components
Rcpp::StringVector polygon_legend = Rcpp::StringVector::create(
  "stroke_colour", "fill_colour"
);


// [[Rcpp::export]]
Rcpp::List rcpp_widget_polygon(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = polygon_defaults( data_rows );

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    polygon_colours,
    polygon_legend,
    data_rows,
    geometry_columns
  );
}
