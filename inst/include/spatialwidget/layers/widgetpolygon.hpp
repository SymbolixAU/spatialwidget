#ifndef SPATIALWIDGET_WIDGETPOLYGON_H
#define SPATIALWIDGET_WIDGETPOLYGON_H

#include <Rcpp.h>
namespace spatialwidget {
namespace widgetpolygon {

// map between colour and opacity values
std::unordered_map< std::string, std::string > polygon_colours = {
  { "fill_colour", "fill_opacity" },
  { "stroke_colour", "stroke_opacity"}
};

// vector of possible legend components
Rcpp::StringVector polygon_legend = Rcpp::StringVector::create(
  "fill_colour", "stroke_colour"
);

} // namespace widgetpolygon
} // namespace spatialwidget

#endif
