#' Widget Line
#'
#' Converts an `sf` object with LINESTRING geometriers into JSON for plotting in an htmlwidget
#'
#' @param data \code{sf} object
#' @param stroke_colour string specifying column of \code{sf} to use for the stroke colour,
#' or a single value to apply to all rows of data
#' @param stroke_opacity string specifying column of \code{sf} to use for the stroke opacity,
#' or a single value to apply to all rows of data
#' @param stroke_width string specifying column of \code{sf} to use for the stroke width,
#' or a single value to apply to all rows of data
#' @param legend logical indicating if legend data will be returned
#' @param json_legend logical indicating if the legend will be returned as json
#'
#' @examples
#'
#' ## use default stroke options
#' l <- widget_line( widget_roads, legend = TRUE )
#'
#' @export
widget_line <- function( data,
                         stroke_colour = NULL,
                         stroke_opacity = NULL,
                         stroke_width = NULL,
                         legend = TRUE,
                         json_legend = TRUE) {

  l <- as.list( match.call( expand.dots = F) )
  l[[1]] <- NULL
  l[["data"]] <- NULL
  l[["json_legend"]] <- NULL
  l[["stroke_colour"]] <- force( stroke_colour )
  l[["stroke_opacity"]] <- force( stroke_opacity )
  l[["stroke_width"]] <- force( stroke_width )

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "LINESTRING")

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }
  l[["data_type"]] <- NULL

  js_data <- rcpp_widget_line( data, l, c("geometry"), json_legend  )
  return( js_data )
}


#' Widget Polygon
#'
#' Converts an `sf` object with POLYGON geometriers into JSON for plotting in an htmlwidget
#'
#' @inheritParams widget_line
#' @param fill_colour string specifying column of \code{sf} to use for the fill colour,
#' or a single value to apply to all rows of data
#' @param fill_opacity string specifying column of \code{sf} to use for the fill opacity,
#' or a single value to apply to all rows of data
#'
#' @examples
#'
#' l <- widget_polygon( widget_melbourne, legend = FALSE )
#' l <- widget_polygon( widget_melbourne, fill_colour = "AREASQKM16", legend = TRUE )
#'
#' @export
widget_polygon <- function( data,
                            stroke_colour = NULL,
                            stroke_opacity = NULL,
                            stroke_width = NULL,
                            fill_colour = NULL,
                            fill_opacity = NULL,
                            legend = TRUE,
                            json_legend = TRUE ) {

  l <- as.list( match.call( expand.dots = F ) )
  l[[1]] <- NULL
  l[["data"]] <- NULL
  l[["json_legend"]] <- NULL
  l[["stroke_colour"]] <- force( stroke_colour )
  l[["stroke_opacity"]] <- force( stroke_opacity )
  l[["stroke_width"]] <- force( stroke_width )
  l[["fill_colour"]] <- force( fill_colour )
  l[["fill_opacity"]] <- force( fill_opacity )

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "POLYGON" )

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }
  l[["data_type"]] <- NULL

  js_data <- rcpp_widget_polygon( data, l, c("geometry"), json_legend )
  return( js_data )
}


#' Widget Point
#'
#' Converts an `sf` object with POINT geometriers into JSON for plotting in an htmlwidget
#'
#' @inheritParams widget_polygon
#' @param lon string specifying the column of \code{data} containing the longitude.
#' Ignored if using an \code{sf} object
#' @param lat string specifying the column of \code{data} containing the latitude.
#' Ignored if using an \code{sf} object
#'
#' @examples
#'
#' l <- widget_point( data = widget_capitals, legend = FALSE )
#'
#' @export
widget_point <- function( data,
                          fill_colour = NULL,
                          fill_opacity = NULL,
                          lon = NULL,
                          lat = NULL,
                          legend = TRUE,
                          json_legend = TRUE ) {

  l <- as.list( match.call( expand.dots = F ) )
  l[[1]] <- NULL
  l[["data"]] <- NULL
  l[["json_legend"]] <- NULL
  l[["lon"]] <- force( lon )
  l[["lat"]] <- force( lat )
  l[["fill_colour"]] <- force( fill_colour )
  l[["fill_opacity"]] <- force( fill_opacity )

  l <- resolve_legend( l, legend )
  l <- resolve_data( data, l, "POINT" )

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }

  tp <- l[["data_type"]]
  l[["data_type"]] <- NULL

  if( tp == "sf" ) {
    js_data <- rcpp_widget_point( data, l, c("geometry"), json_legend )
  } else if (tp == "df" ) {
    if( is.null( lon ) || is.null( lat ) ) {
      stop("lon and lat are requried for data.frames")
    }
    js_data <- rcpp_widget_point_df(
      data, l, list(myGeometry = c("lon","lat") ), json_legend
      )
  }
  return( js_data )
}


#' Widget OD
#'
#' Converts an `sf` object with two POINT geometriers into JSON for plotting in an htmlwidget
#'
#' @inheritParams widget_polygon
#' @param origin string specifying the column of \code{data} containing the origin geometry
#' @param destination string specifying the column of \code{data} containing the destination geometry
#'
#' @examples
#'
#' l <- widget_od( data = widget_arcs, origin = "origin", destination = "destination", legend = FALSE )
#'
#' @export
widget_od <- function( data,
                       origin,
                       destination,
                       fill_colour = NULL,
                       fill_opacity = NULL,
                       legend = TRUE,
                       json_legend = TRUE ) {

  l <- as.list( match.call( expand.dots = F ) )
  l[[1]] <- NULL
  l[["data"]] <- NULL
  l[["json_legend"]] <- NULL

  l <- resolve_legend( l, legend )
  l <- resolve_od_data( data, l, "POINT" )

  if( !is.null( l[["data"]] ) ) {
    data <- l[["data"]]
    l[["data"]] <- NULL
  }

  tp <- l[["data_type"]]
  l[["data_type"]] <- NULL

  js_data <- rcpp_widget_point( data, l, c("origin","destination"), json_legend )

  return( js_data )
}


resolve_legend <- function( l, legend ) {
  l[['legend']] <- legend
  return( l )
}

## TODO( allow MULTI* objects)
sfrow <- function( data , sfc_type ) {
  geom_column <- attr(data, "sf_column")
  return(
    which(vapply(data[[geom_column]], function(x) attr(x, "class")[[2]], "") %in% c(sfc_type, paste0("MULTI", sfc_type) ) )
  )
}

resolve_od_data <- function( data, l, origin, destination ) UseMethod("resolve_od_data")

#' @export
resolve_od_data.sf <- function( data, l, origin, destination ) {
  if ( is.null( l[["origin"]] ) || is.null( l[["destination"]] ) ) {
    stop("origin and destination columns required")
  }
  l[["data_type"]] <- "sf"
  return( l )
}

#' @export
resolve_od_data.default <- function( data, l, origin, destination ) stop("only sf objects are supported for OD")

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
  l[["geometry"]] <- c( l[["lon"]], l[["lat"]] )
  l[["data"]] <- data
  l[["data_type"]] <- "df"
  return( l )
}
