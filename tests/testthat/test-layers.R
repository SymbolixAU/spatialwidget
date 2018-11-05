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
