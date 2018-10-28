// #include <Rcpp.h>
// #include "spatialwidget/spatialwidget.hpp"
//
//
// // [[Rcpp::export]]
// Rcpp::List spatialwidget_geojson( Rcpp::DataFrame data, Rcpp::List params, Rcpp::List defaults ) {
//
//   int data_rows = data.nrows();
//
//   return spatialwidget::api::create_geojson(
//     data, params, defaults,
//     path_columns, path_colours, path_legend,
//     data_rows
//   );
// }
//
//
// // [[Rcpp::export]]
// Rcpp::List rcpp_spatialwidget_polylines( Rcpp::DataFrame data, Rcpp::List params, Rcpp::List defaults ) {
//
//   int data_rows = data.nrows();
//
//   return spatialwidget::api::create_polyline(
//     data, params, lst_defaults,
//     path_columns, path_colours, path_legend,
//     data_rows
//   );
// }
//
