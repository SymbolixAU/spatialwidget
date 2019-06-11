#ifndef R_SPATIALWIDGET_LEGEND_H
#define R_SPATIALWIDGET_LEGEND_H

#include <Rcpp.h>
#include "spatialwidget/utils/utils.hpp"

namespace spatialwidget {
namespace legend {

  inline void set_legend_option(
      Rcpp::List& opts,
      std::string& option,
      std::string& value,
      std::string& colour_name
  ) {


    if ( opts.containsElementNamed( option.c_str() ) ) {
      SEXP s = opts[ option ];
      Rcpp::String s_value;
      switch( TYPEOF( s ) ) {
      case STRSXP: {
        s_value = Rcpp::as< Rcpp::String >( s );
        break;
      }
      case REALSXP :{
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( s );
        int i = iv[0];
        s_value = std::to_string( i );
        break;
      }
      case INTSXP: {
        int i = opts[ option ];
        s_value = std::to_string( i );
        break;
      }
      default: {
        Rcpp::stop("unknown legend_option type, expecting string or int value");
      }
      }
      value = s_value;
    } else if ( opts.containsElementNamed( colour_name.c_str() ) ) {
      Rcpp::List opts2 = opts[ colour_name ];
      set_legend_option( opts2, option, value, colour_name );
    }
  }


  /*
   * Construct Lgend List
   *
   * Creates a list where the name is the colour element, and the value is
   * TRUE or FALSE depending if the that colour is to be used in the legend
   *
   * e.g. list(fill_colour = TRUE, stroke_colour = FALSE)
   */
  inline Rcpp::List construct_legend_list(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::StringVector& param_names,
      Rcpp::StringVector& legend_types
  ) {

    legend_types = Rcpp::intersect( legend_types, param_names );

    int n = legend_types.size();
    int i;
    Rcpp::List legend( n );
    Rcpp::String this_legend;

    Rcpp::IntegerVector parameter_type = lst_params[ "parameter_type" ];

    for ( i = 0; i < n; i++ ) {
      legend[ i ] = false;
    }
    legend.names() = legend_types;

    // find the 'legend' argument
    int legend_location = spatialwidget::utils::where::where_is( "legend", param_names );

    if ( legend_location > -1 ) {

      SEXP lege = params[ legend_location ];

      switch( TYPEOF( lege ) ) {
      case LGLSXP: { // logical
        // the user supplied either legend = T or legend = F
        // if T, switch all the 'false' elements to true
        for ( i = 0; i < n; i++ ) {  // TODO( dont' swithc the FALSEs to TRUE)
          legend[ i ] = lege;
        }
        break;
      }
      case VECSXP: { // list
        // iterate the list, and, if the item is true, switch the element of the list to true
        Rcpp::List lege_list = Rcpp::as< Rcpp::List >( lege );
        n = lege_list.size();
        Rcpp::StringVector lege_list_names = lege_list.names();
        for (i = 0; i < n; i++ ) {
          this_legend = lege_list_names[ i ];
          legend[ this_legend ] = lege_list[ i ];
        }
        break;
      }
      default: {
        Rcpp::stop("unknown legend type");
      }
      }

    }
    return legend;
  }

} // namespace legend
} // namespace spatialwidget

#endif
