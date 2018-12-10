
<!-- README.md is generated from README.Rmd. Please edit that file -->

[![Travis build
status](https://travis-ci.org/SymbolixAU/spatialwidget.svg?branch=master)](https://travis-ci.org/SymbolixAU/spatialwidget)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/spatialwidget/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/spatialwidget?branch=master)

# spatialwidget

### What’s a ‘spatialwidget’

Well, what do these packages have in common?

  - leaflet
  - googleway
  - mapdeck
  - mapview
  - tmap

<!-- end list -->

1.  They are all [htmlwidgets](http://www.htmlwidgets.org/)
2.  They all plot interactive maps
3.  They all take data from R and display it on the maps.

And on 22nd August 2017 on the [r-spatial github
page](https://github.com/r-spatial/discuss/issues/15#issue-251762127) it
was requested if there could be a common package which could be shared
by all the interactive web-plotting libraries

> Currently there is code in the leaflet package that extracts data from
> sp and sf objects and converts it into a dataframe that is then passed
> to the Javascript side (by converting it into a JSON). This code is
> fairly generic and not really dependent on anything leaflet specific.
> It makes a lot of sense to take out this code and make it a package of
> its own. That way we can build other web plotting R packages to wrap
> say d3.geo or mapboxGL or cesium and reuse a major chunk of the code
> that takes data from spatial objects and passes it to Javascript.

so **spatialwidget** is my attempt at this library.

### What does it do?

It takes a simple feature object (`sf`), plus some user-supplied
arguments, and converts the data into JSON, ready for plotting/ parsing
in whatever javascript library you chose.

### Can you show me?

Sure. In this example I’m using the `capitals` data, which is an `sf`
object of all the capital cities.

``` r
library(spatialwidget)
library(sf)
#  Linking to GEOS 3.6.1, GDAL 2.1.3, proj.4 4.9.3
sf <- spatialwidget::widget_capitals
sf
#  Simple feature collection with 200 features and 2 fields
#  geometry type:  POINT
#  dimension:      XY
#  bbox:           xmin: -174 ymin: -53 xmax: 179.13 ymax: 64.1
#  epsg (SRID):    NA
#  proj4string:    NA
#  First 10 features:
#                 country          capital               geometry
#  1          Afghanistan            Kabul    POINT (69.11 34.28)
#  2              Albania           Tirane    POINT (19.49 41.18)
#  3              Algeria          Algiers     POINT (3.08 36.42)
#  4       American Samoa        Pago Pago POINT (-170.43 -14.16)
#  5              Andorra Andorra la Vella     POINT (1.32 42.31)
#  6               Angola           Luanda     POINT (13.15 -8.5)
#  7  Antigua and Barbuda      West Indies    POINT (-61.48 17.2)
#  8            Argentina     Buenos Aires      POINT (-60 -36.3)
#  9              Armenia          Yerevan     POINT (44.31 40.1)
#  10               Aruba       Oranjestad   POINT (-70.02 12.32)
```

As each capital is a POINT, you can use `widget_point()` to conver it to
JSON.

``` r
l <- widget_point( data = sf[1:2, ], fill_colour = "country" , legend = F)
```

Each row of `capitals` has been converted into a JSON object. And all
these objects are within an array.

Look, here are the first two rows of `capitals` as JSON

``` r
sf[1:2, ]
#  Simple feature collection with 2 features and 2 fields
#  geometry type:  POINT
#  dimension:      XY
#  bbox:           xmin: 19.49 ymin: 34.28 xmax: 69.11 ymax: 41.18
#  epsg (SRID):    NA
#  proj4string:    NA
#        country capital            geometry
#  1 Afghanistan   Kabul POINT (69.11 34.28)
#  2     Albania  Tirane POINT (19.49 41.18)
jsonlite::prettify( l$data )
#  [
#      {
#          "type": "Feature",
#          "properties": {
#              "fill_colour": "#440154FF"
#          },
#          "geometry": {
#              "geometry": {
#                  "type": "Point",
#                  "coordinates": [
#                      69.11,
#                      34.28
#                  ]
#              }
#          }
#      },
#      {
#          "type": "Feature",
#          "properties": {
#              "fill_colour": "#FDE725FF"
#          },
#          "geometry": {
#              "geometry": {
#                  "type": "Point",
#                  "coordinates": [
#                      19.49,
#                      41.18
#                  ]
#              }
#          }
#      }
#  ]
#  
```

You can see that the coordinates are inside a `geometry` object, and the
user-defined `fill_colour` is within the `properties` object.

### That looks a lot like GeoJSON

Well spotted. But it’s not quite GeoJSON for a very good reason.

Some plotting libraries can use more than one geometry, such as
[mapdeck::add\_arc()](https://github.com/SymbolixAU/mapdeck#basic-use),
which uses an origin and destination. So spatialwidget needs to handle
multiple geometries.

Typical GeoJSON will take the
form

``` js
[{"type":"Feature", "properties":{"stroke_colour":"#440154FF"},"geometry":{"type":"Point","coordinates":[0,0]}}]
```

Whereas I’ve nested the geometries one-level deeper, so the
pseudo-GeoJSON i’m using takes the
form

``` js
[{"type":"Feature", "properties":{"stroke_colour":"#440154FF"},"geometry":{"myGeometry":{"type":"Point","coordinates":[0,0]}}}]
```

Where the `myGeometry` object is defined on a per-application bases. You
are free to call this whatever you want inside your
library.

### That sort of makes sense, but can you show me an example with multiple geometries?

Yep.

The `arcs` data is an `sf` object with two POINT geometry columns. So
say we want to generate an arc-map showing an arc between Sydney and all
the other capitals cities. Just call `widget_od`, supplying the origin
and destination columns.

``` r

l <- widget_od( widget_arcs[1:2, ], origin = "origin", destination = "destination")

jsonlite::prettify( l$data )
#  [
#      {
#          "type": "Feature",
#          "properties": {
#              "fill_colour": "#440154FF"
#          },
#          "geometry": {
#              "origin": {
#                  "type": "Point",
#                  "coordinates": [
#                      149.08,
#                      -35.15
#                  ]
#              },
#              "destination": {
#                  "type": "Point",
#                  "coordinates": [
#                      69.11,
#                      34.28
#                  ]
#              }
#          }
#      },
#      {
#          "type": "Feature",
#          "properties": {
#              "fill_colour": "#440154FF"
#          },
#          "geometry": {
#              "origin": {
#                  "type": "Point",
#                  "coordinates": [
#                      149.08,
#                      -35.15
#                  ]
#              },
#              "destination": {
#                  "type": "Point",
#                  "coordinates": [
#                      19.49,
#                      41.18
#                  ]
#              }
#          }
#      }
#  ]
#  
```

Notice now the `geometry` object has within it an `origin` and a
`destination`. This is why I’ve nested the geometries one level deeper
within the GeoJSON

### How do I use it in my package?

You can use these R functions, but they have limited scope. This package
has been designed so you use the C++ functions directly. I’ve gone into
more detail in the
[vignette](https://symbolixau.github.io/spatialwidget/), so it’s
probably best you read that to understand how to call the C++ functions.
