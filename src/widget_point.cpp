#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"
#include "spatialwidget/layers/widgetpoint.hpp"

#include "sfheaders/df/sf.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_widget_point(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns,
    bool jsonify_legend,
    int digits
  ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
  Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;
  Rcpp::StringVector parameter_exclusions = Rcpp::StringVector::create("legend","legend_options","palette","na_colour");

  return spatialwidget::api::create_geojson(
    data,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    parameter_exclusions,
    geometry_columns,
    jsonify_legend,
    digits
  );
}

// [[Rcpp::export]]
Rcpp::List rcpp_widget_point_df(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::List geometries,
    bool jsonify_legend,
    int digits
  ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
  Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;
  Rcpp::StringVector parameter_exclusions = Rcpp::StringVector::create("legend","legend_options","palette","na_colour");

  return spatialwidget::api::create_geojson(
    data,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    parameter_exclusions,
    geometries,
    jsonify_legend,
    digits
  );
}


// [[Rcpp::export]]
Rcpp::List rcpp_widget_point_df_columnar(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::List geometry_columns,
    bool jsonify_legend,
    int digits
) {

  int data_rows = data.nrows();
  Rcpp::List defaults = point_defaults( data_rows );

  std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
  Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;
  Rcpp::StringVector parameter_exclusions = Rcpp::StringVector::create("legend","legend_options","palette","na_colour");

  return spatialwidget::api::create_columnar(
    data,
    params,
    defaults,
    point_colours,
    point_legend,
    data_rows,
    parameter_exclusions,
    geometry_columns,
    jsonify_legend,
    digits
  );
}

// // [[Rcpp::export]]
// Rcpp::List rcpp_widget_point_sf_columnar(
//     Rcpp::DataFrame data,
//     Rcpp::List params,
//     Rcpp::List geometries,
//     bool jsonify_legend,
//     int digits
// ) {
//   Rcpp::DataFrame df = sfheaders::df::sf_to_df( data );
//   //Rcpp::List df_geometries = Rcpp::List::create("x","y");
//
//   //return df;
//
//   int data_rows = df.nrows();
//   Rcpp::List defaults = point_defaults( data_rows );
//
//   std::unordered_map< std::string, std::string > point_colours = spatialwidget::widgetpoint::point_colours;
//   Rcpp::StringVector point_legend = spatialwidget::widgetpoint::point_legend;
//   Rcpp::StringVector parameter_exclusions = Rcpp::StringVector::create("legend","legend_options","palette","na_colour");
//
//   return spatialwidget::api::create_columnar(
//     df,
//     params,
//     defaults,
//     point_colours,
//     point_legend,
//     data_rows,
//     parameter_exclusions,
//     geometries,
//     jsonify_legend,
//     digits
//   );
// }
