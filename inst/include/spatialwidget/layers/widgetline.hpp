#ifndef SPATIALWIDGET_WIDGETLINE_H
#define SPATIALWIDGET_WIDGETLINE_H

#include <Rcpp.h>
namespace spatialwidget {
namespace widgetline {

// map between colour and opacity values
std::unordered_map< std::string, std::string > line_colours = {
  { "stroke_colour", "stroke_opacity" }
};

// vector of possible legend components
Rcpp::StringVector line_legend = Rcpp::StringVector::create(
  "stroke_colour"
);

} // namespace widgetline
} // namespace spatialwidget

#endif
