#ifndef SPATIALWIDGET_UTILS_COLOUR_H
#define SPATIALWIDGET_UTILS_COLOUR_H

#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace colour {

  inline bool isHexDigit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
  }

  inline bool is_hex( std::string str ) {
    int len = str.length();
    if (len != 7 && len != 9 && len != 4 && len != 5) {
      return false; // Invalid length for a hex color
    }

    if (str[0] != '#') {
      return false; // Missing "#" at the beginning
    }

    for (int i = 1; i < len; i++) {
      if (!isHexDigit(str[i])) {
        return false; // Non-hexadecimal character found
      }
    }

    return true; // Passed all checks, valid hex color
  }

  inline bool is_hex( SEXP x ) {
    if( TYPEOF( x ) != STRSXP ) {
      return false;
    }

    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
    Rcpp::String first_colour = sv[0];
    return is_hex( first_colour.get_cstring() );
  }

} // namespace colour
} // namespace utils
} // namespace spatialwidget

#endif
