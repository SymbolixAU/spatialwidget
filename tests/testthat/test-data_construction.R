context("data_construction.hpp")

test_that("data is constructed", {

  n <- 5
  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", stroke_width = 3)
  param_names <- lst_params[[ "parameter" ]]
  df <- data.frame(col1 = 1:n)
  data_names <- names( df )
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(stroke_opacity = rep(100, n))

  ## when entering the 'construct_data' function, all the colours and palettes will have been sorted out
  res <- spatialwidget:::rcpp_construct_data( param_names, params, data_names, lst_defaults, data, data_rows )

  expect_true( nrow(res) == 5)
  ## names will be the 'params' + defaults
  expect_true( all(names(res) %in% c("stroke_opacity", "stroke_colour", "stroke_width")  ) )
})

test_that("invalid columns and parameters handled", {

  n <- 5
  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_colour = "col1", fill_colour = "col2", stroke_width = 3)
  param_names <- lst_params[[ "parameter" ]]
  df <- data.frame(col1 = 1:n)
  data_names <- names( df )
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(stroke_opacity = rep(100, n))

  ## when entering the 'construct_data' function, all the colours and palettes will have been sorted out
  expect_error(
    spatialwidget:::rcpp_construct_data( param_names, params, data_names, lst_defaults, data, data_rows ),
    "unknown column"
  )

  ## param_names is created from params, so they shoudl alwys be teh same length
  ## Rcpp::StringVector param_names = params.names();
  n <- 5
  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_width = 3)
  param_names <- lst_params[[ "parameter" ]]
  df <- data.frame(col1 = 1:n)
  data_names <- names( df )
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list()

  expect_error(
    spatialwidget:::rcpp_construct_data( param_names, params, data_names, lst_defaults, data, data_rows ),
    "unsuitable data objects"
  )

})

test_that("parameters not supplied by user are ignored", {

  n <- 5
  lst_params <- list(parameter = c("stroke_colour", "stroke_width"), parameter_type = c(), data_column_index = c() )
  params <- list(stroke_width = 3)
  param_names <- lst_params[[ "parameter" ]]
  df <- data.frame(col1 = 1:n)
  data_names <- names( df )
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(stroke_opacity = rep(100, n))

  res <- spatialwidget:::rcpp_construct_data( param_names, params, data_names, lst_defaults, data, data_rows )
  expect_true(ncol(res) == 2)
  expect_true( all( names(res) %in% c("stroke_opacity", "stroke_width")))

})
