#ifndef R_SPATIALWIDGET_UTILS_DATES_H
#define R_SPATIALWIDGET_UTILS_DATES_H

#include <Rcpp.h>
#include "jsonify/to_json/dates/dates.hpp"

namespace spatialwidget {
namespace utils {
namespace dates {

  inline bool is_in( const char* x, Rcpp::CharacterVector v ) {
    int n = v.size();
    int i;
    for( i = 0; i < n; i++ ) {
      if( v[i] == x ) {
        return true;
      }
    }
    return false;
  }

  template < int RTYPE >
  inline Rcpp::CharacterVector rClass( Rcpp::Vector< RTYPE > v ) {
    if( Rf_isNull( v.attr("class")) ) {
      return "";
    }
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getRClass( SEXP obj ) {

    switch( TYPEOF( obj ) ) {
    case REALSXP:
      return rClass< REALSXP >( obj );
      //return "numeric";
    case VECSXP:
      return rClass< VECSXP >( obj );
      //return "character";
    case INTSXP:
      return rClass< INTSXP >( obj );
      //return "numeric";
    case LGLSXP:
      //return rClass< LGLSXP >( obj );
      return "logical";
    case STRSXP:
      //return rClass< STRSXP >( obj );
      return "character";
    }
    return "";
  }

  inline void dates_to_string(
    Rcpp::List& data
  ) {
    int tp;
    int df_col;
    Rcpp::StringVector column_names = data.names();
    int n_cols = data.length();

    for( df_col = 0; df_col < n_cols; ++df_col ) {
      const char * col_name = column_names[ df_col ];
      tp = TYPEOF( data[ col_name ] );

      if( tp == REALSXP ) {
        Rcpp::CharacterVector cls = getRClass( data[ col_name ] );

        if(is_in( "Date", cls ) ) {
          Rcpp::NumericVector nv_dte = Rcpp::as< Rcpp::NumericVector >( data[ col_name ] );
          Rcpp::StringVector sv_dte = jsonify::dates::date_to_string( nv_dte );
          data[ col_name ] = sv_dte;

        } else if (is_in( "POSIXt", cls ) ) {
          Rcpp::NumericVector nv_psx = Rcpp::as< Rcpp::NumericVector >( data[ col_name ] );
          Rcpp::StringVector sv_psx = jsonify::dates::posixct_to_string( nv_psx );
          data[ col_name ] = sv_psx;
        }
      }
    }
  }

} // dates
} // utils
} // spatialwidget

#endif
