#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geometries/sizes.hpp"
#include "geojsonsf/write_geojson.hpp"
#include "geojsonsf/geojson/write_geometry.hpp"

#include "spatialwidget/spatialwidget.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/writers/simple.hpp"
#include "jsonify/to_json/writers/complex.hpp"
#include "colourvalues/api/api.hpp"

namespace spatialwidget {
namespace geojson {

  /*
   * converts mesh data structure to geojson
   */
  inline Rcpp::StringVector to_geojson_mesh(
    Rcpp::List& mesh,
    Rcpp::StringVector vertices
  ) {

    Rcpp::String vertex_b = vertices[0];
    Rcpp::String vertex_i = vertices[1];
    Rcpp::NumericMatrix vb = mesh[ vertex_b ];
    Rcpp::NumericMatrix ib = mesh[ vertex_i ];

    // each column of each row of ib gives the row of vb containing coordinates which form the mesh
    // as we're working with polygons, we can turn the coordinates into list of matrices
    size_t n_row = ib.nrow();
    size_t n_col = ib.ncol();
    size_t n_coords = vb.nrow();

    Rcpp::List sfc( n_col );
    Rcpp::List z_values( n_col ); // for creating a list-column of the z attributes

    Rcpp::NumericVector polygon_indeces( n_row );
    Rcpp::NumericVector polygon_coordinates( n_row );

    size_t i, j;

    // TODO:
    // - extract the 'z' elements, create a vector (of averages)
    // - then apply colourvalues
    //Rcpp::NumericVector avg_z( n_col );

    //Rcpp::NumericVector avg_z( n_col );

    for( i = 0; i < n_col; i++ ) {

      polygon_indeces = ib(Rcpp::_, i);
      //Rcpp::NumericMatrix a_polygon( n_row, n_coords );

      Rcpp::NumericVector z_vals( n_row );

      for( j = 0; j < n_row; j++ ) {
        int this_index = polygon_indeces[j];
        this_index = this_index - 1;

        //a_polygon(j, Rcpp::_) = vb(Rcpp::_, this_index);
        z_vals[ j ] = vb(2, this_index);

      }
      //avg_z[i] = Rcpp::mean( z_values );
      //Rcpp::Rcout << "z_values : " << z_values << std::endl;
      z_values(i) = z_vals;
    }


    std::string palette = "viridis";
    std::string na_colour = "#808080";
    Rcpp::NumericVector alpha(1);
    alpha[0] = 255.0;
    bool include_alpha = true;
    int n_summaries = 0;
    bool format = false;
    bool summary = false;
    int digits = 2;

    Rcpp::List colours = colourvalues::api::colour_values_hex(
      z_values, palette, alpha, na_colour, include_alpha, format, digits, summary, n_summaries
    );

    //Rcpp::StringVector first_colour = colours[1];
    //Rcpp::Rcout << "first_colour : " << first_colour << std::endl;

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();

    for( i = 0; i < n_col; i++ ) {

      // we're writing a POLYGON
      polygon_indeces = ib(Rcpp::_, i);
      Rcpp::NumericMatrix a_polygon( n_row, n_coords );
      //Rcpp::List sfg(1);
      //Rcpp::NumericVector z_values( n_row ); // each 'col' contains the index of the xyz1 coords


      writer.StartObject();
      geojsonsf::writers::start_features( writer );

      writer.String("geometry");
      writer.StartObject();


      writer.String("geometry");
      writer.StartObject();
      writer.String("type");
      writer.String("Polygon");
      writer.String("coordinates");
      writer.StartArray();

      for( j = 0; j < n_row; j++ ) {
        int this_index = polygon_indeces[j];
        this_index = this_index - 1;

        a_polygon(j, Rcpp::_) = vb(Rcpp::_, this_index);
        //z_values[ j ] = a_polygon(j, 2);

      }
      jsonify::writers::simple::write_value(writer, a_polygon);

      writer.EndArray();
      writer.EndObject();

      geojsonsf::writers::start_properties( writer );

      writer.StartObject();
      // TODO: properties
      writer.String("fill_colour");
      //double z = Rcpp::mean( z_values );
      Rcpp::StringVector poly_colours = colours[j];
      jsonify::writers::simple::write_value( writer, poly_colours, false );

      writer.EndObject();
      writer.EndObject();
      writer.EndObject();
    //avg_z[i] = Rcpp::mean( z_values );
    //writer.EndObject();
    }

    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;

  }

