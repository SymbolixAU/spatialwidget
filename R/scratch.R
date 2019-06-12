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
#   # rcpp_make_colours(
#   #   Rcpp::List& lst_params,
#   #   Rcpp::List& params,
#   #   Rcpp::DataFrame& data,
#   #   Rcpp::List& lst_defaults,
#   #   int col_index,
#   #   SEXP& palette_type,
#   #   Rcpp::NumericVector& alpha,
#   #   std::string& colour_name,
#   #   bool& include_legend,
#   #   int legend_digits = 2
#   # )
#
  # data <- data.frame(
  #   lat = c(49.25,49.2)
  #   , lng = c(-123.1,-123)
  #   , value = factor( c("A","B"), levels = c("B","A"))
  # )
  #
  # str( data$value )
  #
  # widget_point(data, fill_colour = "value", lon = "lng", lat = "lat")
  #
  # str( data$value )
#
# })
