#' Capital cities for each country
#'
#' A data set containing the coordinates of 200 capitical cities in the world
#'
#' @format A data frame with 200 observations and 4 variables
#' \describe{
#'   \item{country}{country name}
#'   \item{capital}{capital name}
#'   \item{lat}{latitude of capital}
#'   \item{lon}{longitude of capital}
#' }
"capitals"

#' Roads in central Melbourne
#'
#' A simple feature \code{sf} object of roads in central Melbourne
#'
#' @details
#' Obtained from \url{www.data.gov.au} and distributed under the Creative Commons 4 License
#' \url{https://creativecommons.org/licenses/by/4.0/}
#'
#' @format An sf and data frame object with 18286 observations and 16 variables
#'
"roads"

#' Melbourne
#'
#' Polygons for Melbourne and the surrounding area
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
#'   \item{SA3_NAME16}{statistical area 3 name of the polygon}
#'   \item{GCC_NAME16}{}
#'   \item{GCC_CODE16}{}
#'   \item{SA2_MAIN16}{statistical area 2 code of the polygon}
#'   \item{AREASQKM16}{area of the SA2 polygon}
#'   \item{SA2_NAME16}{statistical area 2 name of the polygon}
#'   \item{SA4_CODE16}{statistical area 4 code of the polygon}
#'   \item{SA4_NAME16}{statistical area 4 name of the polygon}
#'   \item{geometry}{sfc geometry column}
#' }
"melbourne"
