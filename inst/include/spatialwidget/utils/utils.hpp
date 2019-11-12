#ifndef R_SPATIALWIDGET_UTILS_H
#define R_SPATIALWIDGET_UTILS_H

#include "spatialwidget/utils/fill/fill.hpp"
#include "spatialwidget/utils/factors/factors.hpp"
#include "spatialwidget/utils/where/where.hpp"
#include "spatialwidget/utils/remove/remove.hpp"
#include "spatialwidget/utils/map/map.hpp"
#include "spatialwidget/utils/colour/colour.hpp"

namespace spatialwidget {
namespace utils {

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

} // utils
} // spatialwidget

#endif
