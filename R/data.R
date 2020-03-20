#' Capital cities for each country
#'
#' A simple feature \code{sf} object containing the coordinates of 200 capitical cities in the world
#'
#' @format A sf object with 200 observations and 4 variables
#' \describe{
#'   \item{country}{country name}
#'   \item{capital}{capital name}
#'   \item{geometry}{sfc geometry column}
#' }
"widget_capitals"


#' Origin Destination points between Sydney, Australia and other capitals cities
#'
#' A simple feature \code{sf} object with two \code{sfc} columns, "origin" and "destination"
#'
#' @format A sf object with 199 observations and 6 variables
#' \describe{
#'   \item{country_from}{origin country}
#'   \item{capital_from}{origin capital}
#'   \item{country_to}{destination country}
#'   \item{capital_to}{destination capital}
#'   \item{origin}{sfc geometry column}
#'   \item{destination}{sfc geometry column}
#' }
"widget_arcs"


#' Roads in central Melbourne
#'
#' A simple feature \code{sf} object of roads in central Melbourne
#'
#' @details
#' Obtained from \url{http://www.data.gov.au} and distributed under the Creative Commons 4 License
#' \url{https://creativecommons.org/licenses/by/4.0/}
#'
#' @format An sf and data frame object with 18286 observations and 16 variables
#'
"widget_roads"

#' Melbourne
#'
#' A simple feature \code{sf} object of Polygons for Melbourne and the surrounding area
#'
#' This data set is a subset of the Statistical Area Level 2 (SA2) ASGS
#' Edition 2016 data released by the Australian Bureau of Statistics
#' \url{ http://www.abs.gov.au }
#'
#' The data is realsed under a Creative Commons Attribution 2.5 Australia licence
#' \url{https://creativecommons.org/licenses/by/2.5/au/}
#'
#' The data has been down-cast from MULTIPOLYGONS to POLYGONS.
#'
#' @format A data frame with 397 observations and 7 variables
#' \describe{
#'   \item{SA2_NAME}{statistical area 2 name of the polygon}
#'   \item{SA3_NAME}{statistical area 3 name of the polygon}
#'   \item{AREASQKM}{area of the SA2 polygon}
#'   \item{geometry}{sfc geometry column}
#' }
"widget_melbourne"
