#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"

// [[Rcpp::export]]
Rcpp::StringVector rcpp_to_geojson_mesh(
  Rcpp::List& mesh,
  Rcpp::StringVector vertices
) {

  return spatialwidget::geojson::to_geojson_mesh( mesh, vertices );

}
