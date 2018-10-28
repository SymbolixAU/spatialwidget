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
  inline Rcpp::StringVector to_geojson_atomise( Rcpp::DataFrame& sf ) {

    // Rcpp::Rcout << "to_geojson_atomise() " << std::endl;
    std::string geom_column = sf.attr("sf_column");
    // Rcpp::Rcout << "geom_column: " << geom_column << std::endl;

    size_t n_cols = sf.ncol();
    size_t n_properties = n_cols - 1;
    size_t n_rows = sf.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = sf.names();
    Rcpp::StringVector property_names( n_properties );

    // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;
    // Rcpp::Rcout << "column_names: " << column_names << std::endl;

    int property_counter = 0;
    // Rcpp::Rcout << "sf.length: " << sf.length() << std::endl;

    for (int i = 0; i < sf.length(); i++) {
      if (column_names[i] != geom_column) {
        // Rcpp::Rcout << "property counter: " << property_counter << std::endl;
        property_names[property_counter] = column_names[i];
        property_counter++;
        // Rcpp::Rcout << "property counter: " << property_counter << std::endl;
      }
    }

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

      Rcpp::List sfc = sf[ geom_column ];
      write_geometry( writer, sfc, i );

      if( n_properties > 0 ) {
        writer.EndObject();
      }
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
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
    geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
    return geojson;
  }


  inline Rcpp::StringVector to_geojson_atomise( Rcpp::DataFrame& df, const char* lon, const char* lat ) {

    size_t n_cols = df.ncol();
    size_t n_properties = n_cols - 2; // LON & LAT columns
    size_t n_rows = df.nrows();
    size_t i, j;
    Rcpp::StringVector column_names = df.names();
    Rcpp::StringVector property_names(df.size() - 1);

    // the sfc_POINT
    Rcpp::NumericVector nv_lon = df[lon];
    Rcpp::NumericVector nv_lat = df[lat];

    Rcpp::CharacterVector cls = Rcpp::CharacterVector::create("XY", "POINT", "sfg");

    int property_counter = 0;
    for (int i = 0; i < df.length(); i++) {
      if ( column_names[i] != lon && column_names[i] != lat ) {
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

      SEXP sfg = Rcpp::NumericVector::create(nv_lon[i], nv_lat[i]);
      write_geometry( writer, sfg, cls );

      if( n_properties > 0 ) {
        writer.EndObject();
      }
    }
    writer.EndArray();

    Rcpp::StringVector geojson = sb.GetString();
    geojson.attr("class") = Rcpp::CharacterVector::create("geojson","json");
    return geojson;
  }


} // namespace geojson
} // namespace spatialwidget

#endif
