

## TODO

# sf inputs, geojson outputs

# library(sf)
# library(mapdeck) ## for roads data
#
# sf_line <- mapdeck::roads
# sf_line$dte <- sample( seq( as.Date("2018-01-01"), as.Date("2018-12-30"), length.out = 300), size = nrow(sf_line), replace = T )
# sf_line$psx <- sample( seq( as.POSIXct("2018-01-01 00:00:00"), as.POSIXct("2018-12-30 00:00:00"), length.out = 300), size = nrow(sf_line), replace = T )
#
# l <- list()
# l[["stroke_colour"]] <- "dte"
#
#
# ## the list of parameters should include the geometry columns,
# l[["myPathGeometry"]] <- "geometry"       ## a geometry column
# l[["legend"]] <- TRUE
# ## and you need topass in those parameter names which inlcude the geometry columns
#
# data_types <- vapply( sf_line, function(x) class(x)[[1]], "")
#
# js_data <- spatialwidget:::line_example_geojson( sf_line[1:10, ], data_types, l, c("myPathGeometry") )
# str(js_data)

## need to grab the R data type(s) used for colouring, so we can then specify the 'format' argument.
## so, in R, use vapply(data, class, "")

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
