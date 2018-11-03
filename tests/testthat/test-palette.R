context("palette.hpp")

test_that("resolve_palette works", {


  lst_params <- list(parameter = c("stroke_colour", "palette", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", palette = "mypalette", stroke_width = 3)
  expect_equal( spatialwidget:::rcpp_resolve_palette( lst_params, params ), "mypalette" )

  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", stroke_width = 3)
  spatialwidget:::rcpp_resolve_palette( lst_params, params )
  expect_equal( spatialwidget:::rcpp_resolve_palette( lst_params, params ), "viridis" )

})
