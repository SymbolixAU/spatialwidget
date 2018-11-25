
roads <- mapdeck::roads
usethis::use_data( roads )

# library(geojsonsf)
# sf <- geojson_sf("https://symbolixau.github.io/data/geojson/SA2_2016_VIC.json")
# sf <- sf::st_cast( sf, "POLYGON" )
# melbourne <- sf[, c("SA3_NAME16", "GCC_NAME16", "GCC_CODE16", "SA2_MAIN16", "AREASQKM16", "SA2_NAME16", "SA4_CODE16", "SA4_NAME16")]

melbourne <- geojsonsf::geojson_sf( googleway::geo_melbourne )
melbourne <- melbourne[, c("SA2_NAME", "SA3_NAME", "AREASQKM", "geometry")]
usethis::use_data(melbourne, overwrite = T)


library(sf)
capitals <- mapdeck::capitals
capitals <- sf::st_as_sf( capitals, coords = c("lon", "lat"))
usethis::use_data( capitals, overwrite = T)

from <- mapdeck::capitals[ mapdeck::capitals$country == "Australia", ]
to <- mapdeck::capitals[ mapdeck::capitals$country != "Australia", ]

library(sf)

arcs <- cbind(from, to)
arcs <- setNames(arcs, c("country_from", "capital_from", "lat_from", "lon_from",
                         "country_to", "capital_to", "lat_to", "lon_to"))


arcs <- sf::st_as_sf( arcs, coords = c("lon_from", "lat_from"))
arcs <- sf::st_as_sf( arcs, coords = c("lon_to", "lat_to"))

geo <- geojsonsf::df_geojson( arcs[, c("country_from", "lon_to", "lat_to")], lat = "lat_to", lon = "lon_to")
sf <- geojsonsf::geojson_sf( geo )

arcs <- cbind( arcs, sf )

names(arcs)[names(arcs) %in% c("geometry","geometry.1")] <- c("origin", "destination")
sf::st_geometry(arcs) <- "origin"
arcs$country_from.1 <- NULL
arcs$lon_to <- NULL
arcs$lat_to <- NULL
usethis::use_data( arcs, overwrite = T )
