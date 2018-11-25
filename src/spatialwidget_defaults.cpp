#include <Rcpp.h>
#include "spatialwidget/spatialwidget_defaults.hpp"

Rcpp::NumericVector default_stroke_colour( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::NumericVector default_stroke_width( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::NumericVector default_fill_colour( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::NumericVector default_fill_width( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::List line_defaults( int n ) {
  return Rcpp::List::create(
    Rcpp::_["stroke_colour"] = default_stroke_colour( n ),
    Rcpp::_["stroke_width"] = default_stroke_width( n )
  );
}

Rcpp::List polygon_defaults( int n ) {
  return Rcpp::List::create(
    Rcpp::_["stroke_colour"] = default_stroke_colour( n ),
    Rcpp::_["stroke_width"] = default_stroke_width( n ),
    Rcpp::_["fill_colour"] = default_fill_colour( n )
  );
}


Rcpp::List point_defaults( int n ) {
  return Rcpp::List::create(
    Rcpp::_["fill_colour"] = default_fill_colour( n )
  );
}
