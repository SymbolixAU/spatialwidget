#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/spatialwidget_defaults.hpp"
#include "spatialwidget/layers/widgetline.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_widget_line(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::StringVector geometry_columns,
    bool jsonify_legend ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = line_defaults( data_rows );

  std::unordered_map< std::string, std::string > line_colours = spatialwidget::widgetline::line_colours;
  Rcpp::StringVector line_legend = spatialwidget::widgetline::line_legend;
  Rcpp::StringVector parameter_exclusions = Rcpp::StringVector::create("legend","legend_options","palette","na_colour");

  return spatialwidget::api::create_geojson(
    data,
    params,
    defaults,
    line_colours,
    line_legend,
    data_rows,
    parameter_exclusions,
    geometry_columns,
    jsonify_legend
  );
}
