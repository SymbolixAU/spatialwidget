#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/geometries/sizes.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

#include "spatialwidget/geojson/write_geojson.hpp"


namespace spatialwidget {
namespace geojson {

  inline void cls_check( Rcpp::CharacterVector& cls ) {
    if (cls.size() != 3 ) {
      Rcpp::stop("unknown sf class");
    }
  }

  template< typename Writer >
  inline void write_geometry(Writer& writer, SEXP sfg, Rcpp::CharacterVector& cls ) {

    std::string geom_type;
    geom_type = cls[1];

    int sfglength = geojsonsf::utils::get_sexp_length( sfg );

    if (sfglength == 0) {
      writer.Null();
    } else {

      bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
      if ( isnull ) {
        writer.Null();
      } else {
        geojsonsf::writers::begin_geojson_geometry(writer, geom_type);
        write_geojson(writer, sfg, geom_type, cls );
        geojsonsf::writers::end_geojson_geometry( writer, geom_type );
      }
    }
  }

  template< typename Writer >
  inline void write_geometry(Writer& writer, Rcpp::List& sfc, int i) {

    SEXP sfg = sfc[ i ];

    std::string geom_type;
    Rcpp::CharacterVector cls = geojsonsf::getSfClass(sfg);
    cls_check( cls );
    geom_type = cls[1];

    // need to keep track of GEOMETRYCOLLECTIONs so we can correctly close them
    bool isGeometryCollection = (geom_type == "GEOMETRYCOLLECTION") ? true : false;

    int sfglength = geojsonsf::utils::get_sexp_length( sfg );

    if (sfglength == 0) {
      writer.Null();
    } else {

      bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
      if ( isnull ) {
        writer.Null();
      } else {
        geojsonsf::writers::begin_geojson_geometry(writer, geom_type);
        write_geojson(writer, sfg, geom_type, cls );

        geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
        geojsonsf::writers::end_geojson_geometry( writer, geom_type );
      }
    }
  }

  template< typename Writer >
  inline void write_geometry(Writer& writer, Rcpp::List& sfc, int i, int geometry,
                      std::string& geom_type, Rcpp::CharacterVector& cls ) {

    SEXP sfg = sfc[ i ];
    std::string downcast_geometry;

    if ( geom_type == "MULTIPOINT") {
      downcast_geometry = "POINT";
    } else if ( geom_type == "MULTILINESTRING" ) {
      downcast_geometry = "LINESTRING";
    } else if ( geom_type == "MULTIPOLYGON" ) {
      downcast_geometry = "POLYGON";
    } else {
      downcast_geometry = geom_type;
    }

    // need to keep track of GEOMETRYCOLLECTIONs so we can correctly close them
    bool isGeometryCollection = (geom_type == "GEOMETRYCOLLECTION") ? true : false;

    int sfglength = geojsonsf::utils::get_sexp_length( sfg );

    if (sfglength == 0) {
      writer.Null();
    } else {

      bool isnull = geojsonsf::utils::is_null_geometry( sfg, geom_type );
      if ( isnull ) {
        writer.Null();
      } else {

        geojsonsf::writers::begin_geojson_geometry( writer, downcast_geometry );
        write_geojson( writer, sfg, geom_type, cls, geometry );

        geom_type = (isGeometryCollection) ? "GEOMETRYCOLLECTION" : geom_type;
        geojsonsf::writers::end_geojson_geometry( writer, downcast_geometry );
      }
    }
  }


