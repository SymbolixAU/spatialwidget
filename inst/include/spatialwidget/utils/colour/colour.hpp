#ifndef SPATIALWIDGET_UTILS_COLOUR_H
#define SPATIALWIDGET_UTILS_COLOUR_H

#include <regex>
#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace colour {

  inline bool is_hex( std::string str ) {
    std::regex hex_regex("^#[0-9a-fA-F]{8}$|#[0-9a-fA-F]{6}$|#[0-9a-fA-F]{4}$|#[0-9a-fA-F]{3}$");
    bool res = std::regex_match( str, hex_regex );
    return res;
  }

} // namespace colour
} // namespace utils
} // namespace spatialwidget

#endif
