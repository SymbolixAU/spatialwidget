#include <Rcpp.h>
#include "spatialwidget/palette/palette.hpp"

/*
 * resolve palette
 *
 * @param lst_params named list( parameter = c(), parameter_type = c(), data_column_index = c() )
 * @param params the values supplied by the user when calling the function
 *
 * @return either the palette value supplied by the user, or the default "viridis"
 *
 */
// [[Rcpp::export]]
Rcpp::StringVector rcpp_resolve_palette( Rcpp::List lst_params, Rcpp::List params ) {
  SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );
  if ( TYPEOF( pal) == STRSXP ) {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( pal );
    return sv;
  }
  return R_NilValue;
}


/*
 * colour_str_with_palette
 *
 */
// [[Rcpp::export]]
Rcpp::List rcpp_colour_str_with_palette(
    SEXP palette,
    SEXP fill_colour_vec,
    Rcpp::NumericVector alpha,
    std::string na_colour,
    bool include_alpha,
    std::string colour_name) {
  return spatialwidget::palette::colour_with_palette(
    palette, fill_colour_vec, alpha, na_colour, include_alpha, colour_name
  );
}

/*
 * colour_with_num_with_palette
 *
 */
// [[Rcpp::export]]
Rcpp::List rcpp_colour_num_with_palette(
    SEXP palette,
    SEXP fill_colour_vec,
    Rcpp::NumericVector alpha,
    std::string na_colour,
    bool include_alpha,
    std::string colour_name,
    int legend_digits = 2) {

  return spatialwidget::palette::colour_with_palette(
    palette, fill_colour_vec, alpha, na_colour, include_alpha, colour_name, legend_digits
  );
}
