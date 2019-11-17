#ifndef R_SPATIALWIDGET_H
#define R_SPATIALWIDGET_H

#include "Rcpp.h"

// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/api/api.hpp"

// [[Rcpp::depends(jsonify)]]
#include "jsonify/jsonify.hpp"

#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/data_construction/data_construction.hpp"
#include "spatialwidget/geojson/geojson.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/parameters/parameters.hpp"
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace api {

  //inline int x;

  inline Rcpp::StringVector create_geojson_mesh(
    Rcpp::List& mesh, Rcpp::StringVector vertices
  ) {
    return spatialwidget::geojson::to_geojson_mesh( mesh, vertices );
  }

  /*
   * sf object with one or many sfc columns
   *
   * expects `data` to be an sf object, where the geometry_columns is a string vector
   * containing the sfc colunm names (of sf) you want to use as the geometry objects
   * inside the GeoJSON
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::StringVector& geometry_columns,
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "hex"
    ) {

    // Rcpp::Rcout << "create_geojson1" << std::endl;
    //Rcpp::Rcout << "legend digits: " << legend_digits << std::endl;

    Rcpp::List res(2);

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true,   // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns, digits );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      std::string& geometry_column,              // single geometry column from sf object
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson2" << std::endl;
    // Rcpp::Rcout << "legend digits: " << legend_digits << std::endl;

    Rcpp::List res(2);

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true,  // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson( df, geometry_column, digits );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      std::string& geometry_column,
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson3" << std::endl;
    Rcpp::List res(2);

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true, // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_downcast_atomise( df, geometry_column, digits );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::StringVector& geometry_column,
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson4" << std::endl;
    Rcpp::List res(2);

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true, // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_downcast_atomise( df, geometry_column, digits );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::List& geometry_columns,
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson5" << std::endl;
    // Rcpp::Rcout << "legend digits: " << legend_digits << std::endl;

    Rcpp::List res(2);
    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true, // factors as string
      colour_format
    );

    //return lst;

    //Rcpp::DataFrame df = lst["data"];
    //return x;
    //spatialwidget::construction::construct_df( df, data_rows );
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    //return df;

    //Rcpp::DataFrame df2 = df;

    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns, digits );

    //return js_data;

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

      Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
      // Rcpp::Rcout << "legend: " << sv_leg << std::endl;

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
inline Rcpp::List create_binary(
    Rcpp::DataFrame& data,
    Rcpp::List& params,
    Rcpp::List& lst_defaults,
    std::unordered_map< std::string, std::string >& layer_colours,
    Rcpp::StringVector& layer_legend,
    int& data_rows,
    Rcpp::StringVector& parameter_exclusions,
    Rcpp::List& geometry_columns,
    bool jsonify_legend,
    int digits = -1,
    std::string colour_format = "rgb"  // can't be hex for binary data
) {

  Rcpp::List res(2);
  Rcpp::StringVector data_names = data.names();

  Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
    data,
    params,
    lst_defaults,
    layer_colours,
    layer_legend,
    data_rows,
    parameter_exclusions,
    false, // factors as string
    colour_format
  );

  // lst is an object with a [data] and [legend] component
  // data is a data.frame
  // for primitive layers, each column should be a vector (apart form colours, which will have four elements)
  // we can turn all the columns into numeric vectors(?)
  // (any reason why some won't be numeric?)
  // (year, like tooltips...)
  // (oh, taht's right)
  // - all the mapdeck get* functions shoudl be numeric, thoughh

  return lst["data"];

  // TODO
  // construct vectors of positions, colours, and everything else

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

  return df;

  //
  // Rcpp::List lst_geometries = df["geometry"];
  //
  // Rcpp::NumericVector lons = lst_geometries[0];
  // Rcpp::NumericVector lats = lst_geometries[1];
  //

  // Rcpp::StringVector df_names = df.names();
  // Rcpp::Rcout << df_names << std::endl;
  //
  // Rcpp::NumericVector lons = df["lon"];
  // Rcpp::NumericVector lats = df["lat"];
  // //return lons;
  //
  //
  // R_xlen_t n_1 = lons.size();
  // R_xlen_t n_2 = lats.size();
  //
  // R_xlen_t n = n_1 + n_2;
  //
  // Rcpp::NumericVector binary_res( n );
  //
  // R_xlen_t i;
  // for( i = 0; i < n_1; i++ ) {
  //   binary_res[i] = lons[i];
  // }
  //
  // int idx = 0;
  // for( i = n_1; i < n; i++ ) {
  //   binary_res[i] = lats[ idx ];
  //   idx++;
  // }
  //
  // return binary_res;


  //
  // Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns, digits );
  //
  // res[0] = js_data;
  //
  // SEXP legend = lst[ "legend" ];
  // if ( jsonify_legend ) {
  //   legend = jsonify::api::to_json( legend );
  //
  //   Rcpp::StringVector sv_leg = Rcpp::as< Rcpp::StringVector>( legend );
  //   // Rcpp::Rcout << "legend: " << sv_leg << std::endl;
  //
  //   res[1] = sv_leg;
  // } else {
  //   res[1] = legend;
  // }
  //
  // res.names() = Rcpp::CharacterVector::create("data", "legend");
  // return res;
}



  /*
   * expects `data` to be data.frame withn lon & lat & elev columns. The 'bool elevation'
   * argument must be set to 'true', and the 'geometry_columns' should contain an 'elevation'
   * value - 'geometry_column <- list( geometry = c("lon","lat","elevation") )'
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::List& geometry_columns,
      bool jsonify_legend,
      bool elevation,
      int digits = -1,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson6" << std::endl;
    // Rcpp::Rcout << "legend digits: " << legend_digits << std::endl;

    Rcpp::List res(2);
    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true, // factors as string
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_z_atomise( df, geometry_columns, digits );


    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::StringVector geometry_columns,
      bool jsonify_legend,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "create_geojson7" << std::endl;

    Rcpp::List res(2);

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      true, // factors as string
      colour_format
    );

    //return lst;

    SEXP df = lst["data"];

    //Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    Rcpp::StringVector js_data = jsonify::api::to_json( df );

    res[0] = js_data;

    SEXP legend = lst[ "legend" ];
    if ( jsonify_legend ) {
      legend = jsonify::api::to_json( legend );

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
