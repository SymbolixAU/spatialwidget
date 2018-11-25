#ifndef SPATIALWIDGET_UTILS_MAP_H
#define SPATIALWIDGET_UTILS_MAP_H

#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace map {

  inline Rcpp::StringVector extract_map(std::unordered_map<std::string, std::string> const& input_map, int n) {
    Rcpp::StringVector vals( n );
    int i = 0;
    for (auto const& element : input_map) {
      vals[i] = element.first;
      i++;
      vals[i] = element.second;
      i++;
    }
    return vals;
  }

} // namespace map
} // namespace utils
} // namespace spatialwidget

#endif
