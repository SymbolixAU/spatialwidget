# context("colours")
#
# test_that("colours correctly made",{
#
#   df <- spatialwidget::widget_capitals
#   l <- list(fill_colour = "country", stroke_colour = "capital", legend = T)
#   p <- spatialwidget:::rcpp_construct_params( data = df, params = l)
#   pn <- names( l )
#   ll <- c("fill_colour","stroke_colour")
#
#   lst_legend_list <- spatialwidget:::rcpp_construct_legend_list(
#     lst_params = p
#     , params = l
#     , param_names = pn
#     , legend_types = ll
#   )
#
#   rcpp_make_colours(
#     Rcpp::List& lst_params,
#     Rcpp::List& params,
#     Rcpp::DataFrame& data,
#     Rcpp::List& lst_defaults,
#     int col_index,
#     SEXP& palette_type,
#     Rcpp::NumericVector& alpha,
#     std::string& colour_name,
#     bool& include_legend,
#     int legend_digits = 2
#   )
#
# })
#
#
# library(quadmesh)
# library(raster)
# ## dummy raster
# rr <- setExtent(raster::raster(matrix(sample(1:12), 3)), raster::extent(0, 4, 0, 3))
# qm <- quadmesh(rr * 10000)  ## something suitably exaggerated
#
# geo <- spatialwidget:::rcpp_to_geojson_mesh(qm, c("vb","ib"))
# geo
#
# jsonify::validate_json( geo )
#
# js <- widget_polygon( widget_melbourne[1:3, ])
#
#
