#ifndef SPATIALWIDGET_WIDGETPOINT_H
#define SPATIALWIDGET_WIDGETPOINT_H

#include <Rcpp.h>
namespace spatialwidget {
namespace widgetpoint {

// map between colour and opacity values
  std::unordered_map< std::string, std::string > point_colours = {
    { "fill_colour", "fill_opacity" }
  };

  // vector of possible legend components
  Rcpp::StringVector point_legend = Rcpp::StringVector::create(
    "fill_colour"
  );

} // namespace widgetpoint
} // namespace spatialwidget

#endif
