#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"
#include "spatialwidget/layers/widgetpoint.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_widget_point(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns,
    bool jsonify_legend ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
  Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    geometry_columns,
    jsonify_legend
  );
}

// [[Rcpp::export]]
Rcpp::List rcpp_widget_point_df(
    Rcpp::DataFrame data,
    Rcpp::List data_types,
    Rcpp::List params,
    Rcpp::List geometries,
    bool jsonify_legend) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
  Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;

  return spatialwidget::api::create_geojson(
    data,
    data_types,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    geometries,
    jsonify_legend
  );
}
