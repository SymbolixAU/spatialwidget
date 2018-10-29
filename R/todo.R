

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

## if you have multiple geometry columns, you need to pass in all of them (for example, if plotting a 'from' & 'to' arc)




# List of 2
# $ data  : 'geojson' chr "[{\"type\":\"Feature\",\"properties\":{\"stroke_colour\":\"#46317EFF\"},\"geometry\":{\"type\":\"LineString\",\"| __truncated__
# $ legend: 'json' chr "{\"stroke_colour\":[false]}"

## tests
## colorus and opacities
## Z& M attributes in Geojosn result
