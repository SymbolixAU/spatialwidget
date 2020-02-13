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

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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

    // issue 46
    spatialwidget::utils::dates::dates_to_string( df );

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
 * expects `data` to be data.frame withn lon & lat columns.
 */
inline SEXP create_columnar(
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
    std::string colour_format = "rgb"  // can't be hex for columnar data
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

  //return lst;

  // lst is an object with a [data] and [legend] component

  // TODO
  // turn the colours into a single vector
  // r1, g1, b1, a1, r2, g2, b2, a2, ...

  // turn the coordinates into a single vector
  // p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, ...

  // all other columns are kept as-is (they should already be vectors)

  std::unordered_map< std::string, std::string>::iterator it;

  std::string colour_column;
  std::string opacity_column;

  //Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
  Rcpp::List lst_columnar = Rcpp::as< Rcpp::List >( lst["data"] );
  lst_columnar.attr("class") = R_NilValue;

  //return lst_columnar;

  for ( it = layer_colours.begin(); it != layer_colours.end(); ++it ) {

    colour_column = it->first;
    // opacity_column = it->second;

    Rcpp::NumericMatrix colour_mat = lst_columnar[ colour_column ];
    Rcpp::NumericMatrix t_colour_mat = Rcpp::transpose( colour_mat );
    t_colour_mat.attr("dim") = R_NilValue;

    // // convert matrix to vector
    // R_xlen_t increment = colour_mat.ncol();
    // R_xlen_t n = colour_mat.nrow() * increment;
    // R_xlen_t counter = 0;
    // R_xlen_t i = 0;
    // Rcpp::NumericVector colour_vec( n );
    // for( i = 0; i < n; i += increment, counter++ ) {
    //   Rcpp::Range rng( i, i + increment );
    //   colour_vec[ rng ] = colour_mat.row( counter );
    // }

    lst_columnar[ colour_column ] = t_colour_mat;
  }

  // now add on the geometry columns to our output, then jsonify it, adnd we're done.

  return lst_columnar;

  //
  // // now do geometry coordinates
  // // and still make it 'nested'
  //
  // //Rcpp::Rcout << "geometry_columns: " << geometry_columns.names() << std::endl;
  // Rcpp::List lst_geometry; // list containing all geometry vectors
  // //int n_geometries = geometry_columns.size();
  // Rcpp::StringVector geometry_names = geometry_columns.names();
  //
  // int n_rows = data.nrows();
  // //int n_cols = data.ncol();
  //
  // int n_lons = geometry_columns.size();
  // int n_lats = geometry_columns.size();  // it is expected the lon & lat data is the same size because
  //
  // //int n_lonlat = n_lons + n_lats;
  // //int n_properties = n_cols - n_lonlat; // LON & LAT columns
  // int i, j;
  //
  // Rcpp::StringVector lons( n_lons );  // the first elements of each 'geometry'
  // Rcpp::StringVector lats( n_lats );
  //
  // if( Rf_isNull( geometry_columns.names() ) ) {
  //   Rcpp::stop("Expecting a list of geometries, each element is named and contains the lon and lat columns");
  // }
  //
  // for ( i = 0; i < n_lons; i++ ) {
  //   Rcpp::StringVector this_lonlat = geometry_columns[ i ];
  //   lons[i] = this_lonlat[0];
  //   lats[i] = this_lonlat[1];
  // }
  //
  // for ( i = 0; i < n_lons; i++ ) {
  //   const char* this_lon = lons[i];
  //   const char* this_lat = lats[i];
  //   // for data.frames, can simply extract vector
  //   // for sf objects, I need to implement sfheaders::to_df
  //   Rcpp::NumericVector nv_lon = data[ this_lon ];
  //   Rcpp::NumericVector nv_lat = data[ this_lat ];
  //
  //   Rcpp::Rcout << "nv_lon :" << nv_lon << std::endl;
  //   Rcpp::Rcout << "nv_lat :" << nv_lat << std::endl;
  //
  //   Rcpp::NumericVector coords( n_rows * 2 );
  //   int counter = 0;
  //   int increment = 2;
  //   //Rcpp::NumericVector v = Rcpp::NumericVector::create( nv_lon[i], nv_lat[i] );
  //   for( j = 0; j < nv_lon.size(); j+= increment, counter++ ) {
  //     coords[ j ] = nv_lon[ counter ];
  //     coords[ j + 1 ] = nv_lat[ counter ];
  //   }
  //
  //   Rcpp::String nme = geometry_names[i];
  //   Rcpp::Rcout << "name: " << nme.get_cstring() << std::endl;
  //
  //   lst_geometry[ nme.get_cstring() ] = coords;
  // }
  //
  // spatialwidget::utils::remove::remove_list_elements( lst_columnar, lats );
  // spatialwidget::utils::remove::remove_list_elements( lst_columnar, lons );
  //
  //
  // lst_columnar[ "geometry" ] = lst_geometry;
  //
  // return lst_columnar;
  //
  // Rcpp::StringVector js_data = jsonify::api::to_json(
  //   lst_columnar, true, digits, false, true, "column"
  // );
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
  // //res.names() = Rcpp::CharacterVector::create("data", "legend");
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

} // namespace api
} // namespace spatialwidget

#endif
