#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/geometries/sizes.hpp"
#include "geojsonsf/write_geojson.hpp"
#include "geojsonsf/geojson/write_geometry.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/writers/simple.hpp"
//#include "jsonify/to_json/dataframe.hpp"

namespace spatialwidget {
namespace geojson {

  /*
   * a variation on the atomise function to return an array of atomised features
   */
  inline Rcpp::StringVector to_geojson_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector& geometries,
      int digits) {

    int n_geometries = geometries.size();
    int geom;

    int n_cols = sf.ncol();
    int n_properties = n_cols - n_geometries;
    int n_rows = sf.nrows();
    int i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names( n_properties );

    int property_counter = 0;

    for ( i = 0; i < sf.length(); i++) {
      Rcpp::String this_column = column_names[i];
      int idx = spatialwidget::utils::where::where_is( this_column, geometries );

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
        // jsonify::dataframe::dataframe_cell( writer, this_vec, i );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true );
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

  // down-casts MULTIGEOMETRIES to their simpler geometry
  // only for one-column sfc objects
  inline Rcpp::StringVector to_geojson_downcast_atomise(
      Rcpp::DataFrame& sf,
      std::string geometry,
      int digits ) {


    const char* geom_column = geometry.c_str();

    int n_cols = sf.ncol();
    int n_properties = n_cols - 1;  // single geometry column
    int n_rows = sf.nrows();
    int i, j, i_geometry;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    int property_multiplier = 0;
    std::string geom_type;
    Rcpp::CharacterVector cls;

    int property_counter = 0;
    for ( i = 0; i < n_cols; i++ ) {

      Rcpp::String this_column = column_names[i];

      if ( this_column.get_cstring() != geometry ) {  // i.e., it's not the geometry
        property_names[ property_counter ] = column_names[i];
        property_counter++;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();

    for( i = 0; i < n_rows; i++ ) {

      Rcpp::List sfc = sf[ geom_column ];
      SEXP sfg = sfc[ i ];

      cls = geojsonsf::getSfClass(sfg);
      geojsonsf::write_geometry::cls_check( cls );
      geom_type = cls[1];

      if ( geom_type == "GEOMETRYCOLLECTION" ) {
        Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
      }

      property_multiplier = geojsonsf::sizes::geometry_size( sfg, geom_type, cls );

      for( i_geometry = 0; i_geometry < property_multiplier; i_geometry++ ) {

        writer.StartObject();
        geojsonsf::writers::start_features( writer );
        geojsonsf::writers::start_properties( writer );

        writer.StartObject();

        // properties first, then sfc
        for( j = 0; j < n_properties; j++ ) {
          const char *h = property_names[ j ];

          SEXP this_vec = sf[ h ];

          writer.String( h );
          jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true  );
        }
        writer.EndObject();

        writer.String("geometry");
        writer.StartObject();

        writer.String( geom_column );
        geojsonsf::write_geometry::write_geometry( writer, sfc, i, i_geometry, geom_type, cls, digits );

        writer.EndObject();
        writer.EndObject();
      }
    }

    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }

  // down-casts MULTIGEOMETRIES to their simpler geometry
  // for two-sfc-columned sf objects
  inline Rcpp::StringVector to_geojson_downcast_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector geometries,
      int digits)
  {

    int n_geometries = geometries.size();
    if ( n_geometries != 2 ) {
      Rcpp::stop("Only supports 2-column sf objects");
    }

    int n_cols = sf.ncol();
    int n_rows = sf.nrows();
    int i, j;
    int geometry, geometry_column;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    std::string geom_type;
    Rcpp::CharacterVector cls;

    int property_counter = 0;
    for ( i = 0; i < n_cols; i++) {

      Rcpp::String this_column = column_names[i];
      int idx = spatialwidget::utils::where::where_is( this_column, geometries );

      if ( idx == -1 ) {  // i.e., it's not in the vector of geometries
        property_names[ property_counter ] = column_names[i];
        property_counter++;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );
    writer.StartArray();

    for( i = 0; i < n_rows; i++ ) {

      int geometry_size = 0;
      int row_multiplier = 0;
      Rcpp::IntegerVector geometry_sizes( n_geometries );

      for ( geometry = 0; geometry < n_geometries; geometry++ ) {

        const char* geom_column = geometries[ geometry ];

        Rcpp::List sfc = sf[ geom_column ];
        SEXP sfg = sfc[ i ];

        cls = geojsonsf::getSfClass(sfg);
        geojsonsf::write_geometry::cls_check( cls );
        geom_type = cls[1];

        if ( geom_type == "GEOMETRYCOLLECTION" ) {
          Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
        }

        geometry_size = geojsonsf::sizes::geometry_size( sfg, geom_type, cls );
        geometry_sizes[ geometry ] = geometry_size; // keeping track of the size of each geometry

        if ( geometry == 0 ) {
          row_multiplier = geometry_size;
        } else {
          row_multiplier = row_multiplier * geometry_size;
        }
      }
      //
      // we now have stored a list of each geometry - downcast_geometries
      // And we can create a matrix to store the indexes of the geometries
      // we need to access in each iteration.

      Rcpp::IntegerMatrix geometry_indeces( row_multiplier, n_geometries );  // for OD, n_geometries should be 2
      Rcpp::IntegerVector xx = Rcpp::seq_len( geometry_sizes[0] );
      Rcpp::IntegerVector yy = Rcpp::seq_len( geometry_sizes[1] );
      Rcpp::IntegerVector one = Rcpp::rep( xx, yy.size() );
      Rcpp::IntegerVector two = Rcpp::rep_each( yy, xx.size() );

      geometry_indeces( Rcpp::_, 0 ) = one;
      geometry_indeces( Rcpp::_, 1 ) = two;

      for( geometry = 0; geometry < row_multiplier; geometry++ ) {
        // loop over all down-casted geometries for this row

        writer.StartObject();
        geojsonsf::writers::start_features( writer );
        geojsonsf::writers::start_properties( writer );

        writer.StartObject();

        // properties first, then sfc
        for( j = 0; j < property_counter; j++ ) {
          const char *h = property_names[ j ];

          SEXP this_vec = sf[ h ];

          writer.String( h );
          //jsonify::dataframe::dataframe_cell( writer, this_vec, i );
          jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true );
        }
        writer.EndObject();


        // loop over geometries, and replicate the geometry 'row_multiplier' number of times?
        writer.String("geometry");
        writer.StartObject();

        for ( geometry_column = 0; geometry_column < n_geometries; geometry_column++ ) {

          const char* geom_column = geometries[ geometry_column ];

          Rcpp::List sfc = sf[ geom_column ];
          SEXP sfg = sfc[ i ];

          cls = geojsonsf::getSfClass(sfg);
          geojsonsf::write_geometry::cls_check( cls );
          geom_type = cls[1];

          writer.String( geom_column );
          int geometry_index = geometry_indeces(geometry, geometry_column) - 1;
          geojsonsf::write_geometry::write_geometry( writer, sfc, i, geometry_index, geom_type, cls, digits);
        }

        writer.EndObject();
        writer.EndObject();
      }
    }

    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }


  /*
   * converts 'sf' object to standard GeoJSON
   */
  inline Rcpp::StringVector to_geojson( Rcpp::DataFrame& sf, std::string geom_column, int digits ) {

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

    int n_cols = sf.ncol();
    int n_properties = n_cols - 1;
    int n_rows = sf.nrows();
    int i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    int property_counter = 0;
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
        //jsonify::dataframe::dataframe_cell( writer, this_vec, i );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true  );
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
      int digits )
  {

    int n_cols = df.ncol();
    int n_rows = df.nrows();

    int n_lons = geometries.size();
    int n_lats = geometries.size();  // it is expected the lon & lat data is the same size because

    int n_lonlat = n_lons + n_lats;
    int n_properties = n_cols - n_lonlat; // LON & LAT columns

    // it comes as columns on a data.frame
    int i, j;
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

    int property_counter = 0;

    for (int i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];

      int idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      int idx_lat = spatialwidget::utils::where::where_is( this_column, lats );

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
        //jsonify::dataframe::dataframe_cell( writer, this_vec, i );
        jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true );
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
      int digits )
  {

    int n_cols = df.ncol();
    int n_rows = df.nrows();

    int n_lons = geometries.size();
    int n_lats = geometries.size();  // it is expected the lon & lat data is the same size because
    int n_elevs = geometries.size();

    int n_lonlat = n_lons + n_lats + n_elevs;
    int n_properties = n_cols - n_lonlat; // LON & LAT & ELEV columns

    // it comes as columns on a data.frame
    int i, j;
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

    int property_counter = 0;

    for ( i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];

      int idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      int idx_lat = spatialwidget::utils::where::where_is( this_column, lats );
      int idx_elev = spatialwidget::utils::where::where_is( this_column, elevs );

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
          //jsonify::dataframe::dataframe_cell( writer, this_vec, i );
          jsonify::writers::simple::write_value( writer, this_vec, i, -1, false, true  );
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
