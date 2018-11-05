#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"

// map between colour and opacity values
std::unordered_map< std::string, std::string > point_colours = {
  { "fill_colour", "fill_opacity" }
};

// vector of possible legend components
Rcpp::StringVector point_legend = Rcpp::StringVector::create(
  "fill_colour"
);

// [[Rcpp::export]]
Rcpp::List rcpp_widget_point(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    geometry_columns
  );
}


// [[Rcpp::export]]
Rcpp::List rcpp_widget_point_df(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::List geometries) {
    // Rcpp::StringVector lons,
    // Rcpp::StringVector lats) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  // Rcpp::Rcout << "data rows: " << data_rows << std::endl;
  // Rcpp::Rcout << "data cols: " << data.ncol() << std::endl;

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    geometries
  );
}
