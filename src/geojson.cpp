#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"


// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_sf( Rcpp::DataFrame df, Rcpp::StringVector geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( df, geometries );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_df( Rcpp::DataFrame df, Rcpp::List geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( df, geometries );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_downcast( Rcpp::DataFrame df, std::string geometry_column ) {
  return spatialwidget::geojson::to_geojson_downcast_atomise( df, geometry_column );
}
