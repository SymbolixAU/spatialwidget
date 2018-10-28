#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>

Rcpp::StringVector to_geojson_atomise( Rcpp::DataFrame& sf );

Rcpp::StringVector to_geojson( Rcpp::DataFrame& sf );

Rcpp::StringVector to_geojson_atomise( Rcpp::DataFrame& sf, const char* lon, const char* lat );

Rcpp::StringVector to_geojson( Rcpp::DataFrame& sf, const char* lon, const char* lat );

#endif
