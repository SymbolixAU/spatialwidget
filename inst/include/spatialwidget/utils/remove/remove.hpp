#ifndef SPATIALWIDGET_UTILS_REMOVE_H
#define SPATIALWIDGET_UTILS_REMOVE_H

#include <Rcpp.h>

namespace spatialwidget {
namespace utils {
namespace remove {

  inline void remove_list_elements(
      Rcpp::List& list,
      Rcpp::StringVector& elements,
      Rcpp::StringVector& to_remove ) {

    elements = Rcpp::setdiff( elements,  to_remove );
    list = list[ elements ];
  }

  inline void remove_list_elements(
      Rcpp::List& list,
      Rcpp::StringVector& to_remove ) {

    Rcpp::StringVector elements = list.names();
    remove_list_elements( list, elements, to_remove );
  }

} // namespace where
} // namespace utils
} // namespace spatialwidget

#endif
