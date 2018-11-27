context("layers")

test_that("that weired legend errer I was getting has gone", {

  l1 <- widget_point(capitals[1:2, ], fill_colour = "country", legend = T)
  l1$legend

  l2 <- widget_point(capitals[1:2, ], legend = F)
  l2$legend

  l3 <- widget_point(capitals[1:2, ], fill_colour = "country", legend = T)
  l3$legend

  expect_true(l1$legend == l3$legend)

})

test_that("legend is not jsonified", {

  l <- widget_point(capitals[1:10, ], fill_colour = "country", legend = T, json_legend = FALSE)
  expect_true(inherits(l, "list"))
  expect_true(length( l$legend$fill_colour$colour ) == 10 )

  l <- widget_line(roads[1:10, ], stroke_colour = "FQID", legend = T, json_legend = FALSE)
  expect_true(inherits(l, "list"))
  expect_true(length( l$legend$stroke_colour$colour ) == 5 )

  l <- widget_polygon(melbourne[1:10, ], fill_colour = "AREASQKM", legend = T, json_legend = FALSE)
  expect_true(inherits(l, "list"))
  expect_true(length( l$legend$fill_colour$colour ) == 5 )

})
