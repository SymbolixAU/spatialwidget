#ifndef SPATIALWIDGET_DEFAULTS_H
#define SPATIALWIDGET_DEFAULTS_H

#include <Rcpp.h>

Rcpp::NumericVector default_stroke_colour( int n );

Rcpp::NumericVector default_stroke_width( int n );

Rcpp::NumericVector default_fill_colour( int n );

Rcpp::NumericVector default_fill_width( int n );

Rcpp::NumericVector default_fill_opacity( int n );

Rcpp::NumericVector default_radius( int n );

Rcpp::List point_defaults( int n );

Rcpp::List line_defaults( int n );

Rcpp::List polygon_defaults( int n );

#endif
