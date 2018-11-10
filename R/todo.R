


## benchmarking defaults vs no defaults
## - this is to test if allocating a default list element is worth it

# lons <- seq(-180,180, by = 0.001)
# lats <- seq(-90, 90, by = 0.001)
# n <- 1e6
# df <- data.frame(
#   lon = sample(lons, size = n, replace = T)
#   , lat = sample(lats, size = n, replace = T)
#   , radius = rnorm(n = n)
#   , fill_colour = rnorm(n = n)
#   , fill_opacity = rnorm(n = n)
# )
# data_types <- vapply(df, function(x) class(x)[[1]], "")
#
# l <- list()
# l[["lon"]] <- "lon"
# l[["lat"]] <- "lat"
# l[["fill_colour"]] <- "fill_colour"
# l[["fill_opacity"]] <- "fill_opacity"
# l[["radius"]] <- "radius"
# l[["json_legend"]] <- FALSE
#
# geometry_columns <- list(mygeom = c("lon","lat"))
#
# library(microbenchmark)
#
# microbenchmark(
#
#   defaults = {
#     js <- spatialwidget:::rcpp_widget_point_df_defaults(
#       data = df,
#       data_types = data_types,
#       params = l,
#       geometries = geometry_columns,
#       jsonify_legend = TRUE
#     )
#   },
#   no_defaults = {
#     js <- spatialwidget:::rcpp_widget_point_df(
#       data = df,
#       data_types = data_types,
#       params = l,
#       geometries = geometry_columns,
#       jsonify_legend = TRUE
#     )
#   },
#   times = 5
# )
#
# # Unit: seconds
# #        expr      min       lq     mean   median       uq      max neval
# #    defaults 6.447032 6.634274 6.640007 6.659364 6.722150 6.737213     5
# # no_defaults 5.743852 5.818002 5.912442 5.879783 5.996567 6.124006     5


