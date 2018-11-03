context("utils")

test_that("fill_vector returns new list element", {
  lst <- list()
  param <- "my_param"
  val <- 1
  n <- 20
  new_lst <- spatialwidget:::rcpp_fill_single_vector( lst, param, val, n)
  expect_true( "my_param" %in% names(new_lst))
  expect_true( all( new_lst[["my_param"]] == rep(1, n) ) )
})


test_that("where_is returns correct index", {
  expect_equal(spatialwidget:::rcpp_where_is("a", letters), 0)
  expect_equal(spatialwidget:::rcpp_where_is("b", letters), 1)
  expect_equal(spatialwidget:::rcpp_where_is("z", letters), 25)
})

test_that("data_column_index returns correct column index", {
  # data_names <- c("name1","name2","name3")
  # expect_equal(spatialwidget:::rcpp_data_column_index("name2", data_names), 1)
  # expect_equal(spatialwidget:::rcpp_data_column_index("new_name", data_names), -1)
})


# library(microbenchmark)
# txt <- function(n = 5000) {
#   a <- do.call(paste0, replicate(5, sample(LETTERS, n, TRUE), FALSE))
#   paste0(a, sprintf("%04d", sample(9999, n, TRUE)), sample(LETTERS, n, TRUE))
# }
# sv <- txt(1e6)
# this <- sv[1e6]
#
# microbenchmark(
#   fciiv = {
#     spatialwidget:::rcpp_where_is( this, sv )
#   },
#   base = {
#     which(this == sv)
#   },
#   times = 5
# )
#
# # Unit: milliseconds
# #  expr      min       lq     mean   median       uq      max neval
# # fciiv 16.85030 20.95012 23.25741 21.88659 23.57455 33.02549     5
# #  base 30.42226 30.84569 35.30781 31.86136 32.41005 50.99966     5


# library(microbenchmark)
#
# txt <- function(n = 5000) {
#   a <- do.call(paste0, replicate(5, sample(LETTERS, n, TRUE), FALSE))
#   paste0(a, sprintf("%04d", sample(9999, n, TRUE)), sample(LETTERS, n, TRUE))
# }
# sv <- txt(1e6)
# this <- sv[1e6]
# microbenchmark(
#   fciiv = {
#     spatialwidget:::rcpp_data_column_index(this, sv)
#   },
#   dci = {
#     spatialwidget:::rcpp_find_character_index_in_vector(sv, this)
#   },
#   times = 5
# )
#
# # Unit: milliseconds
# # expr       min        lq      mean    median        uq       max neval
# # fciiv 15.080700 15.126027 15.424576 15.347360 15.462630 16.106163     5
# # dci  7.737278  7.899864  8.134883  8.228087  8.337941  8.471244     5


# library(microbenchmark)
#
# lst <- list()
# param <- "yo"
# val <- 1L
# n <- 1e8
# microbenchmark(
#   base = {
#     lst[[param]] <- rep(val, n)
#   },
#   sw = {
#     lst <- spatialwidget:::rcpp_fill_single_vector( lst, param, val, n)
#   },
#   times = 5
# )
# # Unit: milliseconds
# # expr      min       lq     mean   median       uq      max neval
# # base 316.4571 342.9706 344.4254 347.5521 349.1109 366.0364     5
# #   sw 214.9857 233.6731 235.6869 238.2186 242.6415 248.9155     5
