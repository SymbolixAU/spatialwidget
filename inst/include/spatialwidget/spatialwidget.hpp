#ifndef R_SPATIALWIDGET_H
#define R_SPATIALWIDGET_H

#include "Rcpp.h"

// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/colours/colours_hex.hpp"

// [[Rcpp::depends(jsonify)]]
#include "jsonify/to_json.hpp"

#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/data_construction/data_construction.hpp"
#include "spatialwidget/geojson/geojson.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/parameters/parameters.hpp"
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace api {

  /*
   * sf object with one or many sfc columns
   *
   * expects `data` to be an sf object, where the geometry_columns is a string vector
   * containing the sfc colunm names (of sf) you want to use as the geometry objects
   * inside the GeoJSON
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
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
      data_rows,
      parameter_exclusions
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
   * expects `data` to be an sf object, where the geometry_column is a string
   * of the sfc column names (of sf) you want to use as the geometry object inside the GeoJSON.
   *
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      std::string& geometry_column,              // single geometry column from sf object
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
      data_rows,
      parameter_exclusions
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson( df, geometry_column);

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
   * expects `data` to be an sf object, where the geometry_column is a string
   * of the sfc column name (of sf) you want to use as the geometry object inside the GeoJSON.
   * This function will down-cast MULTI* objects to their single form
   *
   */
  inline Rcpp::List create_geojson_downcast(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      std::string& geometry_column,
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
      data_rows,
      parameter_exclusions
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_downcast_atomise( df, geometry_column );

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
   * expects `data` to be an sf object, where the geometry_column is a string vector
   * of the sfc column name (of sf) you want to use as the geometry object inside the GeoJSON.
   * This function will down-cast MULTI* objects to their single form
   *
   */
  inline Rcpp::List create_geojson_downcast(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::StringVector& geometry_column,
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
      data_rows,
      parameter_exclusions
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_downcast_atomise( df, geometry_column );

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
   * expects `data` to be data.frame withn lon & lat columns. The geometry_columns
   * argument is a named list, list(myGeometry = c("lon","lat")), where 'myGeometry'
   * will be returned inside the 'geometry' object of the GeoJSON
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
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
      data_rows,
      parameter_exclusions
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
   * expects `data` to be data.frame withn lon & lat & elev columns. The 'bool elevation'
   * argument must be set to 'true', and the 'geometry_columns' should contain an 'elevation'
   * value - 'geometry_column <- list( geometry = c("lon","lat","elevation") )'
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
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
      data_rows,
      parameter_exclusions
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
      Rcpp::StringVector& parameter_exclusions,
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
      data_rows,
      parameter_exclusions
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
