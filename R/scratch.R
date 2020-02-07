
## design:
## - sf object converted to long data.frame
## - one row per coordinate
## - colours (and other data) get repeated per attribute

# # l <- widget_point( data = widget_capitals[1:2,], legend = FALSE )
# # spatialwidget:::widget_point_columnar(data = widget_capitals[1:2, ] )
#
# df <- sfheaders::sf_to_df( widget_capitals )
#
# res <- spatialwidget:::widget_point_columnar(
#   data = df[1:2, ]
#   , lon = "x"
#   , lat = "y"
#   )




# library(Rcpp)
#
# cppFunction(
#   code = '
#     Rcpp::NumericVector mat_to_vec( Rcpp::NumericMatrix mat ) {
#
#       Rcpp::NumericMatrix mat2 = Rcpp::transpose( mat );
#       mat2.attr("dim") = R_NilValue;
#
#       Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( mat2 );
#       return nv;
#
#     }
#   '
# )
#
# m <- matrix(1:8, ncol = 2)
#
# mat_to_vec( m )

