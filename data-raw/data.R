
library(sf)
widget_roads <- mapdeck::roads[1:100, ]
usethis::use_data( widget_roads, overwrite = TRUE )

# library(geojsonsf)
# sf <- geojson_sf("https://symbolixau.github.io/data/geojson/SA2_2016_VIC.json")
# sf <- sf::st_cast( sf, "POLYGON" )
# melbourne <- sf[, c("SA3_NAME16", "GCC_NAME16", "GCC_CODE16", "SA2_MAIN16", "AREASQKM16", "SA2_NAME16", "SA4_CODE16", "SA4_NAME16")]

widget_melbourne <- geojsonsf::geojson_sf( googleway::geo_melbourne )
widget_melbourne <- melbourne[, c("SA2_NAME", "SA3_NAME", "AREASQKM", "geometry")]
usethis::use_data(widget_melbourne, overwrite = T)


library(sf)
widget_capitals <- mapdeck::capitals
widget_capitals <- sf::st_as_sf( capitals, coords = c("lon", "lat"))
usethis::use_data( widget_capitals, overwrite = T)

from <- mapdeck::capitals[ mapdeck::capitals$country == "Australia", ]
to <- mapdeck::capitals[ mapdeck::capitals$country != "Australia", ]

library(sf)

widget_arcs <- cbind(from, to)
widget_arcs <- setNames(widget_arcs, c("country_from", "capital_from", "lat_from", "lon_from",
                         "country_to", "capital_to", "lat_to", "lon_to"))


# widget_arcs <- sf::st_as_sf( widget_arcs, coords = c("lon_to", "lat_to"))

geo <- geojsonsf::df_geojson( widget_arcs[, c("country_from", "lon_to", "lat_to")], lat = "lat_to", lon = "lon_to")
sf <- geojsonsf::geojson_sf( geo )

widget_arcs <- sf::st_as_sf( widget_arcs, coords = c("lon_from", "lat_from"))
widget_arcs <- cbind( widget_arcs, sf )

names(widget_arcs)[names(widget_arcs) %in% c("geometry","geometry.1")] <- c("origin", "destination")
sf::st_geometry(widget_arcs) <- "origin"
widget_arcs$country_from.1 <- NULL
widget_arcs$lon_to <- NULL
widget_arcs$lat_to <- NULL

usethis::use_data( widget_arcs, overwrite = T )
