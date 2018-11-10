
roads <- mapdeck::roads
usethis::use_data( roads )

library(geojsonsf)
sf <- geojson_sf("https://symbolixau.github.io/data/geojson/SA2_2016_VIC.json")
sf <- sf::st_cast( sf, "POLYGON" )
melbourne <- sf[, c("SA3_NAME16", "GCC_NAME16", "GCC_CODE16", "SA2_MAIN16", "AREASQKM16", "SA2_NAME16", "SA4_CODE16", "SA4_NAME16")]

usethis::use_data(melbourne)


library(sf)
capitals <- mapdeck::capitals
capitals <- sf::st_as_sf( capitals, coords = c("lon", "lat"))
usethis::use_data( capitals, overwrite = T)