  /*
   * a variation on the atomise function to return an array of atomised features
   */
  inline Rcpp::StringVector to_geojson_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector& geometries,
      int digits,
      bool factors_as_string = true  // already used in parameters_to_data (parameters.hpp)
  ) {

    R_xlen_t n_geometries = geometries.size();
    R_xlen_t geom;

    R_xlen_t n_cols = sf.ncol();
    R_xlen_t n_properties = n_cols - n_geometries;
    R_xlen_t n_rows = sf.nrows();
    R_xlen_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names( n_properties );

    R_xlen_t property_counter = 0;

    for ( i = 0; i < sf.length(); i++) {
      Rcpp::String this_column = column_names[i];
      R_xlen_t idx = spatialwidget::utils::where::where_is( this_column, geometries );

      if ( idx == -1 ) {  // i.e., it's not in the vector of geometries
        property_names[ property_counter ] = column_names[i];
        property_counter++;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();

    for( i = 0; i < n_rows; i++ ) {

      writer.StartObject();
      geojsonsf::writers::start_features( writer );
      geojsonsf::writers::start_properties( writer );

      writer.StartObject();

      // properties first, then sfc
      for( j = 0; j < n_properties; j++ ) {
        const char *h = property_names[ j ];

        SEXP this_vec = sf[ h ];

        writer.String( h );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, factors_as_string );

        // Rcpp::StringVector geojson_test = sb.GetString();
        // Rcpp::Rcout << "geojson: " << geojson_test << std::endl;
      }
      writer.EndObject();

      writer.String("geometry");
      writer.StartObject();

      for ( geom = 0; geom < n_geometries; geom++ ) {
        const char* geom_column = geometries[ geom ];

        writer.String( geom_column );
        Rcpp::List sfc = sf[ geom_column ];
        geojsonsf::write_geometry::write_geometry( writer, sfc, i, digits );
      }

      writer.EndObject();
      writer.EndObject();
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }

  /*
   * converts 'sf' object to standard GeoJSON
   */
  inline Rcpp::StringVector to_geojson(
      Rcpp::DataFrame& sf,
      std::string geom_column,
      int digits,
      bool factors_as_string = true  // already used in parameters_to_data (parameters.hpp)
  ) {

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

    R_xlen_t n_cols = sf.ncol();
    R_xlen_t n_properties = n_cols - 1;
    R_xlen_t n_rows = sf.nrows();
    R_xlen_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    R_xlen_t property_counter = 0;
    for ( i = 0; i < n_cols; i++) {
      if (column_names[i] != geom_column) {
        property_names[property_counter] = column_names[i];
        property_counter++;
      }
    }

    writer.StartObject();
    geojsonsf::writers::start_feature_collection( writer );

    writer.StartArray();

    for( i = 0; i < n_rows; i++ ) {

      writer.StartObject();

      geojsonsf::writers::start_features( writer );
      geojsonsf::writers::start_properties( writer );
      writer.StartObject();

      for( j = 0; j < n_properties; j++ ) {
        const char *h = property_names[ j ];

        SEXP this_vec = sf[ h ];

        writer.String( h );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, factors_as_string  );
      }
      writer.EndObject();

      writer.String("geometry");
      Rcpp::List sfc = sf[ geom_column ];
      geojsonsf::write_geometry::write_geometry( writer, sfc, i, digits );

      writer.EndObject();
    }

    writer.EndArray();
    writer.EndObject();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }

  // list of geometries is designed for lon & lat columns of data
  inline Rcpp::StringVector to_geojson_atomise(
      Rcpp::DataFrame& df,
      Rcpp::List& geometries, // i.e., list(origin = c("start_lon", "start_lat", destination = c("end_lon", "end_lat")))
      int digits,
      bool factors_as_string = true  // already used in parameters_to_data (parameters.hpp)
  ) {

    R_xlen_t n_cols = df.ncol();
    R_xlen_t n_rows = df.nrows();

    R_xlen_t n_lons = geometries.size();
    R_xlen_t n_lats = geometries.size();  // it is expected the lon & lat data is the same size because

    R_xlen_t n_lonlat = n_lons + n_lats;
    R_xlen_t n_properties = n_cols - n_lonlat; // LON & LAT columns

    // it comes as columns on a data.frame
    R_xlen_t i, j;
    Rcpp::StringVector lons( n_lons );  // the first elements of each 'geometry'
    Rcpp::StringVector lats( n_lats );

    if( Rf_isNull( geometries.names() ) ) {
      Rcpp::stop("Expecting a list of geometries, each element is named and contains the lon and lat columns");
    }

    Rcpp::StringVector geometry_names = geometries.names();

    for ( i = 0; i < n_lons; i++ ) {
      Rcpp::StringVector this_lonlat = geometries[i];
      lons[i] = this_lonlat[0];
      lats[i] = this_lonlat[1];
    }

    Rcpp::StringVector column_names = df.names();
    Rcpp::StringVector property_names( n_properties );

    Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XY", "POINT", "sfg");

    R_xlen_t property_counter = 0;

    for ( i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];

      R_xlen_t idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      R_xlen_t idx_lat = spatialwidget::utils::where::where_is( this_column, lats );

      if ( idx_lon == -1 && idx_lat == -1 ) {
        property_names[property_counter] = column_names[i];
        property_counter++;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();

    for( i = 0; i < n_rows; i++ ) {

      writer.StartObject();
      geojsonsf::writers::start_features( writer );
      geojsonsf::writers::start_properties( writer );

      writer.StartObject();

      // properties first, then sfc
      for( j = 0; j < n_properties; j++ ) {
        const char *h = property_names[ j ];
        SEXP this_vec = df[ h ];

        writer.String( h );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, factors_as_string );
        //jsonify::writers::complex::write_value( writer, this_vec, true, -1, true, true, "row", i );
      }

      writer.EndObject();

      writer.String("geometry");

      writer.StartObject();
      for ( j = 0; j < n_lons; j++ ) {
        const char* this_lon = lons[j];
        const char* this_lat = lats[j];
        Rcpp::NumericVector nv_lon = df[this_lon];
        Rcpp::NumericVector nv_lat = df[this_lat];
        SEXP sfg = Rcpp::NumericVector::create( nv_lon[i], nv_lat[i] );

        writer.String( geometry_names[j] );

        geojsonsf::write_geometry::write_geometry( writer, sfg, cls, digits );
      }
      writer.EndObject();
      writer.EndObject();
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }


  // list of geometries is designed for lon & lat & z columns of data
  inline Rcpp::StringVector to_geojson_z_atomise(
      Rcpp::DataFrame& df,
      Rcpp::List& geometries, // i.e., list(origin = c("start_lon", "start_lat", destination = c("end_lon", "end_lat")))
      int digits,
      bool factors_as_string = true  // already used in parameters_to_data (parameters.hpp)
  ) {

    R_xlen_t n_cols = df.ncol();
    R_xlen_t n_rows = df.nrows();

    R_xlen_t n_lons = geometries.size();
    R_xlen_t n_lats = geometries.size();  // it is expected the lon & lat data is the same size because
    R_xlen_t n_elevs = geometries.size();

    R_xlen_t n_lonlat = n_lons + n_lats + n_elevs;
    R_xlen_t n_properties = n_cols - n_lonlat; // LON & LAT & ELEV columns

    // it comes as columns on a data.frame
    R_xlen_t i, j;
    Rcpp::StringVector lons( n_lons );  // the first elements of each 'geometry'
    Rcpp::StringVector lats( n_lats );
    Rcpp::StringVector elevs( n_elevs );

    if( Rf_isNull( geometries.names() ) ) {
      Rcpp::stop("Expecting a list of geometries, each element is named and contains the lon, lat and z columns");
    }

    Rcpp::StringVector geometry_names = geometries.names();

    // check there are three entries in the list
    Rcpp::StringVector this_lonlat;

    for ( i = 0; i < n_lons; i++ ) {
      this_lonlat = geometries[i];
      if ( this_lonlat.size() != 3 ) {
        Rcpp::stop("Expecting a list of geometries, each element is named and contains the lon, lat and z columns");
      }
      lons[i] = this_lonlat[0];
      lats[i] = this_lonlat[1];
      elevs[i] = this_lonlat[2];
    }

    Rcpp::StringVector column_names = df.names();
    Rcpp::StringVector property_names( n_properties );

    Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XYZ", "POINT", "sfg");

    R_xlen_t property_counter = 0;

    for ( i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];

      R_xlen_t idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      R_xlen_t idx_lat = spatialwidget::utils::where::where_is( this_column, lats );
      R_xlen_t idx_elev = spatialwidget::utils::where::where_is( this_column, elevs );

      if ( idx_lon == -1 && idx_lat == -1 && idx_elev == -1 ) {
        property_names[property_counter] = column_names[i];
        property_counter++;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();


    for( i = 0; i < n_rows; i++ ) {

      if ( n_properties > 0 ) {

        writer.StartObject();
        geojsonsf::writers::start_features( writer );
        geojsonsf::writers::start_properties( writer );

        writer.StartObject();

        // properties first, then sfc
        for( j = 0; j < n_properties; j++ ) {
          const char *h = property_names[ j ];

          SEXP this_vec = df[ h ];

          writer.String( h );
          jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, factors_as_string  );
        }
        writer.EndObject();
      }

      // now geometries
      if( n_properties > 0 ) {
        writer.String("geometry");
      }

      writer.StartObject();
      for ( j = 0; j < n_lons; j++ ) {
        const char* this_lon = lons[j];
        const char* this_lat = lats[j];
        const char* this_elev = elevs[j];

        Rcpp::NumericVector nv_lon = df[this_lon];
        Rcpp::NumericVector nv_lat = df[this_lat];
        Rcpp::NumericVector nv_elev = df[this_elev];
        SEXP sfg = Rcpp::NumericVector::create( nv_lon[i], nv_lat[i], nv_elev[i] );

        writer.String( geometry_names[j] );

        geojsonsf::write_geometry::write_geometry( writer, sfg, cls, digits );
      }
      writer.EndObject();

      if( n_properties > 0 ) {
        writer.EndObject();
      }
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }

} // namespace geojson
} // namespace spatialwidget

#endif
