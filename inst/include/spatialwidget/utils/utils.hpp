#ifndef R_SPATIALWIDGET_UTILS_H
#define R_SPATIALWIDGET_UTILS_H

#include <Rcpp.h>
#include "spatialwidget/utils/fill/fill.hpp"
#include "spatialwidget/utils/where/where.hpp"
#include "spatialwidget/utils/remove/remove.hpp"

namespace spatialwidget {
namespace utils {


  inline void construct_df(Rcpp::List& df, int& nrows) {

  	if (nrows < 1) {
  		Rcpp::stop("Error creating data layer");
  	}

  	Rcpp::IntegerVector nv = Rcpp::seq(1, nrows);
  	df.attr("class") = "data.frame";
  	df.attr("row.names") = nv;
  }

  inline bool param_is_string( SEXP param ) {
  	return TYPEOF( param ) == STRSXP;  // string vectors
  }

	/*
	 * determins the data type in the list of argument parameters (not the data)
	 */
	inline int get_parameter_r_type( SEXP param ) {
		return TYPEOF( param );
	}



  /*
   * construct params
   *
   * Creates a list
   * ["parameter"] - StringVector of the names of parameters
   * ["parameter_type"] - IntegerVector of the TYPE of parameter
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
			parameter_type = spatialwidget::utils::get_parameter_r_type( params[i] );
			parameter_r_types[i] = parameter_type;

			if ( parameter_type == STRSXP ) { // STRSXP (string vector)

				Rcpp::String param_value = params[i];
				// data_column_index[i] = spatialwidget::utils::data_column_index( param_value, data_names );
				data_column_index[i] = spatialwidget::utils::where::where_is( param_value.get_cstring(), data_names );
			}
		}
		return Rcpp::List::create(
			Rcpp::_["parameter"] = param_names,
			Rcpp::_["parameter_type"] = parameter_r_types,
			Rcpp::_["data_column_index"] = data_column_index
		);
	}

} // namespace utils
} // namespace spatialwidget

Rcpp::List create_data(
    Rcpp::DataFrame& data,
    Rcpp::List& params, Rcpp::List& lst_defaults,
    Rcpp::StringVector& layer_columns,
    std::unordered_map< std::string, std::string >& layer_colours,
    Rcpp::StringVector& layer_legend,
    int& data_rows);

#endif
