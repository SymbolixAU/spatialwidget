
<!-- README.md is generated from README.Rmd. Please edit that file -->

[![Travis build
status](https://travis-ci.org/SymbolixAU/spatialwidget.svg?branch=master)](https://travis-ci.org/SymbolixAU/spatialwidget)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/spatialwidget/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/spatialwidget?branch=master)

# spatialwidget

works in two stages

  - sorts out the legend
  - converts remaining data and parameters into pseudo-GeoJSON

# SF objects

An `sf` object is retured as a JSON array of pseudo-GeoJSON features,
one array element for each row of the `sf`

## How do I use it in my package?

You need to implement a `.cpp` file and a `.R` file.

The `.cpp` file must include

  - `std::unordered_map< std::string, std::string > colours` - a mapping
    between colours and opacities
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
std::unordered_map< std::string, std::string > line_colours = {
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
be used and returned. If the parameter is a single value, that value
will be used for every row.

You also need to specify the ‘geometry’ columns of the `sf` object you
want to include.

**line\_example.R**

``` r

library(sf)
#  Linking to GEOS 3.6.1, GDAL 2.1.3, proj.4 4.9.3
library(mapdeck) ## for roads data

sf_line <- mapdeck::roads

l <- list()
l[["stroke_colour"]] <- "RIGHT_LOC"


## the list of parameters should include the geometry columns,
l[["myPathGeometry"]] <- "geometry"       ## a geometry column

## and you need topass in those parameter names which inlcude the geometry columns

js_data <- spatialwidget:::line_example_geojson( sf_line, l, c("myPathGeometry") )
str(js_data)
#  List of 2
#   $ data  : 'json' chr "[{\"type\":\"Feature\",\"properties\":{\"stroke_colour\":\"#46317EFF\",\"stroke_width\":1.0},\"geometry\":{\"my"| __truncated__
#   $ legend: 'json' chr "{\"stroke_colour\":[false]}"
```

### What do you mean by ‘pseudo-GeoJSON’?

Because you can supply multiple geometry columns, all of them need to be
converted into GeoJSON. But, each of these GeoJSONs will have the same
properties (because they come from the same row of an `sf` object). So
rather than duplicating the properties for each geometry, I’ve decided
to include each geometry inside the `geometry : {}` object.

Therefore this invalidates the GeoJSON standard, so it’s technically not
GeoJSON.

``` r

js_data <- spatialwidget:::line_example_geojson( sf_line[1, ], l, c("myPathGeometry") )
cat( js_data$data )
#  [{"type":"Feature","properties":{"stroke_colour":"#440154FF","stroke_width":1.0},"geometry":{"myPathGeometry":{"type":"LineString","coordinates":[[145.014291,-37.830458],[145.014345,-37.830574],[145.01449,-37.830703],[145.01599,-37.831484],[145.016479,-37.831699],[145.016813,-37.83175],[145.01712,-37.831742],[145.0175,-37.831667],[145.017843,-37.831559],[145.018349,-37.83138],[145.018603,-37.83133],[145.018901,-37.831301],[145.019136,-37.831301],[145.01943,-37.831333],[145.019733,-37.831377],[145.020195,-37.831462],[145.020546,-37.831544],[145.020641,-37.83159],[145.020748,-37.83159],[145.020993,-37.831664]]}}}]
```

There is a working example in [mapdeck
here](https://github.com/SymbolixAU/mapdeck/blob/geojson/src/path.cpp)

``` cpp
#include <Rcpp.h>

#include "mapdeck_defaults.hpp"
#include "layers/path.hpp"
#include "spatialwidget/spatialwidget.hpp"

Rcpp::List path_defaults(int n) {
    return Rcpp::List::create(
        _["polyline"] = mapdeck::defaults::default_polyline(n),
        _["stroke_colour"] = mapdeck::defaults::default_stroke_colour(n),
        _["stroke_width"] = mapdeck::defaults::default_stroke_width(n)
    );
}

// [[Rcpp::export]]
Rcpp::List rcpp_path_geojson( Rcpp::DataFrame data, Rcpp::List params ) {

    int data_rows = data.nrows();
    Rcpp::List lst_defaults = path_defaults( data_rows );  // initialise with defaults
    std::unordered_map< std::string, std::string > path_colours = mapdeck::path::path_colours;
    Rcpp::StringVector path_legend = mapdeck::path::path_legend;

    return spatialwidget::api::create_geojson(
        data, params, lst_defaults,
        path_colours, path_legend,
        data_rows
    );
}
```
