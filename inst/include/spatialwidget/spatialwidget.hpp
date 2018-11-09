#ifndef R_SPATIALWIDGET_H
#define R_SPATIALWIDGET_H

#include "Rcpp.h"

// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/colours/colours_hex.hpp"

// [[Rcpp::depends(jsonify)]]
#include "jsonify/to_json.hpp"

#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/data_construction/data_construction.hpp"
//#include "spatialwidget/geojson/geometrycollection.hpp"
#include "spatialwidget/geojson/geojson.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/parameters/parameters.hpp"
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace api {

  /*
   * expects `data` to be an sf object
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& geometry_columns,
      bool jsonify_legend
    ) {

    Rcpp::List res(2);

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      data_types,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::vectors::to_json( legend );
      Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
      res[1] = sv_leg;
    } else {
      res[1] = legend;
    }

    res.names() = Rcpp::CharacterVector::create("data", "legend");
    return res;
  }

  /*
   * expects `data` to be data.frame withn lon & lat columns
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::List& geometry_columns,
      bool jsonify_legend
  ) {

    Rcpp::List res(2);
    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      data_types,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows
    );


    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::vectors::to_json( legend );
      Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
      res[1] = sv_leg;
    } else {
      res[1] = legend;
    }

    res.names() = Rcpp::CharacterVector::create("data", "legend");
    return res;
  }


/*
 * expects `data` to be data.frame withn lon & lat & elev columns
 */
inline Rcpp::List create_geojson(
    Rcpp::DataFrame& data,
    Rcpp::List& data_types,
    Rcpp::List& params,
    Rcpp::List& lst_defaults,
    std::unordered_map< std::string, std::string >& layer_colours,
    Rcpp::StringVector& layer_legend,
    int& data_rows,
    Rcpp::List& geometry_columns,
    bool jsonify_legend,
    bool elevation
) {

  Rcpp::List res(2);
  Rcpp::StringVector data_names = data.names();

  Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
    data,
    data_types,
    params,
    lst_defaults,
    layer_colours,
    layer_legend,
    data_rows
  );

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
  Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_z_atomise( df, geometry_columns );


  res[0] = js_data;

  SEXP legend = lst[ "legend" ];
  if ( jsonify_legend ) {
    legend = jsonify::vectors::to_json( legend );
    Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
    res[1] = sv_leg;
  } else {
    res[1] = legend;
  }

  res.names() = Rcpp::CharacterVector::create("data", "legend");
  return res;
}



  /*
   * expects `data` to be data.frame withn a polyline
   */
  inline Rcpp::List create_polyline(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector geometry_columns,
      bool jsonify_legend
  ) {

    Rcpp::List res(2);

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      data_types,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = jsonify::dataframe::to_json( df );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::vectors::to_json( legend );
      Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
      res[1] = sv_leg;
    } else {
      res[1] = legend;
    }

    res.names() = Rcpp::CharacterVector::create("data", "legend");
    return res;
  }

} // namespace api
} // namespace spatialwidget

#endif
