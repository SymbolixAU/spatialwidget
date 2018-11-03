#ifndef R_SPATIALWIDGET_DATA_CONSTRUCTION_H
#define R_SPATIALWIDGET_DATA_CONSTRUCTION_H

#include <Rcpp.h>
#include "spatialwidget/utils/utils.hpp"

#include "spatialwidget/utils/fill/fill.hpp"

namespace spatialwidget {
namespace construction {

  /*
   * Assess each variable passed in to the R function as an argument, determines
   * if it's a column of data, or a single value to use as the whole column.
   *
   * If it's a column of data, that column is used. If it's a single value,
   * that value is 'cbind'-ed as a column of data
   *
   * This assumes the fill and stroke colours have already been resolved and removed
   * from the list of parameters
   */
  inline Rcpp::DataFrame construct_data(
  		Rcpp::StringVector& param_names,
  		//Rcpp::StringVector& required_columns,
  		Rcpp::List& params,
  		Rcpp::StringVector& data_names,
  		Rcpp::List& lst_defaults,
  		Rcpp::DataFrame& data,
  		int& data_rows) {

  	int n = params.size();
  	int colIndex = -1;

  	// Rcpp::Rcout << "param names: " << param_names << std::endl;

  	// iterate each of the parameters
  	for (int i = 0; i < n; i ++ ) {
  		// if the param element is length 1; check if it's a column name

  		Rcpp::String this_param = param_names[i];
  		// Rcpp::Rcout << "this_param: " << this_param.get_cstring() << std::endl;

  		//int idx = spatialwidget::where_is( this_param.get_cstring(), required_columns );
  		//Rcpp::Rcout << "index of this param: " << idx << std::endl;

  		// If we use R to construct the parameter list, we don't need to do this check
  		//if ( idx >= 0 ) {
  			// to get into this if statement the parameter passed into the R function is
  			// to be used as a column of data

  			if( spatialwidget::utils::param_is_string( params[i] ) ) {
  				// it's a string
  				// is it also a column name

  				Rcpp::String param_value = params[i];

  				// Rcpp::Rcout << "param value: " << param_value << std::endl;

  				// returns -1 if length != 1
  				// colIndex = spatialwidget::utils::data_column_index( param_value, data_names );
  				colIndex = spatialwidget::utils::where_is( param_value.get_cstring(), data_names );
  				// Rcpp::Rcout << "colIndex: " << colIndex << std::endl;

  				if ( colIndex >= 0 ) {
  					// The param_value IS a column name
  					lst_defaults[ this_param ] = data[ colIndex ];

  				} else {
  					// IT's not a column name, but it is still a string
  					// and needs to be applied to all rows
  					//SEXP value = param_value;
  					lst_defaults[ this_param ] = spatialwidget::utils::fill::fill_vector( param_value, data_rows );

  				}
  			} else {
  				// paramter is not a string, so it can't be a column name
  				SEXP value = params[i];
  			  spatialwidget::utils::fill::fill_vector( lst_defaults, this_param, value, data_rows );
  			}
  		} // TODO( is there an 'else' condition? )

  	// Rcpp::Rcout << "constructing df: " << std::endl;
  	spatialwidget::utils::construct_df( lst_defaults, data_rows );
  	// Rcpp::Rcout << "constructed" << std::endl;
  	// Rcpp::StringVector default_names = lst_defaults.names();
  	// Rcpp::Rcout << "default_names: " << default_names << std::endl;
  	return lst_defaults;
  }

} // namespace construction
} // namespace spatialwidget



#endif
