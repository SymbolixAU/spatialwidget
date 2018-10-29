

## TODO

# sf inputs, geojson outputs

# library(sf)
# library(mapdeck) ## for roads data
#
# sf_line <- mapdeck::roads
#
# l <- list()
# l[["stroke_colour"]] <- "RIGHT_LOC"
#
#
# ## the list of parameters should include the geometry columns,
# l[["myPathGeometry"]] <- "geometry"       ## a geometry column
#
# ## and you need topass in those parameter names which inlcude the geometry columns
#
# js_data <- spatialwidget:::line_example_geojson( sf_line[1, ], l, c("myPathGeometry") )
# str(js_data)

# if you have multiple geometry columns, you need to pass in all of them (for example, if plotting a 'from' & 'to' arc)
#
# n <- 5
# a_point <- function() {
#   lon <- sample(-180:180, size = 1)
#   lat <- sample(-90:90, size = 1)
#   paste0('{"type":"Point","coordinates":[',lon,',',lat,']}')
# }
#
# geojson <- paste0("[",paste0(sapply(seq_len(n), function(x) a_point() ), collapse = ","),"]")
#
# sf <- geojsonsf::geojson_sf( geojson )
# sf$id <- 1:n
#
#
# data <- sf[1:n, ]
# params <- l
# defaults <- list("fill_colour" = rep(1.0, n), "radius" = rep(1.0, n) )
# colours <- matrix(c("fill_colour", "fill_opacity"), ncol = 2)
# legend <- "fill_colour"
# geometry <- "myPathGeometry"
#
# spatialwidget:::spatialwidget_geojson(
#   data
#   , params
#   , defaults
#   , colours
#   , legend
#   , geometry
#   )



# spatialwidget:::spatialwidget_geojson(
#   Rcpp::DataFrame data,
#   Rcpp::List params,
#   Rcpp::List defaults,
#   Rcpp::StringMatrix colours,
#   Rcpp::StringVector legend,
#   Rcpp::StringVector geometry)
