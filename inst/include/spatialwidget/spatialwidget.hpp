#ifndef R_SPATIALWIDGET_H
#define R_SPATIALWIDGET_H

#include "Rcpp.h"

// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/colours/colours_hex.hpp"

// [[Rcpp::depends(jsonify)]]
#include "jsonify/to_json.hpp"

#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/data_construction/data_construction.hpp"
//#include "spatialwidget/geojson/geometrycollection.hpp"
#include "spatialwidget/geojson/geojson.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/parameters/parameters.hpp"
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace api {

  /*
   * expects `data` to be an sf object
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types, // named list, names == data.names(), values == data.class[[1]] ?
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      Rcpp::StringVector geometry_columns ) {

    Rcpp::StringVector data_names = data.names();
    // Rcpp::Rcout << "data_names start: " << data_names << std::endl;

    // TODO receive the geometry columns from user input

    //std::string geom_column = data.attr("sf_column");
    // Rcpp::Rcout << "geom_column: " << geom_column << std::endl;
    // Rcpp::Rcout << "create_geojson" << std::endl;

    // Rcpp::Rcout << "parameters to data " << std::endl;
    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      data_types,
      params,
      lst_defaults,
      layer_colours,
      layer_legend,
      data_rows
    );

    // Rcpp::Rcout << "getting data from list " << std::endl;
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );

    // Rcpp::StringVector nmes = df.names();
    // Rcpp::Rcout << "nmes2: " << nmes << std::endl;

    SEXP legend = lst[ "legend" ];
    legend = jsonify::vectors::to_json( legend );

    // df.attr("sf_column") = geom_column;

    //Rcpp::Rcout << "js_data-ing" << std::endl;

    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, geometry_columns );
    //Rcpp::Rcout << "js_data: " << js_data << std::endl;

    return Rcpp::List::create(
      Rcpp::_["data"] = js_data,
      Rcpp::_["legend"] = legend
    );
  }

  /*
   * expects `data` to be data.frame withn lon & lat columns
   */
  inline Rcpp::List create_geojson(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows,
      const char* lon,
      const char* lat
  ) {

    Rcpp::StringVector data_names = data.names();
    // Rcpp::Rcout << "data_names start: " << data_names << std::endl;

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data, data_types,
      params, lst_defaults,
      layer_colours, layer_legend, data_rows
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    SEXP legend = lst[ "legend" ];
    legend = jsonify::vectors::to_json( legend );

    Rcpp::StringVector js_data = spatialwidget::geojson::to_geojson_atomise( df, lon, lat );

    return Rcpp::List::create(
      Rcpp::_["data"] = js_data,
      Rcpp::_["legend"] = legend
    );
  }

  /*
   * expects `data` to be data.frame withn a polyline
   */
  inline Rcpp::List create_polyline(
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& params,
      Rcpp::List& lst_defaults,
      std::unordered_map< std::string, std::string >& layer_colours,
      Rcpp::StringVector& layer_legend,
      int& data_rows
  ) {

    Rcpp::List lst = spatialwidget::parameters::parameters_to_data(
      data,
      data_types,
      params,
      lst_defaults,
      layer_colours, layer_legend, data_rows
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst["data"] );
    SEXP legend = lst[ "legend" ];
    legend = jsonify::vectors::to_json( legend );

    Rcpp::StringVector js_data = jsonify::dataframe::to_json( df );

    return Rcpp::List::create(
      Rcpp::_["data"] = js_data,
      Rcpp::_["legend"] = legend
    );
  }

} // namespace api
} // namespace spatialwidget

#endif
