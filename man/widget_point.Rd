% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/spatial_widget.R
\name{widget_point}
\alias{widget_point}
\title{Widget Point}
\usage{
widget_point(data, fill_colour, fill_opacity, lon = NULL, lat = NULL,
  legend = TRUE, json_legend = TRUE)
}
\arguments{
\item{fill_opacity}{}

\item{lon}{string specifying the column of \code{data} containing the longitude.
Ignored if using an \code{sf} object}

\item{lat}{string specifying the column of \code{data} containing the latitude.
Ignored if using an \code{sf} object}

\item{legend}{logical indicating if legend data will be returned}

\item{json_legend}{logical indicating if the legend will be returned as json}
}
\description{
Converts an `sf` object with POINT geometriers into JSON for plotting in an htmlwidget
}
\examples{

l <- widget_point( data = capitals, legend = FALSE )

}