#ifndef R_SPATIALWIDGET_PARAMETERS_TO_DATA_H
#define R_SPATIALWIDGET_PARAMETERS_TO_DATA_H

#include <Rcpp.h>

#include "geometries/utils/vectors/vectors.hpp"

#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/colour/colour.hpp"
#include "spatialwidget/utils/utils.hpp"
//#include <Rcpp/Benchmark/Timer.h>

namespace spatialwidget {
namespace parameters {

  /*
   * construct params
   *
   * @param data   data.frame supplied
   * @param params list of paramters
   *
   * the \code{params} argument will be a named list (from R), where the names are
   * the parameters of a function, and the values are the values supplied by the user to the function.
   *
   * Creates a list
   * ["parameter"] - StringVector of the names of parameters
   * ["parameter_type"] - IntegerVector of the SEXP TYPE of parameter
   * ["data_column_index"] - IntegerVector of the column index in the data
   */
  inline Rcpp::List construct_params(
      Rcpp::DataFrame& data,
      Rcpp::List& params
  ) {

    int n_params = params.size();
    Rcpp::StringVector param_names = params.names();

    //Rcpp::Rcout << "param_names " << param_names << std::endl;

    Rcpp::IntegerVector parameter_r_types( n_params );
    Rcpp::IntegerVector data_column_index( n_params, -1 );
    Rcpp::StringVector data_names = data.names();

    int i = 0;
    int parameter_type;

    for (i = 0; i < n_params; i++) {
      parameter_type = TYPEOF( params[i] );
      parameter_r_types[i] = parameter_type;

      if ( parameter_type == STRSXP ) { // STRSXP (string vector)
        Rcpp::String param_value = params[i];
        data_column_index[i] = geometries::utils::where_is( param_value, data_names );
      }
    }
    return Rcpp::List::create(
      Rcpp::_["parameter"] = param_names,
      Rcpp::_["parameter_type"] = parameter_r_types,
      Rcpp::_["data_column_index"] = data_column_index
    );
  }

  /*
   * paramters to data
   */
  inline Rcpp::List parameters_to_data(
  		Rcpp::DataFrame& data,                // user-supplied data
  		Rcpp::List& params,                   // list of parameters from calling function
  		Rcpp::List& lst_defaults,
  		std::unordered_map< std::string, std::string > colour_columns,
  		Rcpp::StringVector& layer_legend,     // vector of colours to use in the legend
  		int& data_rows,
  		Rcpp::StringVector& parameter_exclusions,
  		Rcpp::IntegerVector& repeats,
  		R_xlen_t& total_colours,
  		bool factors_as_string = true,
  		std::string colour_format = "hex"
  ) {


    //Turn factors to strings
    if (factors_as_string ) {
      spatialwidget::utils::factors::factors_to_string( data );
    }

    // convert dates to characters
    // issue 46 - moved this outside
    //spatialwidget::utils::dates::dates_to_string( data );

  	Rcpp::StringVector param_names = params.names();
  	Rcpp::StringVector data_names = data.names();

  	// Rcpp::Rcout << "param_names " << param_names << std::endl;
  	// Rcpp::Rcout << "data_names " << data_names << std::endl;

  	Rcpp::List lst_params = construct_params( data, params );

  	Rcpp::List lst_legend = spatialwidget::legend::construct_legend_list(
  	  lst_params,
  	  params,
  	  param_names,
  	  layer_legend
  	);


  	Rcpp::StringVector legend_names = lst_legend.names();

  	std::unordered_map< std::string, std::string>::iterator it;

		bool include_legend;

		std::string colour_column;
		std::string opacity_column;

		for ( it = colour_columns.begin(); it != colour_columns.end(); ++it ) {

		  colour_column = it->first;
		  opacity_column = it->second;

		  // Rcpp::Rcout << "colour_column: " << colour_column << std::endl;
		  // Rcpp::Rcout << "opacity_column: " << opacity_column << std::endl;

		  include_legend = geometries::utils::where_is( colour_column, legend_names ) >= 0 ? true : false;

	    spatialwidget::colour::resolve_colour(
	      lst_params,
	      params,
	      data,
	      lst_defaults,
	      colour_column,
	      opacity_column,
	      lst_legend,
	      include_legend,
	      repeats,
	      total_colours,
	      colour_format
	      );

	    // Rcpp::Rcout << "sw resolved colour" << std::endl;
		}

		//return lst_defaults;

  	//Rcpp::stop("stopping");

  	// list(
  	//  colourType ("fill_colour", "stroke_colour", "stroke_from", "stroke_to")
  	//  type = ("gradient","category")
  	//  title = "title"
  	//  legend = data.frame( colour = "#", variable = x)
  	//  css = ""
  	//  position = NULL <<---- NOT USED IN spatialwidget
  	//)

  	// need to remove any paramters which won't be used in the data being plotted
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, parameter_exclusions );

    Rcpp::StringVector colours_remove = spatialwidget::utils::map::extract_map( colour_columns, colour_columns.size() * 2 );
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, colours_remove );
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, layer_legend );

  	//lst_params = construct_params( data, params );
  	//return lst_params;
  	//return lst_defaults;

  	// Rcpp::Rcout << "sw - construcint data" << std::endl;

  	Rcpp::List df = spatialwidget::construction::construct_data(
  		param_names,
  		params,
  		data_names,
  		lst_defaults,
  		data,
  		data_rows
  	);

    // if 'interleaving', we don't want a final df, because columns lenghts are / can be different
    if( colour_format != "interleaved" ) {
      // Rcpp::Rcout << "constructing data" << std::endl;
      spatialwidget::construction::construct_df( df, data_rows );
    }

  	Rcpp::List result = Rcpp::List::create(
  		Rcpp::_["data"] = df,
  		Rcpp::_["legend"] = lst_legend
  	);

  	return result;
  }
} // namespace parameters
} // namespace spatialwidget

#endif
