

## TODO

# # sf inputs, geojson outputs
#
# library(sf)
# library(mapdeck) ## for roads data
# sf_line <- mapdeck::roads
#
# l <- list()
# l[["stroke_colour"]] <- "RIGHT_LOC"
# l[["geometry"]] <- "geometry"       ## the geometry column
#
# js_data <- spatialwidget:::line_example_geojson( sf_line, l )
# str(js_data)

# List of 2
# $ data  : 'geojson' chr "[{\"type\":\"Feature\",\"properties\":{\"stroke_colour\":\"#46317EFF\"},\"geometry\":{\"type\":\"LineString\",\"| __truncated__
# $ legend: 'json' chr "{\"stroke_colour\":[false]}"

## tests
## colorus and opacities
## Z& M attributes in Geojosn result
