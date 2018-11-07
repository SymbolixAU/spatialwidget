#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/utils/utils.hpp"

#include "jsonify/jsonify.hpp"
#include "jsonify/to_json/dataframe.hpp"

#include "spatialwidget/geojson/write_geojson.hpp"


namespace spatialwidget {
namespace geojson {

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


  /*
  * a variation on the atomise function to return an array of atomised features
  */
  inline Rcpp::StringVector to_geojson_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector geometries ) {

    // Rcpp::Rcout << "to_geojson_atomise() " << std::endl;
    // TODO( receive the geometry columns as a StringVector, then iterate over those,
    //       creating an Array of GeoJSONs )

    int n_geometries = geometries.size();
    int geom;

    //std::string geom_column = sf.attr("sf_column");
    // Rcpp::Rcout << "geom_column: " << geom_column << std::endl;

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - n_geometries;
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names( n_properties );

    // Rcpp::Rcout << "n_cols: " << n_cols << std::endl;
    // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;
    // Rcpp::Rcout << "n_geometries: " << n_geometries << std::endl;
    // Rcpp::Rcout << "column_names: " << column_names << std::endl;

    int property_counter = 0;
    // Rcpp::Rcout << "sf.length: " << sf.length() << std::endl;

    for (int i = 0; i < sf.length(); i++) {
      Rcpp::String this_column = column_names[i];
      int idx = spatialwidget::utils::where::where_is( this_column, geometries );

      // Rcpp::Rcout << "this_column: " << this_column << std::endl;
      // Rcpp::Rcout << "idx: " << idx << std::endl;

      //if (column_names[i] != geom_column) {
      if ( idx == -1 ) {  // i.e., it's not in the vector of geometries
        // Rcpp::Rcout << "property counter: " << property_counter << std::endl;
        property_names[ property_counter ] = column_names[i];
        property_counter++;
        // Rcpp::Rcout << "property counter: " << property_counter << std::endl;
      }
    }

    // Rcpp::Rcout << "property names: " << property_names << std::endl;

    // Rcpp::Rcout << "starting sb " << std::endl;
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

          SEXP this_vec = sf[ h ];

          jsonify::writers::write_value( writer, h );
          jsonify::dataframe::dataframe_cell( writer, this_vec, i );
        }
        writer.EndObject();
      }

      // now geometries
      if( n_properties > 0 ) {
        writer.String("geometry");
      }

      //writer.StartArray();
      writer.StartObject();
      for ( geom = 0; geom < n_geometries; geom++ ) {
        const char* geom_column = geometries[ geom ];
        // writer.StartObject();
        writer.String( geom_column );
        Rcpp::List sfc = sf[ geom_column ];
        write_geometry( writer, sfc, i );
        // writer.EndObject();
      }
      writer.EndObject();
      //writer.EndArray();

      // Rcpp::List sfc = sf[ geom_column ];
      // write_geometry( writer, sfc, i );

      if( n_properties > 0 ) {
        writer.EndObject();
      }
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("json");
    return geojson;
  }

  inline Rcpp::StringVector to_geojson( Rcpp::DataFrame& sf ) {

    rapidjson::StringBuffer sb;
    rapidjson::Writer < rapidjson::StringBuffer > writer( sb );

    //Rcpp::Rcout << "finding geom" << std::endl;
    std::string geom_column = sf.attr("sf_column");
    //Rcpp::Rcout << "found geom" << std::endl;

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    int property_counter = 0;
    for (int i = 0; i < sf.length(); i++) {
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
    // Rcpp::StringVector& lons,
    // Rcpp::StringVector& lats ) {

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
    Rcpp::StringVector geometry_names = geometries.names();

    for ( i = 0; i < n_lons; i++ ) {
      Rcpp::StringVector this_lonlat = geometries[i];
      lons[i] = this_lonlat[0];
      lats[i] = this_lonlat[1];
    }


    // size_t n_lons = lons.size();
    // size_t n_lats = lats.size();
    // if ( n_lons != n_lats ) {
    //   Rcpp::stop("lons and lats are different sizes");
    // }

    // Rcpp::Rcout << "n_cols: " << n_cols << std::endl;
    // Rcpp::Rcout << "n_lonlat: " << n_lonlat << std::endl;
    // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;

    Rcpp::StringVector column_names = df.names();
    Rcpp::StringVector property_names( n_properties );

    // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;
    // Rcpp::Rcout << "column_names: " << column_names << std::endl;
    // Rcpp::Rcout << "property_names: " << property_names << std::endl;

    // the sfc_POINT
    // Rcpp::NumericVector nv_lon = df[lon];
    // Rcpp::NumericVector nv_lat = df[lat];

    Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XY", "POINT", "sfg");

    int property_counter = 0;

    for (int i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];
      // Rcpp::Rcout << "this_column: " << this_column << std::endl;

      int idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      int idx_lat = spatialwidget::utils::where::where_is( this_column, lats );

      if ( idx_lon == -1 && idx_lat == -1 ) {
        // Rcpp::Rcout << "setting property " << std::endl;
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

          // Rcpp::Rcout << "property: " << h << std::endl;

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
        Rcpp::NumericVector nv_lon = df[this_lon];
        Rcpp::NumericVector nv_lat = df[this_lat];
        SEXP sfg = Rcpp::NumericVector::create( nv_lon[i], nv_lat[i] );

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


  // list of geometries is designed for lon & lat columns of data
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
    Rcpp::StringVector geometry_names = geometries.names();
    // Rcpp::Rcout << "geometry_names: " << geometry_names << std::endl;
    // Rcpp::Rcout << "n_lons: " << n_lons << std::endl;
    // Rcpp::Rcout << "n_lonlat: " << n_lonlat << std::endl;
    // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;
    // Rcpp::Rcout << "n_elevs: " << n_elevs << std::endl;

    for ( i = 0; i < n_lons; i++ ) {
      Rcpp::StringVector this_lonlat = geometries[i];
      // Rcpp::Rcout << "this_longlat " << this_lonlat << std::endl;
      lons[i] = this_lonlat[0];
      lats[i] = this_lonlat[1];
      elevs[i] = this_lonlat[2];
    }

    Rcpp::StringVector column_names = df.names();
    Rcpp::StringVector property_names( n_properties );
    // Rcpp::Rcout << "column_names: " << column_names << std::endl;

    Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XYZ", "POINT", "sfg");

    int property_counter = 0;

    for (int i = 0; i < df.length(); i++) {

      Rcpp::String this_column = column_names[i];
      // Rcpp::Rcout << "this_column: " << this_column << std::endl;

      int idx_lon = spatialwidget::utils::where::where_is( this_column, lons );
      int idx_lat = spatialwidget::utils::where::where_is( this_column, lats );
      int idx_elev = spatialwidget::utils::where::where_is( this_column, elevs );

      if ( idx_lon == -1 && idx_lat == -1 && idx_elev == -1 ) {
        // Rcpp::Rcout << "setting property " << std::endl;
        property_names[property_counter] = column_names[i];
        property_counter++;
      }
    }

    // Rcpp::Rcout << "property_names: " << property_names << std::endl;

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

          // Rcpp::Rcout << "property: " << h << std::endl;

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
