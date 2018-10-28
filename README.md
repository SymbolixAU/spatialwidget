
<!-- README.md is generated from README.Rmd. Please edit that file -->

# spatialwidget

works in two stages

  - sorts out the legend
  - converts remaining data and parameters into GeoJSON

# SF objects

An `sf` object is retured as a JSON array of GeoJSON features, one array
element for each row of the `sf`

## How do I use it in my package?

You need to implement a `.cpp` file and a `.R` file.

The `.cpp` file must include

  - `std::map< std::string, std::string > colours` - a mapping between
    colours and opacities
  - `Rcpp::StringVector legend` - vector containing the possible legends
  - `Rcpp::List defaults` - A list of vectors, with at least one vector
    per colour option

(the names of these objects, `columns`, `colours`, etc are optional).

You then call `spatialwidget::api::create_geojson()` with these
arguments.

**line\_example.cpp**

``` cpp
#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"

// map between colour and opacity values
std::map< std::string, std::string > line_colours = {
  { "stroke_colour", "stroke_opacity" }
};

// vector of possible legend components
Rcpp::StringVector line_legend = Rcpp::StringVector::create(
  "stroke_colour"
);

Rcpp::NumericVector default_stroke_colour( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::NumericVector default_stroke_width( int n ) {
  Rcpp::NumericVector nv( n, 1.0 );
  return nv;
}

Rcpp::List line_defaults( int n ) {
  return Rcpp::List::create(
   Rcpp::_["stroke_colour"] = default_stroke_colour( n ),
   Rcpp::_["stroke_width"] = default_stroke_width( n )
  );
}

// [[Rcpp::export]]
Rcpp::List line_example_geojson( Rcpp::DataFrame data, Rcpp::List params ) {

  int data_rows = data.nrows();
  Rcpp::List defaults = line_defaults( data_rows );

  return spatialwidget::api::create_geojson(
    data, params, defaults,
    line_colours, line_legend,
    data_rows
  );
}
```

In R you create a list of paramters, for example specifying which
columns of your data will be used the colours.

If a parameter specifies a column of the data object, that column will
be used and returned. If the parameter is a single value

**line\_example.R**

``` r

library(sf)      ## for printing sf options
library(mapdeck) ## for roads data
sf_line <- mapdeck::roads

l <- list()
l[["stroke_colour"]] <- "RIGHT_LOC"
l[["geometry"]] <- "geometry"       ## the geometry column

js_data <- spatialwidget:::line_example_geojson( sf_line, l )
str(js_data)

# List of 2
# $ data  : 'geojson' chr "[{\"type\":\"Feature\",\"properties\":{\"stroke_colour\":\"#46317EFF\"},\"geometry\":{\"type\":\"LineString\",\"| __truncated__
# $ legend: 'json' chr "{\"stroke_colour\":[false]}"
```
