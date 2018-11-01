#' Spatial line
#'
#' @param sf \code{sf} object
#' @param stroke_colour string specifying column of \code{sf} to use for the stroke colour,
#' or a single value to apply to all rows of data
#' @param stroke_opacity string specifying column of \code{sf} to use for the stroke opacity,
#' or a single value to apply to all rows of data
#' @param stroke_width string specifying column of \code{sf} to use for the stroke width,
#' or a single value to apply to all rows of data
#' @param legend logical indicating if legend data will be returned
#'
#' @export
spatial_line <- function( sf, stroke_colour, stroke_opacity, stroke_width, legend = TRUE) {
  l <- list()
  l[["stroke_colour"]] <- stroke_colour
  l[["stroke_opacity"]] <- stroke_opacity
  l[["stroke_width"]] <- stroke_width
  l[["legend"]] <- legend
  l[["geometry"]] <- attr( sf, "sf_column" )

  data_types <- vapply( sf_line, function(x) class(x)[[1]], "")

  js_data <- spatialwidget:::line_example_geojson( sf, data_types, l, c("geometry") )
  return( js_data )
}
