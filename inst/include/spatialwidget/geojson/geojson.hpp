#ifndef R_SPATIALWIDGET_GEOJSONSF_H
#define R_SPATIALWIDGET_GEOJSONSF_H

#include <Rcpp.h>
//#include <boost/math/common_factor.hpp>

#include "geojsonsf/geojsonsf.h"
#include "geojsonsf/utils/utils.hpp"
#include "geojsonsf/geometries/sizes.hpp"

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

        // Rcpp::Rcout << "downcast_geometry: " << downcast_geometry << std::endl;
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
      Rcpp::StringVector geometries ) {

    // std::string geom_column = sf.attr("sf_column");
    //int n_geometries = geometries.size();
    if ( geometries.size() != 1) {
      Rcpp::stop("Down-casting only supported for single-sfc column objects");
    }
    //int geom;
    const char* geom_column = geometries[0];

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;  // single geometry column
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    size_t property_multiplier = 0;
    std::string geom_type;
    Rcpp::CharacterVector cls;

    int property_counter = 0;
    for (int i = 0; i < sf.length(); i++) {
      // if (column_names[i] != geom_column) {
      //   property_names[property_counter] = column_names[i];
      //   property_counter++;
      // }

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

      Rcpp::List sfc = sf[ geom_column ];
      SEXP sfg = sfc[ i ];

      cls = geojsonsf::getSfClass(sfg);
      geom_type = cls[1];

      if ( geom_type == "GEOMETRYCOLLECTION" ) {
        Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
      }

      property_multiplier = geojsonsf::sizes::geometry_size( sfg, geom_type, cls );
      // Rcpp::Rcout << "property_multiplier: " << property_multiplier << std::endl;

      for( int geometry = 0; geometry < property_multiplier; geometry++ ) {

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

        //for ( geom = 0; geom < n_geometries; geom++ ) {
        //  const char* geom_column = geometries[ geom ];

          writer.String( geom_column );
          //Rcpp::List sfc = sf[ geom_column ];
          //write_geometry( writer, sfc, i );
          write_geometry( writer, sfc, i, geometry, geom_type, cls );
        //}
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
  // for many columned sf objects
  inline Rcpp::StringVector to_geojson_multi_column_downcast_atomise(
      Rcpp::DataFrame& sf,
      Rcpp::StringVector geometries ) {

    int n_geometries = geometries.size();

    //int geom;
    //const char* geom_column = geometries[0];

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;  // single geometry column
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    size_t property_multiplier = 0;
    std::string geom_type;
    Rcpp::CharacterVector cls;

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

      // Rcpp::List sfc = sf[ geom_column ];
      // SEXP sfg = sfc[ i ];
      //
      // cls = geojsonsf::getSfClass(sfg);
      // geom_type = cls[1];

      // if ( geom_type == "GEOMETRYCOLLECTION" ) {
      //   Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
      // }

      // for downcasting multi-column sf objects, need to know the property_multiplier
      // for ALL geometry columns in this row
      geometry_size = 0;
      int row_multiplier = 0;
      //Rcpp::IntegerVector geometry_sizes( n_geometries );
      Rcpp::List downcast_geometries( n_geometries );

      for ( int geometry = 0; geometry < n_geometries; geometry++ ) {

        const char* geom_column = geometries[ geometry ];

        Rcpp::List sfc = sf[ geom_column ];
        SEXP sfg = sfc[ i ];

        cls = geojsonsf::getSfClass(sfg);
        geom_type = cls[1];

        if ( geom_type == "GEOMETRYCOLLECTION" ) {
          Rcpp::stop("GEOMETRYCOLLECTION not supported for down-casting");
        }

        geometry_size = geojsonsf::sizes::geometry_size( sfg, geom_type, cls );
        Rcpp::List this_geometry( geometry_size );
        for ( int j = 0; j < geometry_size; j++ ) {
          this_geometry[j] = sfg[j];
        }
        downcast_geometries[ geometry ] = this_geometry;
        geometry_sizes[ geometry ] = geometry_size; // keeping track of the size of each geometry

        // TODO each geometry will need to be multiplied by the length of all the other geometries
        if ( geometry == 0 ) {
          row_multiplier = geometry_size;
        } else {
          row_multiplier = row_multiplier * geometry_size;
        }

        Rcpp::Rcout << "row_multiplier: " << row_multiplier << std::endl;
      }
      //
      // we now have stored a list of each geometry - downcast_geometries
      // And we can create a matrix to store the indexes of the geometries
      // we need to access in each iteration.

      Rcpp::NumericMatrix geometry_indeces( row_multiplier, n_geometries );
      // fill this matrix
      //for( int r = 0; r < row_multiplier; r++ ) {
      for( int col = 0; col < n_geometries; col++ ) {
        Rcpp::IntegerVector this_vec( row_multiplier );
        // rep(1:5, times = ( 60 / 5 ))
        //geometry_indeces(r, c)
      }
      //}


      for( int geometry = 0; geometry < n_geometries; geometry++ ) {

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


        // loop over geometries, and replicate the geometry 'row_multiplier' number of times?

        writer.String("geometry");
        writer.StartObject();

        writer.String( geom_column );

        write_geometry( writer, sfc, i, geometry, geom_type, cls );

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

    //std::string geom_column = sf.attr("sf_column");

    // Rcpp::Rcout << "geom_column: " << geom_column << std::endl;

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names(sf.size() - 1);

    // Rcpp::Rcout << "n_col: " << n_cols << std::endl;
    // Rcpp::Rcout << "column_names: " << column_names << std::endl;


    int property_counter = 0;
    for (int i = 0; i < n_cols; i++) {
      if (column_names[i] != geom_column) {
        property_names[property_counter] = column_names[i];
        property_counter++;
      }
    }
    // Rcpp::Rcout << "property counter: " << property_counter << std::endl;

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

        // Rcpp::Rcout << "h: " << h << std::endl;
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

      //if ( n_properties > 0 ) {

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
      //} else {
        // force an empty properties object

      //}

      // now geometries
      //if( n_properties > 0 ) {
        writer.String("geometry");
      //}

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

      //if( n_properties > 0 ) {
        writer.EndObject();
      //}
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
