#ifndef R_SPATIALWIDGET_PARAMETERS_TO_DATA_H
#define R_SPATIALWIDGET_PARAMETERS_TO_DATA_H

#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/legend/legend.hpp"
#include "spatialwidget/colour/colour.hpp"
//#include <Rcpp/Benchmark/Timer.h>

namespace spatialwidget {
namespace parameters {

  inline Rcpp::StringVector extract_map(std::unordered_map<std::string, std::string> const& input_map, int n) {
    Rcpp::StringVector vals( n );
    int i = 0;
    for (auto const& element : input_map) {
      //retval.push_back(element.first);
      vals[i] = element.first;
      i++;
      vals[i] = element.second;
      i++;
    }
    return vals;
  }

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
      Rcpp::List& params) {

    int n_params = params.size();
    Rcpp::StringVector param_names = params.names();
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
        data_column_index[i] = spatialwidget::utils::where::where_is( param_value.get_cstring(), data_names );
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
  		Rcpp::List& data_types,               // column data types of 'data'
  		Rcpp::List& params,                   // list of parameters from calling function
  		Rcpp::List& lst_defaults,
  		//Rcpp::StringVector& layer_columns,
  		//Rcpp::StringVector& colour_columns,
  		std::unordered_map< std::string, std::string > colour_columns,
  		Rcpp::StringVector& legend_types,
  		int& data_rows) {

  	Rcpp::StringVector param_names = params.names();
  	Rcpp::StringVector data_names = data.names();

  	// Rcpp::Rcout << "data_names: " << data_names << std::endl;
  	// Rcpp::Rcout << "param name: " << param_names << std::endl;

  	Rcpp::List lst_params = construct_params( data, params );

  	// determine if a legend is required
  	// if legend == T, for each of the possible legend types for htis plot (scatter, polygon)
  	// create a list. e.g.,
  	// lst_legend[ "fill_colour" ] = true;
  	// lst_legend[ "stroke_colour" ] = false;

  	Rcpp::List lst_legend = spatialwidget::legend::construct_legend_list( lst_params, params, param_names, legend_types );

  	Rcpp::StringVector legend_names = lst_legend.names();
  	// Rcpp::Rcout << "legend_names: " <<  legend_names << std::endl;

  	std::unordered_map< std::string, std::string>::iterator it;

		bool include_legend;

		std::string colour_column;
		std::string opacity_column;

		for ( it = colour_columns.begin(); it != colour_columns.end(); ++it ) {

		  colour_column = it->first;
		  opacity_column = it->second;

		  // Rcpp::Rcout << "colour_column: " << colour_column << std::endl;
		  // Rcpp::Rcout << "opacity_column: " << opacity_column << std::endl;

		  include_legend = spatialwidget::utils::where::where_is( colour_column.c_str(), legend_names ) >= 0 ? true : false;
	    spatialwidget::colour::resolve_colour( lst_params, params, data, data_types, lst_defaults, colour_column.c_str(), opacity_column.c_str(),  lst_legend, include_legend );
		}

		// Rcpp::Rcout << "colours resolved" << std::endl;

  	// legend optinos
  	// IT's a list
  	// iterate the names

  	// required:
  	// - legend values
  	//
  	// list(
  	//  colourType ("fill_colour", "stroke_colour", "stroke_from", "stroke_to")
  	//  type = ("gradient","category")
  	//  title = "title"
  	//  legend = data.frame( colour = "#", variable = x)
  	//  css = ""
  	//  position = NULL <<---- NOT USED IN spatialwidget
  	//)

  	// need to remove any paramters which won't be used in the data being plotted
  	Rcpp::StringVector legend_params = Rcpp::StringVector::create("legend","legend_options"); // TODO( hard-coded?)
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, legend_params );

  	//int remove_size = ( colour_columns.size() * 2 ) + legend_types.size();
  	//Rcpp::Rcout << "remove_size: " << remove_size << std::endl;
  	//Rcpp::StringVector colours_remove( legend_types.size() );

    //Rcpp::StringVector test = extract_map( colour_columns, remove_size - legend_types.size() );
    //Rcpp::Rcout << "test: " << test << std::endl;

    Rcpp::StringVector colours_remove = extract_map( colour_columns, colour_columns.size() * 2 );


  	// Rcpp::StringVector colours_remove = Rcpp::StringVector::create(
  	//   "stroke_from","stroke_to","stroke_colour","fill_colour","stroke_from_opacity",
  	//   "stroke_to_opacity","stroke_opacity","fill_opacity","palette"
  	//   );

  	// Rcpp::Rcout << "param_names 1: " << param_names << std::endl;
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, colours_remove );
  	// Rcpp::Rcout << "param_names 2: " << param_names << std::endl;
  	spatialwidget::utils::remove::remove_list_elements( params, param_names, legend_types );
//
  	lst_params = construct_params( data, params );

  	// Rcpp::Rcout << "constructing data " << std::endl;

  	data_names = data.names();
  	// Rcpp::Rcout << "data_names2: " << data_names << std::endl;

  	Rcpp::DataFrame df = spatialwidget::construction::construct_data(
  		param_names,
  		//layer_columns,
  		params,
  		data_names,
  		lst_defaults,
  		data,
  		data_rows
  	);

  	/// Rcpp::Rcout << "data has been constructed" << std::endl;
  	// data_names = df.names();
  	// Rcpp::Rcout << "df_names: " << data_names << std::endl;

  	Rcpp::List result = Rcpp::List::create(
  		Rcpp::_["data"] = df,
  		Rcpp::_["legend"] = lst_legend
  	);

  	// Rcpp::Rcout << "returning list" << std::endl;
  	return result;
  }
} // namespace parameters
} // namespace spatialwidget

#endif
