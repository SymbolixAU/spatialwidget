#' Widget Line
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
#' @examples
#'
#' ## use default stroke options
#' l <- widget_line( roads, legend = F )
#'
#' @export
widget_line <- function( data, stroke_colour, stroke_opacity, stroke_width, legend = TRUE) {
  l <- as.list( match.call( expand.dots = F) )
  l[[1]] <- NULL
  l[["data"]] <- NULL

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "LINESTRING")

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }
  l[["data_type"]] <- NULL

  data_types <- vapply( data, function(x) class(x)[[1]], "")

  js_data <- rcpp_widget_line( data, data_types, l, c("geometry") )
  return( js_data )
}


## TODO( allow MULTI* objects)
sfrow <- function( data , sfc_type ) {
  geom_column <- attr(data, "sf_column")
  return( which(vapply(data[[geom_column]], function(x) attr(x, "class")[[2]], "") == sfc_type ) )
}


#' Widget Polygon
#'
#' @inheritParams widget_line
#' @param fill_colour
#' @param fill_opacity
#'
#' @examples
#'
#' l <- widget_polygon( melbourne, legend = F)
#' l <- widget_polygon( melbourne, fill_colour = "AREASQKM16", legend = F)
#'
#' @export
widget_polygon <- function( data, stroke_colour, stroke_opacity, stroke_width,
                            fill_colour, fill_opacity, legend = TRUE ) {
  l <- as.list( match.call( expand.dots = F ) )
  l[[1]] <- NULL
  l[["data"]] <- NULL

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "POLYGON" )

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }
  l[["data_type"]] <- NULL

  data_types <- vapply( data, function(x) class(x)[[1]], "")

  js_data <- rcpp_widget_polygon( data, data_types, l, c("geometry") )
  return( js_data )
}


#' Widget Point
#'
#' @inheritParams widget_polygon
#' @param lon
#' @param lat
#'
#' @export
widget_point <- function( data, fill_colour, fill_opacity, lon = NULL, lat = NULL, legend = TRUE ) {
  l <- as.list( match.call( expand.dots = F ) )
  l[[1]] <- NULL
  l[["data"]] <- NULL

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "POINT" )

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }

  data_types <- vapply( data, function(x) class(x)[[1]], "")
  tp <- l[["data_type"]]
  l[["data_type"]] <- NULL

  if( tp == "sf" ) {
    js_data <- rcpp_widget_point( data, data_types, l, c("geometry") )
  } else if (tp == "df" ) {
    if( is.null( lon ) || is.null( lat ) ) {
      stop("lon and lat are requried for data.frames")
    }
    js_data <- rcpp_widget_point_df( data, data_types, l, list(myGeometry = c("lon","lat") ) )
  }

  return( js_data )
}


resolve_legend <- function( l, legend ) {
  l[['legend']] <- legend
  return( l )
}

resolve_data <- function( data, l, sf_geom ) UseMethod("resolve_data")

#' @export
resolve_data.sf <- function( data, l, sf_geom ) {
  sfc_col <- attr( data, "sf_column" )
  l[["geometry"]] <- sfc_col

  if ( paste0("sfc_", sfc_col) != toupper(sf_geom) ) {
    l[["data"]] <- data[ sfrow(data, sf_geom) , ]
  }
  l[["data_type"]] <- "sf"
  return( l )
}

#' @export
resolve_data.data.frame <- function( data, l, sf_geom ) {
  if( sf_geom != "POINT") {
    stop("only POINTS are supported for data.frames")
  }
  l[["data"]] <- data
  l[["data_type"]] <- "df"
  return( l )
}
