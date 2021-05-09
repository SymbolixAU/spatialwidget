#ifndef R_SPATIALWIDGET_H
#define R_SPATIALWIDGET_H

#include "Rcpp.h"

// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/api/api.hpp"

// [[Rcpp::depends(jsonify)]]
#include "jsonify/jsonify.hpp"

// [[Rcpp::depends(geometries)]]
#include "geometries/geometries.hpp"

// [[Rcpp::depends(sfheaders)]]
#include "sfheaders/sfheaders.hpp"

// [[Rcpp::depends(interleave)]]
#include "interleave/interleave.hpp"

#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/data_construction/data_construction.hpp"
#include "spatialwidget/geojson/geojson.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/parameters/parameters.hpp"
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace api {


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

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true,   // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true,  // factors as strings
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true, // factors as string
      colour_format
    );

    //return lst;

    //Rcpp::DataFrame df = lst["data"];
    //return x;
    //spatialwidget::construction::construct_df( df, data_rows );
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true, // factors as string
      colour_format
    );

    //return lst;

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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
      std::string colour_format = "rgb"
  ) {

    // Rcpp::Rcout << "create_geojson7" << std::endl;

    Rcpp::List res(2);

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true, // factors as string
      colour_format
    );

    //return lst;

    //SEXP df = lst["data"];
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // // issue 46
    // spatialwidget::utils::dates::dates_to_string( df );


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

  /*
   * expects `data` to be data.frame with
   * no geometry columns. It only formats data
   * and doesn't create any JSON
   */
  inline SEXP format_data(
      Rcpp::DataFrame& data,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      std::string colour_format = "rgb"  // can't be hex for columnar data
  ) {

    Rcpp::List res(2);
    Rcpp::StringVector data_names = data.names();

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      true, // factors as string
      colour_format
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

    res[0] = df;
    res[1] = lst[ "legend" ];;

    res.names() = Rcpp::CharacterVector::create("data", "legend");
    return res;
  }

  /*
   * expects an interleaved object
   */
  inline SEXP create_interleaved(
      Rcpp::List& interleaved,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      Rcpp::StringVector& binary_columns,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "interleaved"  // can't be hex for columnar data
  ) {

    R_xlen_t i, j;
    Rcpp::List res(2);

    Rcpp::DataFrame data = Rcpp::as< Rcpp::DataFrame >( interleaved["data"] );
    Rcpp::IntegerVector repeats = Rcpp::as< Rcpp::IntegerVector >( interleaved["geometry_coordinates"] );
    R_xlen_t total_colours = interleaved["total_coordinates"];
    Rcpp::IntegerVector geometry_coordinates = interleaved[ "geometry_coordinates" ];
    Rcpp::IntegerVector start_indices = interleaved["start_indices"];
    Rcpp::NumericVector coordinates = interleaved["coordinates"];
    int stride = interleaved["stride"];

    Rcpp::StringVector data_names = data.names();

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,              // used when the column is not a list-column(?)
      total_colours,
      true, // factors as string
      colour_format
    );

    //return lst;
    Rcpp::List df = lst["data"];

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

    Rcpp::IntegerVector expanded_index( data_rows );
    R_xlen_t counter = 0;

    R_xlen_t n_geometries = geometry_coordinates.length();

    for( i = 0; i < n_geometries; ++i ) {
      R_xlen_t expand_by = geometry_coordinates[ i ];

      for( j = 0; j < expand_by; ++j ) {
        expanded_index[ counter + j ] = i;
      }
      counter = counter + expand_by;
    }

    Rcpp::StringVector binary_names = df.names();

    for( i = 0; i < binary_columns.length(); ++i ) {

      Rcpp::String to_find = binary_columns[ i ];
      R_xlen_t name_position = geometries::utils::where_is( to_find, binary_names );
      SEXP v = df[ name_position ];
      if( TYPEOF( v ) != VECSXP ) {
        geometries::utils::expand_vector( df, v, expanded_index, name_position );
      } else {
        // Lists just need to be un-list
        // I'm working on the assumption the list will have the same number of elements
        // as coordinates
        Rcpp::List lst = Rcpp::as< Rcpp::List >( v );
        df[ name_position ] = geometries::utils::unlist_list( lst );

      }
    }

    // Also expand the colours if they are HEX values
    // because they haven't gone through colour_values,
    // so there is only one colour per geometry
    // but we need the colour per coordinate.
    // and then convert to RGBA, and then interleave
    std::unordered_map< std::string, std::string>::iterator it;
    std::string colour_column;
    std::string opacity_column;

    for ( it = layer_colours.begin(); it != layer_colours.end(); ++it ) {
      colour_column = it->first;

      SEXP col = df[ colour_column ];
      if( spatialwidget::utils::colour::is_hex( col ) ) {
        // 1. Fill
        R_xlen_t name_position = geometries::utils::where_is( colour_column, binary_names );
        geometries::utils::expand_vector( df, col, expanded_index, name_position );
        // 2. Convert
        // It's a hex, which means it's a STRSXP
        SEXP expanded_col = df[ colour_column ];
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( expanded_col );
        Rcpp::IntegerMatrix colour_mat = colourvalues::convert::convert_hex_to_rgb( sv );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( colour_mat );
        nm = nm / 255;
        // 3. Interleave
        df[ name_position ] = interleave::interleave( nm );

      }
    }

    Rcpp::List res_list = Rcpp::List::create(
      Rcpp::_["coordinates"] = coordinates,
      Rcpp::_["start_indices"] = start_indices,
      Rcpp::_["data"] = df,
      Rcpp::_["stride"] = stride
    );

    res[0] = jsonify::api::to_json(
      res_list, false, digits, true, true, "col"
    );

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
   * expects `data` to be data.frame with lon & lat columns. The geometry_columns
   * argument is a named list, list(myGeometry = c("lon","lat")),
   */
  inline SEXP create_columnar(
      Rcpp::DataFrame& data,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector& parameter_exclusions,
      Rcpp::List& geometry_columns,  // a list, so we get a named object in the final JSON
      bool jsonify_legend,
      int digits = -1,
      std::string colour_format = "rgb"  // can't be hex for columnar data
  ) {

    Rcpp::List res(2);
    Rcpp::StringVector data_names = data.names();
    R_xlen_t data_n_row = data.nrow();

    Rcpp::IntegerVector repeats(1); // not used
    R_xlen_t total_colours = 0; // not used

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows,
      parameter_exclusions,
      repeats,
      total_colours,
      false, // factors as string
      colour_format
    );

    std::unordered_map< std::string, std::string>::iterator it;

    std::string colour_column;
    std::string opacity_column;

    Rcpp::List lst_columnar = Rcpp::as< Rcpp::List >( lst["data"] );
    lst_columnar.attr("class") = R_NilValue;

    for ( it = layer_colours.begin(); it != layer_colours.end(); ++it ) {

      colour_column = it->first;
      // opacity_column = it->second;

      Rcpp::NumericMatrix colour_mat = lst_columnar[ colour_column ];
      Rcpp::NumericMatrix t_colour_mat = Rcpp::transpose( colour_mat );

      t_colour_mat.attr("dim") = R_NilValue;

      lst_columnar[ colour_column ] = t_colour_mat;
    }

    // combine the lon, lat, z, m values into a single vector
    // need to loop over the geometry_columns list
    // list( myGeometry = c('x','y'), myOtherGeometry = c('xx','yy'))
    R_xlen_t i, j, k;
    R_xlen_t n_geometries = geometry_columns.size();

    if( n_geometries == 0 ) {
      Rcpp::stop("spatialwidget - missing geometry columns");
    }

    Rcpp::StringVector geometry_names = geometry_columns.names();

    for( i = 0; i < n_geometries; ++i ) {

      Rcpp::List this_geometry = geometry_columns[ i ];
      Rcpp::String geom_name = geometry_names[ i ];

      R_xlen_t dimension = this_geometry.size();

      Rcpp::NumericVector coordinates( data_n_row * dimension );
      R_xlen_t idx = 0;

      for( j = 0; j < dimension; ++j ) {
        Rcpp::String coord = this_geometry[ j ];
        Rcpp::NumericVector nv = lst_columnar[ coord ];

        for( k = 0; k < data_n_row; ++k ) {
          idx = k * dimension + j;
          coordinates( idx ) = nv[ k ];
        }
      }

      lst_columnar[ geom_name ] = coordinates;
    }

    // TODO:
    // - remove the extra 'lon' & 'lat' (& z & m ) columns from lst_columnar,
    // - because we don't use them; we get the coords directly from 'data'.
    // - only need to keep them iff deck.gl let's us use them directly,
    // - rather than combining into one long vector

    Rcpp::StringVector js_data = jsonify::api::to_json(
      lst_columnar, false, digits, false, true, "column"
    );

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
