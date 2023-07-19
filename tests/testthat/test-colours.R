context("colours")

test_that("is_hex works - issue 359", {

  colours <- c("#","0","#0","#00","#000","#0000", "#00000", "#000000", "#0000000", "#00000000", "#000000000")
  expected <- c(FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE)

  result <- spatialwidget:::rcpp_is_hex(colours)
  expect_equal(expected, result)

})

test_that("colours returned as hex or rgb",{

  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  total_colours <- nrow( df )
  repeats <- 1L
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "fill_colour"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "hex"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    repeats,
    total_colours,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values(1:5, alpha = 1:5)
  )


  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  total_colours <- nrow( df )
  repeats <- 1L
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "not_a_column_will_use_default"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "hex"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    repeats,
    total_colours,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values(1:5)
  )


  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  total_colours <- nrow( df )
  repeats <- 1L
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "fill_colour"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "rgb"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    repeats,
    total_colours,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values_rgb(1:5, alpha = 1:5)
  )

})
