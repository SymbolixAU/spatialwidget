#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"


// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson( Rcpp::DataFrame sf, std::string geometry ) {
  return spatialwidget::geojson::to_geojson( sf, geometry );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_sf( Rcpp::DataFrame sf, Rcpp::StringVector geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( sf, geometries );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_df( Rcpp::DataFrame df, Rcpp::List geometries ) {
  return spatialwidget::geojson::to_geojson_atomise( df, geometries );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_geojson_dfz( Rcpp::DataFrame df, Rcpp::List geometries ) {
  return spatialwidget::geojson::to_geojson_z_atomise( df, geometries );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_downcast( Rcpp::DataFrame sf, std::string geometry_column ) {
  return spatialwidget::geojson::to_geojson_downcast_atomise( sf, geometry_column );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson_multi_column_downcast( Rcpp::DataFrame sf, Rcpp::StringVector geometries ) {
  return spatialwidget::geojson::to_geojson_downcast_atomise( sf, geometries );
}
