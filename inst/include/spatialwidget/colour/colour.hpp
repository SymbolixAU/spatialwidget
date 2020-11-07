#ifndef R_SPATIALWIDGET_COLOUR_H
#define R_SPATIALWIDGET_COLOUR_H

#include <Rcpp.h>

#include "geometries/utils/vectors/vectors.hpp"

#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/utils/utils.hpp"
#include "spatialwidget/legend/legend.hpp"

namespace spatialwidget {
namespace colour {

  const std::string default_na_colour = "#808080FF";

  inline Rcpp::List make_colours(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& lst_defaults,
      int col_index,
      SEXP& palette_type,
      Rcpp::NumericVector& alpha,
      std::string& colour_name,
      bool& include_legend,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      int legend_digits = 2,
      std::string colour_format = "hex"
    ) {

    // Rcpp::Rcout << "sw - make_colours" << std::endl;

    std::string na_colour = params.containsElementNamed( "na_colour" ) ?
    params["na_colour"] : default_na_colour;

    bool include_alpha = true;            // always true - deck.gl supports alpha

    SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );

    std::string format_type;

    if ( col_index == -1 ) {
      palette_type = lst_defaults[ colour_name.c_str() ];
    } else {
      Rcpp::String this_colour = params[ colour_name.c_str() ];
    }

    // here it's already a STRSXP, not factor (INTSXP)
    //Rcpp::Rcout << "palette_type: " << TYPEOF( palette_type ) << std::endl;
    //Rcpp::stop("stopping");

    switch ( TYPEOF( palette_type ) ) {
    case STRSXP: {} // string vector
    case LGLSXP: {  // logical vector
      // Rcpp::Rcout << "LGLSXP || STRSXP " << std::endl;
      Rcpp::StringVector colour_vec = Rcpp::as< Rcpp::StringVector >( palette_type );
      Rcpp::String first_colour = colour_vec[0];
      if ( spatialwidget::utils::colour::is_hex( first_colour.get_cstring() ) ) {

        Rcpp::StringVector lvls = Rcpp::unique( colour_vec );

        Rcpp::List legend = Rcpp::List::create(
          _["colours"] = colour_vec,
          _["summary_values"] = lvls,
          _["summary_colours"] = lvls
        );

        if( colour_format == "rgb" ) {
          Rcpp::IntegerMatrix colour_mat = colourvalues::convert::convert_hex_to_rgb( colour_vec );
          Rcpp::IntegerMatrix colour_mat_lvls = colourvalues::convert::convert_hex_to_rgb( lvls );

          legend["colours"] = colour_mat;
          legend["summary_colours"] = colour_mat_lvls;
        }


        if ( include_legend ) {
          legend[ "colour_type" ] = colour_name;
          legend[ "type" ] = "category";
        }
        return legend;

      } else {

        // Rcpp::Rcout << "spw else " << std::endl;
        Rcpp::List legend = spatialwidget::palette::colour_with_palette(
          pal, palette_type, repeats, total_colours, alpha, na_colour, include_alpha,
          colour_name, legend_digits, colour_format
        );

        // Rcpp::List legend = spatialwidget::palette::colour_with_palette(
        //   pal, colour_vec, alpha, na_colour, include_alpha, colour_name
        // );

        // TODO
        // - if numeric, it's 'gradient', else 'category'
        // - but factor needs to be category
        if ( include_legend ) {
          legend[ "colour_type" ] = colour_name;
          legend[ "type" ] = "category";
        }
        return legend;
     }
      break;
    }
    default: {

      // Rcpp::NumericVector colour_vec = Rcpp::as< Rcpp::NumericVector >( palette_type );
      // Rcpp::List legend = spatialwidget::palette::colour_with_palette(
      //   pal, colour_vec, alpha, na_colour, include_alpha, colour_name,
      //   legend_digits
      //   );
      // Rcpp::Rcout << "spw default" << std::endl;
      //Rcpp::Rcout << "alpha: " << alpha << std::endl;

      Rcpp::List legend = spatialwidget::palette::colour_with_palette(
        pal, palette_type, repeats, total_colours, alpha, na_colour, include_alpha,
        colour_name, legend_digits, colour_format
      );
      //Rcpp::stop("stopping");

      // Rcpp::Rcout << "sw made colour_with_palette" << std::endl;

      std::string legend_type = Rf_isFactor( palette_type )  ? "category" : "gradient";

      if ( include_legend ) {
        legend[ "colour_type" ] = colour_name;
        legend[ "type" ] = legend_type;
      }
      return legend;
      break;
    }
    }
  }