  /*
  * a variation on the atomise function to return an array of atomised features
  */
  inline Rcpp::StringVector to_geojson_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector& geometries ) {

    int n_geometries = geometries.size();
    int geom;

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - n_geometries;
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names( n_properties );

    int property_counter = 0;

    for (int i = 0; i < sf.length(); i++) {
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

        jsonify::writers::write_value( writer, h );
        jsonify::dataframe::dataframe_cell( writer, this_vec, i );
      }
      writer.EndObject();

      writer.String("geometry");
      writer.StartObject();

      for ( geom = 0; geom < n_geometries; geom++ ) {
        const char* geom_column = geometries[ geom ];

        writer.String( geom_column );
        Rcpp::List sfc = sf[ geom_column ];
        write_geometry( writer, sfc, i );
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
      std::string geometry ) {

    const char* geom_column = geometry.c_str();

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;  // single geometry column
    size_t n_rows = sf.nrows();
    size_t i, j, i_geometry;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    size_t property_multiplier = 0;
    std::string geom_type;
    Rcpp::CharacterVector cls;

    size_t property_counter = 0;
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
      cls_check( cls );
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

          jsonify::writers::write_value( writer, h );
          jsonify::dataframe::dataframe_cell( writer, this_vec, i );
        }
        writer.EndObject();

        writer.String("geometry");
        writer.StartObject();

        writer.String( geom_column );
        write_geometry( writer, sfc, i, i_geometry, geom_type, cls );

        writer.EndObject();
        writer.EndObject();
      }
    }

    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }


  // -----------------------WIP---------------------
  // down-casts MULTIGEOMETRIES to their simpler geometry
  // for two-sfc-columned sf objects
  inline Rcpp::StringVector to_geojson_downcast_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector geometries )
    {

    size_t n_geometries = geometries.size();
    if ( n_geometries != 2 ) {
      Rcpp::stop("Only supports 2-column sf objects");
    }

    size_t n_cols = sf.ncol();
    size_t n_rows = sf.nrows();
    size_t i, j, geometry, geometry_column;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    std::string geom_type;
    Rcpp::CharacterVector cls;

    size_t property_counter = 0;
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
      size_t row_multiplier = 0;
      Rcpp::IntegerVector geometry_sizes( n_geometries );

      for ( geometry = 0; geometry < n_geometries; geometry++ ) {

        const char* geom_column = geometries[ geometry ];

        Rcpp::List sfc = sf[ geom_column ];
        SEXP sfg = sfc[ i ];

        cls = geojsonsf::getSfClass(sfg);
        cls_check( cls );
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

          jsonify::writers::write_value( writer, h );
          jsonify::dataframe::dataframe_cell( writer, this_vec, i );
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
          cls_check( cls );
          geom_type = cls[1];

          writer.String( geom_column );
          int geometry_index = geometry_indeces(geometry, geometry_column) - 1;
          write_geometry( writer, sfc, i, geometry_index, geom_type, cls);
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
  // -----------------------WIP---------------------


  /*
   * converts 'sf' object to standard GeoJSON
   */
  inline Rcpp::StringVector to_geojson( Rcpp::DataFrame& sf, std::string geom_column ) {

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;
    size_t n_rows = sf.nrows();
    size_t i, j;
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

        jsonify::writers::write_value( writer, h );
        jsonify::dataframe::dataframe_cell( writer, this_vec, i );
      }
      writer.EndObject();

      writer.String("geometry");
      Rcpp::List sfc = sf[ geom_column ];
      write_geometry( writer, sfc, i );

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
      Rcpp::List& geometries ) // i.e., list(origin = c("start_lon", "start_lat", destination = c("end_lon", "end_lat")))
  {

    size_t n_cols = df.ncol();
    size_t n_rows = df.nrows();

    size_t n_lons = geometries.size();
    size_t n_lats = geometries.size();  // it is expected the lon & lat data is the same size because

    size_t n_lonlat = n_lons + n_lats;
    size_t n_properties = n_cols - n_lonlat; // LON & LAT columns

    // it comes as columns on a data.frame
    size_t i, j;
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

          jsonify::writers::write_value( writer, h );
          jsonify::dataframe::dataframe_cell( writer, this_vec, i );
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

          write_geometry( writer, sfg, cls );
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
      Rcpp::List& geometries ) // i.e., list(origin = c("start_lon", "start_lat", destination = c("end_lon", "end_lat")))
  {

    size_t n_cols = df.ncol();
    size_t n_rows = df.nrows();

    size_t n_lons = geometries.size();
    size_t n_lats = geometries.size();  // it is expected the lon & lat data is the same size because
    size_t n_elevs = geometries.size();

    size_t n_lonlat = n_lons + n_lats + n_elevs;
    size_t n_properties = n_cols - n_lonlat; // LON & LAT & ELEV columns

    // it comes as columns on a data.frame
    size_t i, j;
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

    for (int i = 0; i < df.length(); i++) {

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

          jsonify::writers::write_value( writer, h );
          jsonify::dataframe::dataframe_cell( writer, this_vec, i );
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

        write_geometry( writer, sfg, cls );
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
