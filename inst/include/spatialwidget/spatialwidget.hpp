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
      //t_colour_mat = t_colour_mat; / 255.0;  // TODO: remove if / when colourvalues returns scaled values
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
