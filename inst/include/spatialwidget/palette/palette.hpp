#ifndef R_SPATIALWIDGET_PALETTE_H
#define R_SPATIALWIDGET_PALETTE_H

#include <Rcpp.h>
#include "geometries/utils/vectors/vectors.hpp"
#include "colourvalues/api/api.hpp"
#include "spatialwidget/utils/utils.hpp"

//#include <Rcpp/Benchmark/Timer.h>

namespace spatialwidget {
namespace palette {


  /*
   * resolve_palette
   *
   * determines if the user supplied a palette, or should use default
   */
  inline SEXP resolve_palette( Rcpp::List& lst_params, Rcpp::List& params ) {

  	Rcpp::StringVector sv = lst_params[ "parameter" ];
  	int idx =  geometries::utils::where_is( "palette" , sv );

  	if (idx >= 0 ) {
  		// if function, evaluate it? (or do this in R before entering Rcpp?)
  		return params[ idx ];
  	} else {
  	  Rcpp::StringVector pal = "viridis";
  	  return pal;
  	}
  	return R_NilValue;
  }

// TODO - fill_colour_vec should be SEXP, so it's handled by colourvalues
  inline Rcpp::List colour_with_palette(
      SEXP& palette,
      SEXP& fill_colour_vec,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      Rcpp::NumericVector& alpha,
      std::string& na_colour,
      bool& include_alpha,
      std::string& colour_name,
      int legend_digits = 2,
      std::string colour_format = "hex"
  ) {

    // Rcpp::Rcout << "colour_format: " << colour_format << std::endl;

    // Rcpp::Rcout << "spw colour_name: " << colour_name.c_str() << std::endl;
    //Rcpp::Rcout << "alpha: " << alpha << std::endl;

    int n_summaries = 5;
    bool format = true;
    bool summary = true;
    //int legend_digits = 2;  // not used in character vector

    switch ( TYPEOF( palette ) ) {
      case VECSXP: {
        // extract the list elemetn for either 'fill' or 'stroke'
        Rcpp::List lst = Rcpp::as< Rcpp::List >( palette );
        SEXP pal = lst[ colour_name.c_str() ];
        return colour_with_palette(
          pal, fill_colour_vec, repeats, total_colours, alpha, na_colour,
          include_alpha, colour_name, legend_digits
          );
        break;
      }
      default: {
        if( colour_format == "hex" ) {
          return colourvalues::api::colour_values_hex(
            fill_colour_vec, palette, alpha, na_colour, include_alpha, format,
            legend_digits, summary, n_summaries
          );
      } else if ( colour_format == "rgb" ) {
        return colourvalues::api::colour_values_rgb(
          fill_colour_vec, palette, alpha, na_colour, include_alpha, format,
          legend_digits, summary, n_summaries
        );
      } else if ( colour_format == "interleaved" ) {

        // Rcpp::Rcout << "colour_format = interleaved" << std::endl;
        // Rcpp::Rcout << "total_colours: " << total_colours << std::endl;
        // Rcpp::Rcout << "repeats: " << repeats << std::endl;
        // Rcpp::Rcout << "spw - goign to colourvalues" << std::endl;

        SEXP res = colourvalues::api::colour_values_rgb_interleaved(
          fill_colour_vec, palette, alpha, repeats, total_colours, na_colour, include_alpha, format,
          legend_digits, summary, n_summaries
        );

        // Rcpp::Rcout << "sp colour_values_rgb_interleaved() done " << std::endl;
        // Rcpp::Rcout << "TYPEOF( res ) " << TYPEOF( res ) << std::endl;
        return res;

      } else {
        Rcpp::stop("spatialwidget - unknown colour format, expecting hex, rgb or interleaved");
      }
      break;
      }
    }
    return ""; // never reached
  }

} // namespace palette
} // namespace spatialwidget

#endif
