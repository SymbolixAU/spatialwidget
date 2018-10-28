#ifndef R_SPATIALWIDGET_PALETTE_H
#define R_SPATIALWIDGET_PALETTE_H

#include <Rcpp.h>
#include "spatialwidget/spatialwidget.hpp"
#include "spatialwidget/utils/utils.hpp"

//#include <Rcpp/Benchmark/Timer.h>

namespace spatialwidget {
namespace palette {

  const Rcpp::StringVector default_palette = "viridis";
  const std::string default_na_colour = "#808080FF";

  /*
   * resolve_palette
   * determines if the user supplied a palette, or should use default
   */
  inline SEXP resolve_palette( Rcpp::List& lst_params, Rcpp::List& params ) {

  	SEXP pal = default_palette;
  	Rcpp::StringVector sv = lst_params[ "parameter" ];
  	int idx =  spatialwidget::utils::find_character_index_in_vector( sv, "palette" );
  	//pal = idx >= 0 ? params[ idx ] : pal;

  	if (idx >= 0 ) {
  		// if function, evaluate it? (or do this in R before entering Rcpp?)
  		pal = params[ idx ];
  	}
  	return pal;
  }

  inline Rcpp::List colour_with_palette(
  		SEXP& palette,
  		Rcpp::StringVector& fill_colour_vec,
  		Rcpp::NumericVector& alpha,
  		std::string& na_colour,
  		bool& include_alpha) {

  	switch ( TYPEOF( palette ) ) {
  	case 1: { // SYMSXP
  	Rcpp::stop("Unsupported palette type");
  	break;
  }
  	case 14: { // REALSXP (i.e, matrix)
  		Rcpp::NumericMatrix thispal = Rcpp::as< Rcpp::NumericMatrix >( palette );
  		return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, include_alpha, true );
  		break;
  	}
  	case 16: {
  		std::string thispal = Rcpp::as< std::string>( palette );
  		return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, alpha, include_alpha, true );
  		break;
  	}
  	default: {
  		Rcpp::stop("Unsupported palette type");
  	}
  	}
  	return ""; // never reached
  }


	inline Rcpp::List colour_with_palette(
			SEXP& palette,
			Rcpp::NumericVector& fill_colour_vec,
			Rcpp::NumericVector& alpha,
			std::string& na_colour,
			bool& include_alpha) {

		int n_summaries = 5;

		switch ( TYPEOF( palette ) ) {
		case 1: { // SYMSXP
		Rcpp::stop("Unsupported palette type");
		break;
	}
		case 14: { // REALSXP (i.e, matrix)
			//Rcpp::Rcout << "caes 14" << std::endl;
			Rcpp::NumericMatrix thispal = Rcpp::as< Rcpp::NumericMatrix >( palette );
			return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, include_alpha, n_summaries );
			break;
		}
		case 16: {
			std::string thispal = Rcpp::as< std::string>( palette );
			return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, alpha, include_alpha, n_summaries );
			break;
		}
		default: {
			Rcpp::stop("Unsupported palette type");
		}
		}
		return ""; // never reached
	}

} // namespace palette
} // namespace spatialwidget

#endif
