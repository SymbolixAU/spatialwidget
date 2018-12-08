#ifndef R_SPATIALWIDGET_DATA_CONSTRUCTION_H
#define R_SPATIALWIDGET_DATA_CONSTRUCTION_H

#include <Rcpp.h>
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace construction {

  inline void construct_df( Rcpp::List& df, int& nrows ) {

    if ( nrows < 1 ) {
      Rcpp::stop("Error creating data layer");
    }

    Rcpp::IntegerVector nv = Rcpp::seq(1, nrows);
    df.attr("class") = "data.frame";
    df.attr("row.names") = nv;
  }

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
  		Rcpp::List& params,
  		Rcpp::StringVector& data_names,
  		Rcpp::List& lst_defaults,
  		Rcpp::DataFrame& data,
  		int& data_rows) {

  	int n = params.size();
  	int colIndex = -1;

  	if (param_names.size() != n ) {
  	  Rcpp::stop("unsuitable data object");
  	}

  	// iterate each of the parameters
  	for (int i = 0; i < n; i ++ ) {
  		// if the param element is length 1; check if it's a column name

  		Rcpp::String this_param = param_names[i];

			if( TYPEOF( params[i] ) == STRSXP ) {
				// it's a string
				// is it also a column name

				Rcpp::String param_value = params[i];

				// returns -1 if length != 1
				colIndex = spatialwidget::utils::where::where_is( param_value, data_names );

				if ( colIndex == -1 ) {
				  continue;
				}

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

  	construct_df( lst_defaults, data_rows );
  	return lst_defaults;
  }

} // namespace construction
} // namespace spatialwidget



#endif
