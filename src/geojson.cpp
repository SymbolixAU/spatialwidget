#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"


// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson( Rcpp::DataFrame sf, std::string geometry ) {
  return spatialwidget::geojson::to_geojson( sf, geometry, -1 );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_sf( Rcpp::DataFrame sf, Rcpp::StringVector geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( sf, geometries, -1 );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_df( Rcpp::DataFrame df, Rcpp::List geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( df, geometries, -1 );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_dfz( Rcpp::DataFrame df, Rcpp::List geometries ) {
  return spatialwidget::geojson::to_geojson_z_atomise( df, geometries, -1 );
}

