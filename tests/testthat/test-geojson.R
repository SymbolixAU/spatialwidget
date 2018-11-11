context("geojson")

test_that("to_geojson always returns a Feature, even if ther arent' any properties", {

  sf <- structure(list(geometry = structure(list(structure(c(0, 0), class = c("XY",
  "POINT", "sfg"))), class = c("sfc_POINT", "sfc"), precision = 0, bbox = structure(c(xmin = 0,
  ymin = 0, xmax = 0, ymax = 0), class = "bbox"), crs = structure(list(
  epsg = NA_integer_, proj4string = NA_character_), class = "crs"), n_empty = 0L)), row.names = 1L, class = c("sf",
  "data.frame"), sf_column = "geometry", agr = structure(integer(0), class = "factor", .Label = c("constant",
  "aggregate", "identity"), .Names = character(0)))

  geo <- spatialwidget:::rcpp_geojson_sf(sf, "geometry")
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(geometry = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

})

test_that("geometry field changes with user input", {

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(mygeometryproperty = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"mygeometryproperty\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

})


test_that("MULTI objects are down-casted", {

  # pt1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_point(c(0,0))))
  # mp1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:6, ncol = 2))))
  # mp2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:6, ncol = 3))))
  # mp3 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:8, ncol = 4))))
  # pt2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_point(c(1,1,3,4))))
  # ls1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_linestring(x = matrix(1:6, ncol = 2))))
  # ls2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_linestring(x = matrix(1:6, ncol = 3))))
  # mls1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multilinestring(x = list(matrix(1:6, ncol = 2), matrix(6:1, ncol = 2), matrix(1:6, ncol = 2)))))
  #
  # js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
  # mp <- geojsonsf::geojson_sf( js )
  # sf::st_crs( mp ) <- sf::st_crs( mls1 )
  #
  # geojsonsf::sf_geojson(pt1)
  # sf <- rbind(pt1, mp1, mp2, mp3, pt2, ls1, ls2, mls1, mp)
  # sf$id <- 1:nrow(sf)
  #
  # geojsonsf::sf_geojson( sf[8, ] , atomise = T)


  ## TODO( redo these tests, because spatialwidget down't return valid GeoJSON, so the geojsonsf::geojson_sf() errors)
  # js <- '{"type":"Feature","properties":{"id":2},"geometry":{"type":"MultiPoint","coordinates":[[1,4],[2,5],[3,6]]}}'
  # sf <- geojsonsf::geojson_sf( js )
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  #
  # expect_true(jsonify:::validate_json(geo_down))
  # sf_down <- geojsonsf::geojson_sf( geo_down )
  # expect_true(nrow(sf_down) == 3)
  #
  # js <- '{"type":"Feature","properties":{"id":3},"geometry":{"type":"MultiPoint","coordinates":[[1,3,5],[2,4,6]]}}'
  # sf <- geojsonsf::geojson_sf( js )
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  #
  # expect_true(jsonify:::validate_json(geo_down))
  # sf_down <- geojsonsf::geojson_sf( geo_down )
  # expect_true(nrow(sf_down) == 2)
  #
  #
  # js <- '{"type":"Feature","properties":{"id":4},"geometry":{"type":"MultiPoint","coordinates":[[1,3,5,7],[2,4,6,8]]}}'
  # sf <- geojsonsf::geojson_sf( js )
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  #
  # expect_true(jsonify:::validate_json(geo_down))
  # sf_down <- geojsonsf::geojson_sf( geo_down )
  # expect_true(nrow(sf_down) == 2)
  #
  # js <- '{"type":"Feature","properties":{"id":8},"geometry":{"type":"MultiLineString","coordinates":[[[1.0,4.0],[2.0,5.0],[3.0,6.0]],[[6.0,3.0],[5.0,2.0],[4.0,1.0]],[[1.0,4.0],[2.0,5.0],[3.0,6.0]]]}}'
  # sf <- geojsonsf::geojson_sf( js )
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  #
  # expect_true(jsonify:::validate_json(geo_down))
  # sf_down <- geojsonsf::geojson_sf( geo_down )
  # expect_true(nrow(sf_down) == 3)
  #
  #
  # js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
  # sf <- geojsonsf::geojson_sf( js )
  #
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  # expect_true(jsonify:::validate_json(geo_down))
  # sf_down <- geojsonsf::geojson_sf( geo_down )
  # expect_true(nrow(sf_down) == 2)
  #
  # ## a combination of some of the above
  # js <- '{"type":"FeatureCollection","features":[{"type":"Feature","properties":{"id":2},"geometry":{"type":"MultiPoint","coordinates":[[1,4],[2,5],[3,6]]}},{"type":"Feature","properties":{"id":8},"geometry":{"type":"MultiLineString","coordinates":[[[1.0,4.0],[2.0,5.0],[3.0,6.0]],[[6.0,3.0],[5.0,2.0],[4.0,1.0]],[[1.0,4.0],[2.0,5.0],[3.0,6.0]]]}},{"type":"Feature","properties":{"id":9},"geometry":{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}}]}'
  # sf <- geojsonsf::geojson_sf( js )
  # geo_down <- spatialwidget:::rcpp_sf_to_geojson_downcast( sf, "geometry" )
  # sf <- geojsonsf::geojson_sf( geo_down )
  #
  # expect_true( nrow(sf) == 8 )
  # expect_true( length(unique(sf$id)) == 3 )
})
