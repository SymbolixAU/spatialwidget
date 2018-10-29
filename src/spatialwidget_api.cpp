#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"


// [[Rcpp::export]]
Rcpp::List spatialwidget_geojson(
    Rcpp::DataFrame data,
    Rcpp::List params,
    Rcpp::List defaults,
    Rcpp::StringMatrix colours,
    Rcpp::StringVector legend,
    Rcpp::StringVector geometry) {

  if ( colours.ncol() != 2 ) {
    Rcpp::stop("incorrect colour dimensions");
  }

  int r = colours.nrow();
  int i;
  int data_rows = data.nrows();
  std::unordered_map< std::string, std::string > layer_colours( r );

  // Rcpp::Rcout << "r: " << r << std::endl;
  // Rcpp::Rcout << "data_rows: " << data_rows << std::endl;

  for ( i = 0; i < r; i++ ) {
    Rcpp::String x = colours(i, 0);
    Rcpp::String y = colours(i, 1);
    // Rcpp::Rcout << "x: " << x.get_cstring() << std::endl;
    // Rcpp::Rcout << "y: " << y.get_cstring() << std::endl;
    layer_colours.insert( {x ,y } );
  }

  return spatialwidget::api::create_geojson(
    data, params,
    defaults,
    layer_colours, legend,
    data_rows,
    geometry
  );
}