  inline void resolve_colour(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& lst_defaults,
      std::string& colour_name,
      std::string& opacity_name,
      Rcpp::List& lst_legend,
      bool& include_legend,
      Rcpp::IntegerVector& repeats,
      R_xlen_t& total_colours,
      std::string colour_format = "hex"
      //int legend_digits = 2
    ) {

    // Rcpp::Rcout << "resolve_colour" << std::endl;

    Rcpp::IntegerVector data_column_index = lst_params[ "data_column_index" ];
    Rcpp::IntegerVector parameter_type = lst_params[ "parameter_type" ];
    Rcpp::StringVector param_names = params.names();

    Rcpp::StringVector hex_strings( data.nrows() );

    double default_alpha = colour_format == "interleaved" ? 1.0 : 255.0;
    Rcpp::NumericVector alpha( 1, default_alpha );
    // Rcpp::Rcout << "alpha: " << alpha << std::endl;

    SEXP this_colour;

    int colour_location = geometries::utils::where_is( colour_name, param_names );
    int opacity_location = geometries::utils::where_is( opacity_name, param_names );

    // if 'colour_name' doesn't exist in the list of default, we need to make one

    int colourColIndex = colour_location >= 0 ? data_column_index[ colour_location ] : -1;
    int alphaColIndex = opacity_location >= 0 ? data_column_index[ opacity_location ] : -1;

    // Rcpp::Rcout << "colourColIndex: " << colourColIndex << std::endl;
    // Rcpp::Rcout << "alphaColIndex: " << alphaColIndex << std::endl;

    if ( colourColIndex >= 0 ) {
      this_colour = data[ colourColIndex ];
    } else {

      if ( colour_location >= 0 ) {

        SEXP val = params[ colour_location ];
        R_xlen_t n = data.nrows();
        Rcpp::String col_name = colour_name;
        spatialwidget::utils::fill::fill_vector( lst_defaults, col_name, val, n );

      } else {
        Rcpp::NumericVector nv( data.nrows(), 1.0 );
        this_colour = nv;
        lst_defaults[ colour_name.c_str() ] = nv; // need to add back to lst_defaults
      }
    }


    if ( alphaColIndex >= 0 ) {
      alpha = data[ alphaColIndex ];
    } else {

      int find_opacity = geometries::utils::where_is( opacity_name, param_names );
      if (find_opacity >= 0 ) {
        int a = params[ find_opacity ]; // will throw an error if not correct type
        alpha.fill( a );
      }
    }

    // TODO
    // get the 'legend_digits' before here so it goes into colourvalues
    //

    // this can't be replaced with 'include_legend'
    bool make_legend = false;
    int legend_digits = 2;
    std::string title;
    std::string css;
    std::string legend_digits_str = std::to_string( legend_digits );

    if ( lst_legend.containsElementNamed( colour_name.c_str() ) ) {
      make_legend = lst_legend[ colour_name.c_str() ];
    }

    if (lst_legend.containsElementNamed( colour_name.c_str() ) ) {

      if ( make_legend == true ) {

        SEXP t = params[ colour_name ];
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( t );
        Rcpp::String s = sv[0];
        title = s;
        css = "";
        //int legend_digits;

        if ( params.containsElementNamed("legend_options") ) {

          Rcpp::List opts = params[ "legend_options" ];
          std::string title_string = "title";
          std::string css_string = "css";
          std::string digits_string = "digits";

          spatialwidget::legend::set_legend_option( opts, title_string, title, colour_name );
          spatialwidget::legend::set_legend_option( opts, css_string, css, colour_name );
          //Rcpp::Rcout << "legend_digits_str " << legend_digits_str << std::endl;
          spatialwidget::legend::set_legend_option( opts, digits_string, legend_digits_str, colour_name );
          //Rcpp::Rcout << "setting legend digits " << std::endl;
          legend_digits = std::stoi( legend_digits_str );
        }
      }
    }

    // Rcpp::Rcout << "making colours " << std::endl;

    // make colours returns a summary anyway. Whether or not it's included
    // on the map is determined by `make_legend` check
    // since colourvalues controls the summary values, we need 'legend_digits'
    // known here before it goes into 'make_colours' and then into colourvalues
    // Rcpp::Rcout << "spw - going to make colours" << std::endl;
    Rcpp::List legend = make_colours(
      lst_params, params, data, lst_defaults, colourColIndex, //data_column_index, //hex_strings,
      this_colour, alpha, colour_name, include_legend, repeats, total_colours, legend_digits, colour_format
    );

    // Rcpp::Rcout << "sw - done make_colours" << std::endl;

    if (lst_legend.containsElementNamed( colour_name.c_str() ) ) {

      if ( make_legend == true ) {
        Rcpp::List summary = Rcpp::List::create(
          Rcpp::_["colour"] = legend[ "summary_colours" ],
          Rcpp::_["variable"] = legend[ "summary_values" ],
          Rcpp::_["colourType"] = legend[ "colour_type" ],
          Rcpp::_["type"] = legend["type"],
          Rcpp::_["title"] = title,
          Rcpp::_["css"] = css
        );
        lst_legend[ colour_name ] = summary;
      }
    }

    lst_defaults[ colour_name.c_str() ] = legend[ "colours" ];

  }


} // namespace colour
} // namespace spatialwidget

#endif
